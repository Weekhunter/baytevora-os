#include "bos/TaskManager.h"

#include <QDebug>
#include <QDateTime>
#include <QMetaObject>
#include <QRegularExpression>
#include <QStringList>

#include "bos/NotificationManager.h"
#include "bos/TaskInfo.h"
#include "bos/WindowManager.h"

namespace bos::shell {

TaskManager::TaskManager(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &TaskManager::refresh);
    refresh();
}

TaskManager::~TaskManager() = default;

QVariantList TaskManager::tasks() const
{
    QVariantList list;
    list.reserve(m_tasks.size());
    for (TaskInfo *task : m_tasks) {
        if (!task) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("processId"), task->processId());
        map.insert(QStringLiteral("applicationName"), task->applicationName());
        map.insert(QStringLiteral("executableName"), task->executableName());
        map.insert(QStringLiteral("state"), task->state());
        map.insert(QStringLiteral("cpuUsage"), task->cpuUsage());
        map.insert(QStringLiteral("memoryUsage"), task->memoryUsage());
        map.insert(QStringLiteral("memoryUsageText"), formatMemory(task->memoryUsage()));
        map.insert(QStringLiteral("startTime"), task->startTime());
        map.insert(QStringLiteral("windowCount"), task->windowCount());
        list.append(map);
    }
    return list;
}

void TaskManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void TaskManager::setWindowManager(QObject *manager)
{
    m_windowManager = qobject_cast<WindowManager*>(manager);
}

void TaskManager::refresh()
{
    if (!m_windowManager) {
        emit tasksChanged();
        return;
    }

    const QVariantList windows = m_windowManager->property("windows").toList();
    updateTasks(windows);
    emit tasksChanged();
}

void TaskManager::startMonitoring()
{
    if (m_timer && !m_timer->isActive()) {
        m_timer->start(1000);
    }
}

void TaskManager::stopMonitoring()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}

bool TaskManager::terminateTask(int processId)
{
    TaskInfo *task = findTaskByProcessId(processId);
    if (!task) {
        qWarning() << QStringLiteral("[BDE] TaskManager: task not found for PID") << processId;
        if (m_notificationManager) {
            m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                      QStringLiteral("Failed to Terminate Application."),
                                                      QStringLiteral("Task Manager"),
                                                      QStringLiteral("error"));
        }
        return false;
    }

    const QString appName = task->applicationName();
    if (isProtected(appName)) {
        qWarning() << QStringLiteral("[BDE] TaskManager: refused to terminate protected application") << appName;
        if (m_notificationManager) {
            m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                      QStringLiteral("Failed to Terminate Application."),
                                                      QStringLiteral("Task Manager"),
                                                      QStringLiteral("error"));
        }
        return false;
    }

    if (!m_windowManager) {
        if (m_notificationManager) {
            m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                      QStringLiteral("Failed to Terminate Application."),
                                                      QStringLiteral("Task Manager"),
                                                      QStringLiteral("error"));
        }
        return false;
    }

    const QVariantList windows = m_windowManager->property("windows").toList();
    bool closedAny = false;
    for (const QVariant &windowVar : windows) {
        const QVariantMap window = windowVar.toMap();
        const QString windowApp = window.value(QStringLiteral("applicationName")).toString();
        if (windowApp == appName) {
            const int id = window.value(QStringLiteral("id")).toInt();
            m_windowManager->closeWindow(id);
            closedAny = true;
        }
    }

    if (closedAny) {
        qDebug() << QStringLiteral("[BDE] TaskManager: terminated") << appName;
        if (m_notificationManager) {
            m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                      QStringLiteral("Application Terminated."),
                                                      QStringLiteral("Task Manager"),
                                                      QStringLiteral("info"));
        }
        refresh();
        return true;
    }

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                  QStringLiteral("Failed to Terminate Application."),
                                                  QStringLiteral("Task Manager"),
                                                  QStringLiteral("error"));
    }
    return false;
}

void TaskManager::updateTasks(const QVariantList &windows)
{
    QMap<QString, TaskInfo*> existing;
    for (TaskInfo *task : std::as_const(m_tasks)) {
        existing.insert(task->applicationName(), task);
    }

    // Group windows by application name.
    QMap<QString, QList<QVariantMap>> groups;
    for (const QVariant &windowVar : windows) {
        const QVariantMap window = windowVar.toMap();
        const QString appName = window.value(QStringLiteral("applicationName")).toString();
        if (appName.isEmpty()) {
            continue;
        }
        groups[appName].append(window);
    }

    QList<TaskInfo*> newTasks;
    const QString now = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));

    for (auto it = groups.cbegin(); it != groups.cend(); ++it) {
        const QString appName = it.key();
        const QList<QVariantMap> &appWindows = it.value();

        TaskInfo *task = existing.take(appName);
        if (!task) {
            task = new TaskInfo(this);
            task->setApplicationName(appName);
            task->setExecutableName(QStringLiteral("/usr/bin/") + appName.toLower().replace(QLatin1Char(' '), QLatin1Char('_')));
            task->setStartTime(now);
        }

        task->setProcessId(appWindows.first().value(QStringLiteral("id")).toInt());
        task->setWindowCount(appWindows.size());

        // State reflects the most severe non-normal state if any.
        QString state = QStringLiteral("Normal");
        for (const QVariantMap &window : appWindows) {
            const QString windowState = window.value(QStringLiteral("state")).toString();
            if (windowState == QStringLiteral("Minimized")) {
                state = QStringLiteral("Minimized");
            } else if (windowState == QStringLiteral("Maximized")) {
                state = QStringLiteral("Maximized");
            }
        }
        task->setState(state);

        // Per-application CPU and memory are reported as 0 in this sprint.
        task->setCpuUsage(0.0);
        task->setMemoryUsage(0);

        newTasks.append(task);
    }

    // Any tasks left in existing no longer have windows; remove them.
    for (TaskInfo *task : existing) {
        task->deleteLater();
    }

    m_tasks = newTasks;
}

TaskInfo *TaskManager::findTaskByProcessId(int processId)
{
    for (TaskInfo *task : std::as_const(m_tasks)) {
        if (task->processId() == processId) {
            return task;
        }
    }
    return nullptr;
}

bool TaskManager::isProtected(const QString &applicationName) const
{
    static const QStringList protectedNames = {
        QStringLiteral("Desktop"),
        QStringLiteral("SessionManager"),
        QStringLiteral("WindowManager"),
        QStringLiteral("NotificationService"),
        QStringLiteral("Settings"),
        QStringLiteral("Task Manager")
    };

    if (protectedNames.contains(applicationName)) {
        return true;
    }

    // Any application whose name ends with "Module" or "Service" is treated as
    // a BOS core module and protected from termination.
    if (applicationName.endsWith(QStringLiteral("Module")) ||
        applicationName.endsWith(QStringLiteral("Service"))) {
        return true;
    }

    return false;
}

QString TaskManager::formatMemory(qint64 bytes) const
{
    if (bytes <= 0) {
        return QStringLiteral("0 B");
    }
    const QStringList units = {
        QStringLiteral("B"),
        QStringLiteral("KB"),
        QStringLiteral("MB"),
        QStringLiteral("GB"),
        QStringLiteral("TB")
    };
    int index = 0;
    double value = static_cast<double>(bytes);
    while (value >= 1024.0 && index < units.size() - 1) {
        value /= 1024.0;
        ++index;
    }
    return QString::number(value, 'f', 2) + QLatin1Char(' ') + units.at(index);
}

} // namespace bos::shell
