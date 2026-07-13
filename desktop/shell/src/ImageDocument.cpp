#include "bos/ImageDocument.h"

#include <QFileInfo>
#include <QStringList>

namespace bos::shell {

ImageDocument::ImageDocument(QObject *parent)
    : QObject(parent)
{
}

QString ImageDocument::imagePath() const { return m_imagePath; }
QString ImageDocument::imageName() const { return m_imageName; }
int ImageDocument::imageWidth() const { return m_imageWidth; }
int ImageDocument::imageHeight() const { return m_imageHeight; }
int ImageDocument::fileSize() const { return m_fileSize; }
QString ImageDocument::format() const { return m_format; }
QDateTime ImageDocument::createdAt() const { return m_createdAt; }
QDateTime ImageDocument::modifiedAt() const { return m_modifiedAt; }
bool ImageDocument::loaded() const { return m_loaded; }
double ImageDocument::zoomLevel() const { return m_zoomLevel; }
int ImageDocument::rotation() const { return m_rotation; }
bool ImageDocument::flippedHorizontally() const { return m_flippedHorizontally; }
bool ImageDocument::flippedVertically() const { return m_flippedVertically; }

void ImageDocument::setImagePath(const QString &path)
{
    if (m_imagePath == path) {
        return;
    }

    m_imagePath = path;
    const QFileInfo info(path);
    m_imageName = info.fileName();
    m_format = info.suffix().toUpper();
    m_fileSize = static_cast<int>(info.size());
    m_createdAt = info.birthTime();
    m_modifiedAt = info.lastModified();
    emit imagePathChanged();
    emit imageNameChanged();
    emit formatChanged();
    emit fileSizeChanged();
    emit createdAtChanged();
    emit modifiedAtChanged();
}

void ImageDocument::setImageSize(const QSize &size)
{
    if (m_imageWidth == size.width() && m_imageHeight == size.height()) {
        return;
    }
    m_imageWidth = size.width();
    m_imageHeight = size.height();
    emit imageSizeChanged();
}

void ImageDocument::setFileSize(int fileSize)
{
    if (m_fileSize == fileSize) {
        return;
    }
    m_fileSize = fileSize;
    emit fileSizeChanged();
}

void ImageDocument::setFormat(const QString &format)
{
    if (m_format == format) {
        return;
    }
    m_format = format;
    emit formatChanged();
}

void ImageDocument::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt) {
        return;
    }
    m_createdAt = createdAt;
    emit createdAtChanged();
}

void ImageDocument::setModifiedAt(const QDateTime &modifiedAt)
{
    if (m_modifiedAt == modifiedAt) {
        return;
    }
    m_modifiedAt = modifiedAt;
    emit modifiedAtChanged();
}

void ImageDocument::setLoaded(bool loaded)
{
    if (m_loaded == loaded) {
        return;
    }
    m_loaded = loaded;
    emit loadedChanged();
}

void ImageDocument::setZoomLevel(double zoomLevel)
{
    if (qFuzzyCompare(m_zoomLevel, zoomLevel)) {
        return;
    }
    m_zoomLevel = zoomLevel;
    emit zoomLevelChanged();
}

void ImageDocument::setRotation(int rotation)
{
    if (m_rotation == rotation) {
        return;
    }
    m_rotation = rotation;
    emit rotationChanged();
}

void ImageDocument::setFlippedHorizontally(bool flipped)
{
    if (m_flippedHorizontally == flipped) {
        return;
    }
    m_flippedHorizontally = flipped;
    emit flipChanged();
}

void ImageDocument::setFlippedVertically(bool flipped)
{
    if (m_flippedVertically == flipped) {
        return;
    }
    m_flippedVertically = flipped;
    emit flipChanged();
}

QString ImageDocument::zoomPercentage() const
{
    return QStringLiteral("%1%").arg(qRound(m_zoomLevel * 100));
}

void ImageDocument::resetTransformations()
{
    setRotation(0);
    setFlippedHorizontally(false);
    setFlippedVertically(false);
    setZoomLevel(1.0);
}

bool ImageDocument::isSupportedFormat(const QString &path)
{
    static const QStringList supported = {
        QStringLiteral("png"),
        QStringLiteral("jpg"),
        QStringLiteral("jpeg"),
        QStringLiteral("bmp"),
        QStringLiteral("gif"),
        QStringLiteral("webp")
    };
    return supported.contains(QFileInfo(path).suffix().toLower());
}

} // namespace bos::shell
