#include "bos/ImageViewerManager.h"

#include <QDir>
#include <QFileInfo>
#include <QImageReader>
#include <QUrl>

#include "bos/ImageDocument.h"
#include "bos/ImageMetadata.h"
#include "bos/ImageSlideshowManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

ImageViewerManager::ImageViewerManager(QObject *parent)
    : QObject(parent)
    , m_document(new ImageDocument(this))
    , m_metadata(new ImageMetadata(this))
    , m_slideshow(new ImageSlideshowManager(this))
{
    m_metadata->setDocument(m_document);
    m_slideshow->setViewerManager(this);
}

ImageViewerManager::~ImageViewerManager() = default;

ImageDocument *ImageViewerManager::document() const
{
    return m_document;
}

ImageMetadata *ImageViewerManager::metadata() const
{
    return m_metadata;
}

ImageSlideshowManager *ImageViewerManager::slideshow() const
{
    return m_slideshow;
}

void ImageViewerManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager *>(manager);
}

void ImageViewerManager::openImage(const QString &path)
{
    if (path.isEmpty()) {
        return;
    }

    const QString localPath = path.startsWith(QStringLiteral("file://"))
                                  ? QUrl(path).toLocalFile()
                                  : path;

    if (!ImageDocument::isSupportedFormat(localPath)) {
        return;
    }

    loadImage(localPath);

    if (m_document->loaded()) {
        emitNotification(QStringLiteral("Image Opened"),
                         QFileInfo(localPath).fileName());
    }
}

void ImageViewerManager::closeImage()
{
    if (!m_document->loaded()) {
        return;
    }

    m_document->setImagePath(QString());
    m_document->setImageSize(QSize(0, 0));
    m_document->setFileSize(0);
    m_document->setFormat(QString());
    m_document->setLoaded(false);
    m_document->resetTransformations();
    emit documentChanged();

    emitNotification(QStringLiteral("Image Closed"),
                     QStringLiteral("Image closed"));
}

void ImageViewerManager::refreshFolder()
{
    if (m_folderPath.isEmpty()) {
        return;
    }
    m_slideshow->setCurrentFolderPath(m_folderPath);
}

void ImageViewerManager::zoomIn()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setZoomLevel(qMin(m_document->zoomLevel() * 1.25, 5.0));
}

void ImageViewerManager::zoomOut()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setZoomLevel(qMax(m_document->zoomLevel() / 1.25, 0.1));
}

void ImageViewerManager::resetZoom()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setZoomLevel(1.0);
}

void ImageViewerManager::fitToWindow(double windowWidth, double windowHeight)
{
    if (!m_document->loaded() || m_document->imageWidth() <= 0 || m_document->imageHeight() <= 0) {
        return;
    }

    const double scaleX = windowWidth / m_document->imageWidth();
    const double scaleY = windowHeight / m_document->imageHeight();
    m_document->setZoomLevel(qMin(scaleX, scaleY));
}

void ImageViewerManager::fitToWidth(double windowWidth)
{
    if (!m_document->loaded() || m_document->imageWidth() <= 0) {
        return;
    }
    m_document->setZoomLevel(windowWidth / m_document->imageWidth());
}

void ImageViewerManager::fitToHeight(double windowHeight)
{
    if (!m_document->loaded() || m_document->imageHeight() <= 0) {
        return;
    }
    m_document->setZoomLevel(windowHeight / m_document->imageHeight());
}

void ImageViewerManager::actualSize()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setZoomLevel(1.0);
}

void ImageViewerManager::rotateLeft()
{
    if (!m_document->loaded()) {
        return;
    }
    int rotation = m_document->rotation() - 90;
    if (rotation < 0) {
        rotation += 360;
    }
    m_document->setRotation(rotation);
    emitNotification(QStringLiteral("Image Rotated"),
                     QStringLiteral("Rotated left"));
}

void ImageViewerManager::rotateRight()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setRotation((m_document->rotation() + 90) % 360);
    emitNotification(QStringLiteral("Image Rotated"),
                     QStringLiteral("Rotated right"));
}

void ImageViewerManager::flipHorizontal()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setFlippedHorizontally(!m_document->flippedHorizontally());
}

void ImageViewerManager::flipVertical()
{
    if (!m_document->loaded()) {
        return;
    }
    m_document->setFlippedVertically(!m_document->flippedVertically());
}

void ImageViewerManager::resetTransformations()
{
    m_document->resetTransformations();
}

void ImageViewerManager::nextImage()
{
    m_slideshow->next();
}

void ImageViewerManager::previousImage()
{
    m_slideshow->previous();
}

void ImageViewerManager::printImage()
{
    if (!m_document->loaded() || m_document->imagePath().isEmpty()) {
        return;
    }

    // The actual print job is submitted from QML via printManager.printDocument()
    // because the shared PrintManager is owned by the application layer. This slot
    // remains a placeholder-safe hook for future direct printing from C++.
    Q_UNUSED(m_notificationManager)

    emitNotification(QStringLiteral("Image Printed"),
                     QFileInfo(m_document->imagePath()).fileName());
}

void ImageViewerManager::loadImage(const QString &path)
{
    QImageReader reader(path);
    const QSize size = reader.size();

    m_folderPath = QFileInfo(path).absolutePath();
    m_document->setImagePath(path);
    m_document->setImageSize(size.isValid() ? size : QSize(0, 0));
    m_document->setLoaded(size.isValid());
    m_document->resetTransformations();

    m_slideshow->setCurrentFolderPath(m_folderPath);
    refreshFolder();

    emit documentChanged();
}

void ImageViewerManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(QStringLiteral("Image Viewer"),
                                              message,
                                              title,
                                              QStringLiteral("info"));
}

} // namespace bos::shell
