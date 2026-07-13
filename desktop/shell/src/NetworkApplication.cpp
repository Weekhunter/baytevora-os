#include "bos/NetworkApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

NetworkApplication::NetworkApplication(QObject *parent)
    : QObject(parent)
{
}

NetworkApplication::~NetworkApplication() = default;

void NetworkApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void NetworkApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int NetworkApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] NetworkApplication: WindowManager not available");
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
        QStringLiteral("Network Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Network Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Network Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Network Manager"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Network Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
