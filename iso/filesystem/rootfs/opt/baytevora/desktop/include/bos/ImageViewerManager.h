#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class ImageDocument;
class ImageMetadata;
class ImageSlideshowManager;
class NotificationManager;

/**
 * @brief Manages the image document, metadata, transformations, and slideshow
 *        for one Image Viewer window.
 */
class ImageViewerManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(ImageDocument *document READ document NOTIFY documentChanged FINAL)
    Q_PROPERTY(ImageMetadata *metadata READ metadata NOTIFY documentChanged FINAL)
    Q_PROPERTY(ImageSlideshowManager *slideshow READ slideshow NOTIFY documentChanged FINAL)

public:
    explicit ImageViewerManager(QObject *parent = nullptr);
    ~ImageViewerManager() override;

    ImageDocument *document() const;
    ImageMetadata *metadata() const;
    ImageSlideshowManager *slideshow() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void openImage(const QString &path);
    Q_INVOKABLE void closeImage();
    Q_INVOKABLE void refreshFolder();

    Q_INVOKABLE void zoomIn();
    Q_INVOKABLE void zoomOut();
    Q_INVOKABLE void resetZoom();
    Q_INVOKABLE void fitToWindow(double windowWidth, double windowHeight);
    Q_INVOKABLE void fitToWidth(double windowWidth);
    Q_INVOKABLE void fitToHeight(double windowHeight);
    Q_INVOKABLE void actualSize();

    Q_INVOKABLE void rotateLeft();
    Q_INVOKABLE void rotateRight();
    Q_INVOKABLE void flipHorizontal();
    Q_INVOKABLE void flipVertical();
    Q_INVOKABLE void resetTransformations();

    Q_INVOKABLE void nextImage();
    Q_INVOKABLE void previousImage();
    Q_INVOKABLE void printImage();

signals:
    void documentChanged();

private:
    void emitNotification(const QString &title, const QString &message);
    void loadImage(const QString &path);

    ImageDocument *m_document = nullptr;
    ImageMetadata *m_metadata = nullptr;
    ImageSlideshowManager *m_slideshow = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QString m_folderPath;
};

} // namespace bos::shell
