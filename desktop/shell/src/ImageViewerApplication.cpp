#include "bos/ImageViewerApplication.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "bos/NotificationManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

ImageViewerApplication::ImageViewerApplication(QObject *parent)
    : QObject(parent)
{
}

ImageViewerApplication::~ImageViewerApplication() = default;

void ImageViewerApplication::setWindowManager(WindowManager *windowManager)
{
    m_windowManager = windowManager;
}

void ImageViewerApplication::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int ImageViewerApplication::open()
{
    return doOpen();
}

int ImageViewerApplication::openFile(const QString &filePath)
{
    if (!filePath.isEmpty()) {
        m_pendingOpenFiles.append(filePath);
    }
    return doOpen();
}

bool ImageViewerApplication::hasPendingOpenFile() const
{
    return !m_pendingOpenFiles.isEmpty();
}

QString ImageViewerApplication::takePendingOpenFile()
{
    if (m_pendingOpenFiles.isEmpty()) {
        return QString();
    }
    return m_pendingOpenFiles.takeFirst();
}

int ImageViewerApplication::doOpen()
{
    if (!m_windowManager) {
        qWarning() << QStringLiteral("[BDE] ImageViewerApplication: WindowManager not available");
        return -1;
    }

    constexpr int width = 800;
    constexpr int height = 560;

    int x = 0;
    int y = 0;
    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        const QRect geometry = screen->availableGeometry();
        x = (geometry.width() - width) / 2;
        y = (geometry.height() - height) / 2;
    }

    const int windowId = m_windowManager->registerWindow(
        QStringLiteral("Image Viewer"),
        width,
        height,
        x,
        y,
        QStringLiteral("Image Viewer"));

    m_windowManager->setActiveWindow(windowId);

    qDebug() << QStringLiteral("[BDE] Image Viewer window opened (ID:") << windowId << QStringLiteral(")");

    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Image Viewer"),
                                                  QStringLiteral("Ready."),
                                                  QStringLiteral("Image Viewer"),
                                                  QStringLiteral("info"));
    }

    return windowId;
}

} // namespace bos::shell
