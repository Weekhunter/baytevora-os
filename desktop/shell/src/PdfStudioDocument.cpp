#include "bos/PdfStudioDocument.h"

namespace bos::shell {

PdfStudioDocument::PdfStudioDocument(QObject *parent)
    : QObject(parent)
{
}

QString PdfStudioDocument::filePath() const
{
    return m_filePath;
}

QString PdfStudioDocument::fileName() const
{
    return m_fileName;
}

int PdfStudioDocument::pageCount() const
{
    return m_pageCount;
}

int PdfStudioDocument::currentPage() const
{
    return m_currentPage;
}

double PdfStudioDocument::zoomLevel() const
{
    return m_zoomLevel;
}

bool PdfStudioDocument::loaded() const
{
    return m_loaded;
}

QString PdfStudioDocument::error() const
{
    return m_error;
}

QString PdfStudioDocument::title() const
{
    return m_title;
}

QString PdfStudioDocument::author() const
{
    return m_author;
}

QString PdfStudioDocument::subject() const
{
    return m_subject;
}

QString PdfStudioDocument::keywords() const
{
    return m_keywords;
}

QString PdfStudioDocument::creator() const
{
    return m_creator;
}

QString PdfStudioDocument::producer() const
{
    return m_producer;
}

QDateTime PdfStudioDocument::creationDate() const
{
    return m_creationDate;
}

QDateTime PdfStudioDocument::modificationDate() const
{
    return m_modificationDate;
}

void PdfStudioDocument::setFilePath(const QString &path)
{
    if (m_filePath == path) {
        return;
    }
    m_filePath = path;
    emit filePathChanged();
}

void PdfStudioDocument::setFileName(const QString &name)
{
    if (m_fileName == name) {
        return;
    }
    m_fileName = name;
    emit fileNameChanged();
}

void PdfStudioDocument::setPageCount(int count)
{
    if (m_pageCount == count) {
        return;
    }
    m_pageCount = count;
    emit pageCountChanged();
}

void PdfStudioDocument::setCurrentPage(int page)
{
    if (m_currentPage == page) {
        return;
    }
    m_currentPage = page;
    emit currentPageChanged();
}

void PdfStudioDocument::setZoomLevel(double zoom)
{
    if (qFuzzyCompare(m_zoomLevel, zoom)) {
        return;
    }
    m_zoomLevel = zoom;
    emit zoomLevelChanged();
}

void PdfStudioDocument::setLoaded(bool loaded)
{
    if (m_loaded == loaded) {
        return;
    }
    m_loaded = loaded;
    emit loadedChanged();
}

void PdfStudioDocument::setError(const QString &error)
{
    if (m_error == error) {
        return;
    }
    m_error = error;
    emit errorChanged();
}

void PdfStudioDocument::setTitle(const QString &title)
{
    if (m_title == title) {
        return;
    }
    m_title = title;
    emit metadataChanged();
}

void PdfStudioDocument::setAuthor(const QString &author)
{
    if (m_author == author) {
        return;
    }
    m_author = author;
    emit metadataChanged();
}

void PdfStudioDocument::setSubject(const QString &subject)
{
    if (m_subject == subject) {
        return;
    }
    m_subject = subject;
    emit metadataChanged();
}

void PdfStudioDocument::setKeywords(const QString &keywords)
{
    if (m_keywords == keywords) {
        return;
    }
    m_keywords = keywords;
    emit metadataChanged();
}

void PdfStudioDocument::setCreator(const QString &creator)
{
    if (m_creator == creator) {
        return;
    }
    m_creator = creator;
    emit metadataChanged();
}

void PdfStudioDocument::setProducer(const QString &producer)
{
    if (m_producer == producer) {
        return;
    }
    m_producer = producer;
    emit metadataChanged();
}

void PdfStudioDocument::setCreationDate(const QDateTime &date)
{
    if (m_creationDate == date) {
        return;
    }
    m_creationDate = date;
    emit metadataChanged();
}

void PdfStudioDocument::setModificationDate(const QDateTime &date)
{
    if (m_modificationDate == date) {
        return;
    }
    m_modificationDate = date;
    emit metadataChanged();
}

void PdfStudioDocument::clearMetadata()
{
    m_title.clear();
    m_author.clear();
    m_subject.clear();
    m_keywords.clear();
    m_creator.clear();
    m_producer.clear();
    m_creationDate = QDateTime();
    m_modificationDate = QDateTime();
    emit metadataChanged();
}

} // namespace bos::shell
