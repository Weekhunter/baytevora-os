#include "bos/StorageApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

StorageApplication::StorageApplication(QObject *parent)
    : QObject(parent)
{
}

StorageApplication::~StorageApplication() = default;

void StorageApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void StorageApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int StorageApplication::open()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] StorageApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 880;
    constexpr int height = 600;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Storage Manager"),
        width,
        height,
        x,
        y,
        QStringLiteral("Storage Manager"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Storage Manager window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Storage Manager"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Storage Manager"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
