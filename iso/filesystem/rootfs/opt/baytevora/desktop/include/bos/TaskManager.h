#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

namespace bos::shell {

class NotificationManager;
class TaskInfo;
class WindowManager;

/**
 * @brief Maintains a live model of running Baytevora applications for the Task
 * Manager.
 *
 * TaskManager refreshes every second from WindowManager state. Each task
 * represents one application with one or more windows. Termination only closes
 * user applications launched through the Application Framework; protected BOS
 * core services and the Task Manager itself cannot be terminated.
 */
class TaskManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList tasks READ tasks NOTIFY tasksChanged FINAL)

public:
    explicit TaskManager(QObject *parent = nullptr);
    ~TaskManager() override;

    QVariantList tasks() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);
    Q_INVOKABLE void setWindowManager(QObject *manager);

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void startMonitoring();
    Q_INVOKABLE void stopMonitoring();

    /**
     * @brief Terminates the task identified by its process ID.
     *
     * The process ID corresponds to the first window ID of the application.
     * This method only closes user applications launched through the Baytevora
     * Application Framework. Protected BOS services cannot be terminated.
     *
     * @return true if the task was terminated, false otherwise.
     */
    Q_INVOKABLE bool terminateTask(int processId);

private:
    void updateTasks(const QVariantList &windows);
    TaskInfo *findTaskByProcessId(int processId);
    bool isProtected(const QString &applicationName) const;
    QString formatMemory(qint64 bytes) const;

    NotificationManager *m_notificationManager = nullptr;
    WindowManager *m_windowManager = nullptr;
    QTimer *m_timer = nullptr;
    QList<TaskInfo*> m_tasks;
};

} // namespace bos::shell
