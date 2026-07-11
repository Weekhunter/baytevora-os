#include "bos/StoreApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

StoreApplication::StoreApplication(QObject *parent)
    : QObject(parent)
{
}

StoreApplication::~StoreApplication() = default;

void StoreApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void StoreApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int StoreApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] StoreApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 1000;
    constexpr int height = 700;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Baytevora Store"),
        width,
        height,
        x,
        y,
        QStringLiteral("Baytevora Store"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Baytevora Store window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Baytevora Store"),
                                                      QStringLiteral("Ready."),
                                                      QStringLiteral("Store"),
                                                      QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
