#include "bos/ImageMetadata.h"

#include "bos/ImageDocument.h"

namespace bos::shell {

ImageMetadata::ImageMetadata(QObject *parent)
    : QObject(parent)
{
}

QString ImageMetadata::fileName() const
{
    return m_document ? m_document->imageName() : QString();
}

QString ImageMetadata::filePath() const
{
    return m_document ? m_document->imagePath() : QString();
}

int ImageMetadata::width() const
{
    return m_document ? m_document->imageWidth() : 0;
}

int ImageMetadata::height() const
{
    return m_document ? m_document->imageHeight() : 0;
}

QString ImageMetadata::resolution() const
{
    if (!m_document) {
        return QString();
    }
    return QStringLiteral("%1 x %2").arg(m_document->imageWidth())
                                      .arg(m_document->imageHeight());
}

QString ImageMetadata::format() const
{
    return m_document ? m_document->format() : QString();
}

int ImageMetadata::fileSize() const
{
    return m_document ? m_document->fileSize() : 0;
}

QString ImageMetadata::createdAt() const
{
    return m_document ? m_document->createdAt().toString(QStringLiteral("yyyy-MM-dd hh:mm"))
                      : QString();
}

QString ImageMetadata::modifiedAt() const
{
    return m_document ? m_document->modifiedAt().toString(QStringLiteral("yyyy-MM-dd hh:mm"))
                      : QString();
}

void ImageMetadata::setDocument(ImageDocument *document)
{
    if (m_document == document) {
        return;
    }

    if (m_document) {
        disconnect(m_document, nullptr, this, nullptr);
    }

    m_document = document;

    if (m_document) {
        connect(m_document, &ImageDocument::imagePathChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::imageNameChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::imageSizeChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::fileSizeChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::formatChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::createdAtChanged, this, &ImageMetadata::metadataChanged);
        connect(m_document, &ImageDocument::modifiedAtChanged, this, &ImageMetadata::metadataChanged);
    }

    emit metadataChanged();
}

} // namespace bos::shell
