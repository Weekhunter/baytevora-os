#include "bos/BrowserApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

BrowserApplication::BrowserApplication(QObject *parent)
    : QObject(parent)
{
}

BrowserApplication::~BrowserApplication() = default;

void BrowserApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void BrowserApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int BrowserApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] BrowserApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 1100;
    constexpr int height = 760;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Browser"),
        width,
        height,
        x,
        y,
        QStringLiteral("Browser"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Browser window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Browser"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Browser"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
