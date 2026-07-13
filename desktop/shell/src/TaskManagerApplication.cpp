#include "bos/TaskManagerApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

TaskManagerApplication::TaskManagerApplication(QObject *parent)
    : QObject(parent)
{
}

TaskManagerApplication::~TaskManagerApplication() = default;

void TaskManagerApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void TaskManagerApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int TaskManagerApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] TaskManagerApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 820;
    constexpr int height = 560;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Task Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Task Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Task Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Task Manager"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Task Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
