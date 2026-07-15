#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

class ImageDocument;

/**
 * @brief Exposes image metadata to QML.
 *
 * ImageMetadata reads from an ImageDocument and presents dimensions, format,
 * file size, and timestamps.
 */
class ImageMetadata : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString fileName READ fileName NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString filePath READ filePath NOTIFY metadataChanged FINAL)
    Q_PROPERTY(int width READ width NOTIFY metadataChanged FINAL)
    Q_PROPERTY(int height READ height NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString resolution READ resolution NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString format READ format NOTIFY metadataChanged FINAL)
    Q_PROPERTY(int fileSize READ fileSize NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString createdAt READ createdAt NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString modifiedAt READ modifiedAt NOTIFY metadataChanged FINAL)

public:
    explicit ImageMetadata(QObject *parent = nullptr);

    QString fileName() const;
    QString filePath() const;
    int width() const;
    int height() const;
    QString resolution() const;
    QString format() const;
    int fileSize() const;
    QString createdAt() const;
    QString modifiedAt() const;

    Q_INVOKABLE void setDocument(ImageDocument *document);

signals:
    void metadataChanged();

private:
    ImageDocument *m_document = nullptr;
};

} // namespace bos::shell
