#pragma once

#include <QObject>
#include <QString>

#include "bos/PdfEditorTools.h"

namespace bos::shell {

class NotificationManager;
class PdfAnnotationManager;
class PdfStudioDocument;

/**
 * @brief Manages the state for one Baytevora PDF Studio window.
 *
 * PdfStudioManager owns the document, annotation layer, current tool, and
 * undo/redo state for a single PDF Studio window. It is registered as a QML
 * type and instantiated by each PdfStudioWindow.
 */
class PdfStudioManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(PdfStudioDocument *document READ document NOTIFY documentChanged FINAL)
    Q_PROPERTY(PdfAnnotationManager *annotationManager READ annotationManager NOTIFY annotationManagerChanged FINAL)
    Q_PROPERTY(int currentPage READ currentPage NOTIFY currentPageChanged FINAL)
    Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged FINAL)
    Q_PROPERTY(double zoomLevel READ zoomLevel NOTIFY zoomLevelChanged FINAL)
    Q_PROPERTY(QString zoomPercentage READ zoomPercentage NOTIFY zoomLevelChanged FINAL)
    Q_PROPERTY(PdfEditorTools::ToolType currentTool READ currentTool WRITE setCurrentTool NOTIFY currentToolChanged FINAL)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged FINAL)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY canRedoChanged FINAL)

public:
    explicit PdfStudioManager(QObject *parent = nullptr);
    ~PdfStudioManager() override;

    PdfStudioDocument *document() const;
    PdfAnnotationManager *annotationManager() const;
    int currentPage() const;
    int pageCount() const;
    double zoomLevel() const;
    QString zoomPercentage() const;
    PdfEditorTools::ToolType currentTool() const;
    bool canUndo() const;
    bool canRedo() const;

    void setCurrentTool(PdfEditorTools::ToolType tool);

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void openDocument(const QString &path);
    Q_INVOKABLE void closeDocument();
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void firstPage();
    Q_INVOKABLE void lastPage();
    Q_INVOKABLE void goToPage(int page);
    Q_INVOKABLE void zoomIn();
    Q_INVOKABLE void zoomOut();
    Q_INVOKABLE void resetZoom();
    Q_INVOKABLE void fitToWidth(double viewWidth);
    Q_INVOKABLE void fitToPage(double viewWidth, double viewHeight);
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();

public slots:
    void updatePageCount(int count);
    void setDocumentLoaded(bool loaded);

signals:
    void documentChanged();
    void annotationManagerChanged();
    void currentPageChanged();
    void pageCountChanged();
    void zoomLevelChanged();
    void currentToolChanged();
    void canUndoChanged();
    void canRedoChanged();

private:
    void clampCurrentPage();
    void notifyInfo(const QString &body);
    void notifyError(const QString &body);
    void onUndoChanged();

    PdfStudioDocument *m_document = nullptr;
    PdfAnnotationManager *m_annotationManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;

    PdfEditorTools::ToolType m_currentTool = PdfEditorTools::ToolType::SelectionTool;

    static constexpr double s_zoomStep = 1.25;
    static constexpr double s_minZoom = 0.1;
    static constexpr double s_maxZoom = 5.0;
    static constexpr double s_defaultZoom = 1.0;
    static constexpr double s_pointsPerInch = 72.0;
    static constexpr double s_defaultPageWidthPoints = 612.0;
    static constexpr double s_defaultPageHeightPoints = 792.0;
};

} // namespace bos::shell
