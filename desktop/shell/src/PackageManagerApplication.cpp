#include "bos/PackageManagerApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

PackageManagerApplication::PackageManagerApplication(QObject *parent)
    : QObject(parent)
{
}

PackageManagerApplication::~PackageManagerApplication() = default;

void PackageManagerApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void PackageManagerApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int PackageManagerApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] PackageManagerApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 960;
    constexpr int height = 640;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Package Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Package Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Package Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Package Manager"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Package Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
