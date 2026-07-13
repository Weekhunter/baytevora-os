#include "bos/SystemMonitorApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

SystemMonitorApplication::SystemMonitorApplication(QObject *parent)
    : QObject(parent)
{
}

SystemMonitorApplication::~SystemMonitorApplication() = default;

void SystemMonitorApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void SystemMonitorApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int SystemMonitorApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] SystemMonitorApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 780;
    constexpr int height = 580;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("System Monitor"),
        width,
        height,
        x,
        y,
        QStringLiteral("System Monitor"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] System Monitor window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("System Monitor"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("System Monitor"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
