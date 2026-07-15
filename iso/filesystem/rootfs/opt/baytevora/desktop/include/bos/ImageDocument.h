#pragma once

#include <QDateTime>
#include <QObject>
#include <QSize>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents the document currently loaded in the Image Viewer.
 */
class ImageDocument : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged FINAL)
    Q_PROPERTY(QString imageName READ imageName NOTIFY imageNameChanged FINAL)
    Q_PROPERTY(QString filePath READ imagePath NOTIFY imagePathChanged FINAL)
    Q_PROPERTY(QString fileName READ imageName NOTIFY imageNameChanged FINAL)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY imageSizeChanged FINAL)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY imageSizeChanged FINAL)
    Q_PROPERTY(int width READ imageWidth NOTIFY imageSizeChanged FINAL)
    Q_PROPERTY(int height READ imageHeight NOTIFY imageSizeChanged FINAL)
    Q_PROPERTY(int fileSize READ fileSize NOTIFY fileSizeChanged FINAL)
    Q_PROPERTY(QString format READ format NOTIFY formatChanged FINAL)
    Q_PROPERTY(QDateTime createdAt READ createdAt NOTIFY createdAtChanged FINAL)
    Q_PROPERTY(QDateTime modifiedAt READ modifiedAt NOTIFY modifiedAtChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged FINAL)
    Q_PROPERTY(QString zoomPercentage READ zoomPercentage NOTIFY zoomLevelChanged FINAL)
    Q_PROPERTY(int rotation READ rotation NOTIFY rotationChanged FINAL)
    Q_PROPERTY(bool flippedHorizontally READ flippedHorizontally NOTIFY flipChanged FINAL)
    Q_PROPERTY(bool flippedVertically READ flippedVertically NOTIFY flipChanged FINAL)

public:
    explicit ImageDocument(QObject *parent = nullptr);

    QString imagePath() const;
    QString imageName() const;
    int imageWidth() const;
    int imageHeight() const;
    int fileSize() const;
    QString format() const;
    QDateTime createdAt() const;
    QDateTime modifiedAt() const;
    bool loaded() const;
    double zoomLevel() const;
    int rotation() const;
    bool flippedHorizontally() const;
    bool flippedVertically() const;

    void setImagePath(const QString &path);
    void setImageSize(const QSize &size);
    void setFileSize(int fileSize);
    void setFormat(const QString &format);
    void setCreatedAt(const QDateTime &createdAt);
    void setModifiedAt(const QDateTime &modifiedAt);
    void setLoaded(bool loaded);
    void setZoomLevel(double zoomLevel);
    void setRotation(int rotation);
    void setFlippedHorizontally(bool flipped);
    void setFlippedVertically(bool flipped);

    Q_INVOKABLE QString zoomPercentage() const;
    Q_INVOKABLE void resetTransformations();

    static bool isSupportedFormat(const QString &path);

signals:
    void imagePathChanged();
    void imageNameChanged();
    void imageSizeChanged();
    void fileSizeChanged();
    void formatChanged();
    void createdAtChanged();
    void modifiedAtChanged();
    void loadedChanged();
    void zoomLevelChanged();
    void rotationChanged();
    void flipChanged();

private:
    QString m_imagePath;
    QString m_imageName;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    int m_fileSize = 0;
    QString m_format;
    QDateTime m_createdAt;
    QDateTime m_modifiedAt;
    bool m_loaded = false;
    double m_zoomLevel = 1.0;
    int m_rotation = 0;
    bool m_flippedHorizontally = false;
    bool m_flippedVertically = false;
};

} // namespace bos::shell
