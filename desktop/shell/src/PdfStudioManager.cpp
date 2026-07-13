#include "bos/PdfStudioManager.h"

#include <QDebug>
#include <QFileInfo>
#include <QPdfDocument>
#include <QUrl>

#include "bos/NotificationManager.h"
#include "bos/PdfAnnotationManager.h"
#include "bos/PdfStudioDocument.h"

namespace bos::shell {

PdfStudioManager::PdfStudioManager(QObject *parent)
    : QObject(parent)
    , m_document(new PdfStudioDocument(this))
    , m_annotationManager(new PdfAnnotationManager(this))
{
    connect(m_annotationManager, &PdfAnnotationManager::undoChanged,
            this, &PdfStudioManager::onUndoChanged);
}

PdfStudioManager::~PdfStudioManager() = default;

PdfStudioDocument *PdfStudioManager::document() const
{
    return m_document;
}

PdfAnnotationManager *PdfStudioManager::annotationManager() const
{
    return m_annotationManager;
}

int PdfStudioManager::currentPage() const
{
    return m_document ? m_document->currentPage() : 0;
}

int PdfStudioManager::pageCount() const
{
    return m_document ? m_document->pageCount() : 0;
}

double PdfStudioManager::zoomLevel() const
{
    return m_document ? m_document->zoomLevel() : s_defaultZoom;
}

QString PdfStudioManager::zoomPercentage() const
{
    if (!m_document) {
        return QStringLiteral("100%");
    }
    return QStringLiteral("%1%").arg(qRound(m_document->zoomLevel() * 100.0));
}

PdfEditorTools::ToolType PdfStudioManager::currentTool() const
{
    return m_currentTool;
}

bool PdfStudioManager::canUndo() const
{
    return m_annotationManager && m_annotationManager->canUndo();
}

bool PdfStudioManager::canRedo() const
{
    return m_annotationManager && m_annotationManager->canRedo();
}

void PdfStudioManager::setCurrentTool(PdfEditorTools::ToolType tool)
{
    if (m_currentTool == tool) {
        return;
    }
    m_currentTool = tool;
    emit currentToolChanged();
}

void PdfStudioManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager *>(manager);
}

void PdfStudioManager::openDocument(const QString &path)
{
    if (!m_document) {
        return;
    }

    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file:///"))) {
        localPath = localPath.mid(8);
    } else if (localPath.startsWith(QStringLiteral("file://"))) {
        localPath = localPath.mid(7);
    }

    const QFileInfo info(localPath);
    if (!info.exists() || !info.isFile()) {
        m_document->setError(QStringLiteral("File not found"));
        m_document->setLoaded(false);
        notifyError(QStringLiteral("Failed to Open PDF."));
        return;
    }

    m_annotationManager->clearAnnotations();

    m_document->setFilePath(localPath);
    m_document->setFileName(info.fileName());
    m_document->setCurrentPage(0);
    m_document->setLoaded(true);
    m_document->setError(QString());
    m_document->clearMetadata();

    // Read PDF metadata through QtPdf so the panel can display real values
    // when the document is available.
    QPdfDocument pdf;
    if (pdf.load(localPath) == QPdfDocument::Success) {
        m_document->setTitle(pdf.metaData(QPdfDocument::Title).toString());
        m_document->setAuthor(pdf.metaData(QPdfDocument::Author).toString());
        m_document->setSubject(pdf.metaData(QPdfDocument::Subject).toString());
        m_document->setKeywords(pdf.metaData(QPdfDocument::Keywords).toString());
        m_document->setCreator(pdf.metaData(QPdfDocument::Creator).toString());
        m_document->setProducer(pdf.metaData(QPdfDocument::Producer).toString());
        m_document->setCreationDate(pdf.metaData(QPdfDocument::CreationDate).toDateTime());
        m_document->setModificationDate(pdf.metaData(QPdfDocument::ModificationDate).toDateTime());
    }

    notifyInfo(QStringLiteral("Document Opened."));
    emit documentChanged();
    emit currentPageChanged();
    emit pageCountChanged();
    emit zoomLevelChanged();
}

void PdfStudioManager::closeDocument()
{
    if (!m_document) {
        return;
    }

    m_annotationManager->clearAnnotations();

    m_document->setFilePath(QString());
    m_document->setFileName(QString());
    m_document->setPageCount(0);
    m_document->setCurrentPage(0);
    m_document->setZoomLevel(s_defaultZoom);
    m_document->setLoaded(false);
    m_document->setError(QString());
    m_document->clearMetadata();

    notifyInfo(QStringLiteral("Document Closed."));
    emit documentChanged();
    emit currentPageChanged();
    emit pageCountChanged();
    emit zoomLevelChanged();
}

void PdfStudioManager::nextPage()
{
    if (!m_document || !m_document->loaded()) {
        return;
    }
    goToPage(m_document->currentPage() + 1);
}

void PdfStudioManager::previousPage()
{
    if (!m_document || !m_document->loaded()) {
        return;
    }
    goToPage(m_document->currentPage() - 1);
}

void PdfStudioManager::firstPage()
{
    goToPage(0);
}

void PdfStudioManager::lastPage()
{
    if (!m_document) {
        return;
    }
    goToPage(m_document->pageCount() - 1);
}

void PdfStudioManager::goToPage(int page)
{
    if (!m_document) {
        return;
    }
    const int oldPage = m_document->currentPage();
    m_document->setCurrentPage(qBound(0, page, qMax(0, m_document->pageCount() - 1)));
    if (m_document->currentPage() != oldPage) {
        emit currentPageChanged();
    }
}

void PdfStudioManager::zoomIn()
{
    if (!m_document) {
        return;
    }
    const double newZoom = qMin(m_document->zoomLevel() * s_zoomStep, s_maxZoom);
    m_document->setZoomLevel(newZoom);
    emit zoomLevelChanged();
}

void PdfStudioManager::zoomOut()
{
    if (!m_document) {
        return;
    }
    const double newZoom = qMax(m_document->zoomLevel() / s_zoomStep, s_minZoom);
    m_document->setZoomLevel(newZoom);
    emit zoomLevelChanged();
}

void PdfStudioManager::resetZoom()
{
    if (!m_document) {
        return;
    }
    m_document->setZoomLevel(s_defaultZoom);
    emit zoomLevelChanged();
}

void PdfStudioManager::fitToWidth(double viewWidth)
{
    if (!m_document || !m_document->loaded() || viewWidth <= 0.0) {
        return;
    }
    const double scale = viewWidth / s_defaultPageWidthPoints;
    m_document->setZoomLevel(qBound(s_minZoom, scale, s_maxZoom));
    emit zoomLevelChanged();
}

void PdfStudioManager::fitToPage(double viewWidth, double viewHeight)
{
    if (!m_document || !m_document->loaded() || viewWidth <= 0.0 || viewHeight <= 0.0) {
        return;
    }
    const double scale = qMin(viewWidth / s_defaultPageWidthPoints,
                              viewHeight / s_defaultPageHeightPoints);
    m_document->setZoomLevel(qBound(s_minZoom, scale, s_maxZoom));
    emit zoomLevelChanged();
}

void PdfStudioManager::undo()
{
    if (m_annotationManager) {
        m_annotationManager->undo();
    }
}

void PdfStudioManager::redo()
{
    if (m_annotationManager) {
        m_annotationManager->redo();
    }
}

void PdfStudioManager::updatePageCount(int count)
{
    if (!m_document) {
        return;
    }
    const int oldCount = m_document->pageCount();
    m_document->setPageCount(count);
    clampCurrentPage();
    if (m_document->pageCount() != oldCount) {
        emit pageCountChanged();
    }
}

void PdfStudioManager::setDocumentLoaded(bool loaded)
{
    if (!m_document) {
        return;
    }
    m_document->setLoaded(loaded);
    if (!loaded) {
        m_document->setPageCount(0);
        m_document->setCurrentPage(0);
        emit pageCountChanged();
        emit currentPageChanged();
    }
    emit documentChanged();
}

void PdfStudioManager::clampCurrentPage()
{
    if (!m_document) {
        return;
    }
    const int oldPage = m_document->currentPage();
    m_document->setCurrentPage(qBound(0, m_document->currentPage(),
                                      qMax(0, m_document->pageCount() - 1)));
    if (m_document->currentPage() != oldPage) {
        emit currentPageChanged();
    }
}

void PdfStudioManager::notifyInfo(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Baytevora PDF Studio"),
                                                  body,
                                                  QStringLiteral("Baytevora PDF Studio"),
                                                  QStringLiteral("info"));
    }
}

void PdfStudioManager::notifyError(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Baytevora PDF Studio"),
                                                  body,
                                                  QStringLiteral("Baytevora PDF Studio"),
                                                  QStringLiteral("error"));
    }
}

void PdfStudioManager::onUndoChanged()
{
    emit canUndoChanged();
    emit canRedoChanged();
}

} // namespace bos::shell
