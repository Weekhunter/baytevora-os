#include "bos/MediaPlayerApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

MediaPlayerApplication::MediaPlayerApplication(QObject *parent)
    : QObject(parent)
{
}

MediaPlayerApplication::~MediaPlayerApplication() = default;

void MediaPlayerApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void MediaPlayerApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int MediaPlayerApplication::open()
{
    return openInternal(QString());
}

int MediaPlayerApplication::openMedia(const QString &path)
{
    return openInternal(path);
}

int MediaPlayerApplication::openInternal(const QString &initialPath)
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] MediaPlayerApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 900;
    constexpr int height = 640;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Media Player"),
        width,
        height,
        x,
        y,
        QStringLiteral("Media Player"));

    m_windowManager->setActiveWindow(windowId);

    Q_UNUSED(initialPath)

    qDebug() << QStringLiteral("[BDE] Media Player window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Media Player"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Media Player"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
