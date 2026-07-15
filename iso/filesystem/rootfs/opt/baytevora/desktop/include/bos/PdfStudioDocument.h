#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Metadata holder for a PDF Studio document.
 *
 * PdfStudioDocument tracks the file path, basic rendering state, and PDF
 * metadata (title, author, dates, etc.) for the currently loaded document. It
 * is owned by PdfStudioManager and exposed to QML.
 */
class PdfStudioDocument : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged FINAL)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged FINAL)
    Q_PROPERTY(double zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged FINAL)

    Q_PROPERTY(QString title READ title NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString author READ author NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString subject READ subject NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString keywords READ keywords NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString creator READ creator NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString producer READ producer NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QDateTime creationDate READ creationDate NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QDateTime modificationDate READ modificationDate NOTIFY metadataChanged FINAL)

public:
    explicit PdfStudioDocument(QObject *parent = nullptr);

    QString filePath() const;
    QString fileName() const;
    int pageCount() const;
    int currentPage() const;
    double zoomLevel() const;
    bool loaded() const;
    QString error() const;

    QString title() const;
    QString author() const;
    QString subject() const;
    QString keywords() const;
    QString creator() const;
    QString producer() const;
    QDateTime creationDate() const;
    QDateTime modificationDate() const;

    void setFilePath(const QString &path);
    void setFileName(const QString &name);
    void setPageCount(int count);
    void setCurrentPage(int page);
    void setZoomLevel(double zoom);
    void setLoaded(bool loaded);
    void setError(const QString &error);

    void setTitle(const QString &title);
    void setAuthor(const QString &author);
    void setSubject(const QString &subject);
    void setKeywords(const QString &keywords);
    void setCreator(const QString &creator);
    void setProducer(const QString &producer);
    void setCreationDate(const QDateTime &date);
    void setModificationDate(const QDateTime &date);
    void clearMetadata();

signals:
    void filePathChanged();
    void fileNameChanged();
    void pageCountChanged();
    void currentPageChanged();
    void zoomLevelChanged();
    void loadedChanged();
    void errorChanged();
    void metadataChanged();

private:
    QString m_filePath;
    QString m_fileName;
    int m_pageCount = 0;
    int m_currentPage = 0;
    double m_zoomLevel = 1.0;
    bool m_loaded = false;
    QString m_error;

    QString m_title;
    QString m_author;
    QString m_subject;
    QString m_keywords;
    QString m_creator;
    QString m_producer;
    QDateTime m_creationDate;
    QDateTime m_modificationDate;
};

} // namespace bos::shell
