#pragma once

#include <QColor>
#include <QObject>
#include <QRectF>
#include <QStack>
#include <QString>
#include <QVariantList>

namespace bos::shell {

class PdfAnnotation;
class PdfEditorTools;

/**
 * @brief Owns and manipulates the local annotation layer for one PDF document.
 *
 * PdfAnnotationManager keeps a list of PdfAnnotation objects, exposes them to
 * QML as a QVariantList, and maintains an undo/redo stack for add, move,
 * resize, and delete operations. All annotations are stored in memory only;
 * persistence is reserved for future milestones.
 */
class PdfAnnotationManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList annotations READ annotations NOTIFY annotationsChanged FINAL)
    Q_PROPERTY(int count READ count NOTIFY annotationsChanged FINAL)
    Q_PROPERTY(bool canUndo READ canUndo NOTIFY undoChanged FINAL)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY undoChanged FINAL)

public:
    explicit PdfAnnotationManager(QObject *parent = nullptr);
    ~PdfAnnotationManager() override;

    QVariantList annotations() const;
    int count() const;
    bool canUndo() const;
    bool canRedo() const;

    Q_INVOKABLE QString addAnnotation(int pageNumber,
                                      int toolType,
                                      const QRectF &rect,
                                      const QColor &color,
                                      const QString &contents,
                                      const QString &author);
    Q_INVOKABLE void moveAnnotation(const QString &id, const QRectF &rect);
    Q_INVOKABLE void resizeAnnotation(const QString &id, const QRectF &rect);
    Q_INVOKABLE void deleteAnnotation(const QString &id);
    Q_INVOKABLE void selectAnnotation(const QString &id);
    Q_INVOKABLE void deselectAllAnnotations();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE void clearAnnotations();

signals:
    void annotationsChanged();
    void undoChanged();
    void selectionChanged(const QString &id);

private:
    struct Change {
        enum class Type { Add, Move, Delete };
        Type type;
        QString id;
        QVariantMap data;
        QRectF oldRect;
        QRectF newRect;
    };

    PdfAnnotation *findAnnotation(const QString &id) const;
    void pushUndo(const Change &change);
    void notifyChanges();

    QList<PdfAnnotation *> m_annotations;
    QStack<Change> m_undoStack;
    QStack<Change> m_redoStack;
};

} // namespace bos::shell
