#include "bos/PdfAnnotationManager.h"

#include <QUuid>

#include "bos/PdfAnnotation.h"
#include "bos/PdfEditorTools.h"

namespace bos::shell {

PdfAnnotationManager::PdfAnnotationManager(QObject *parent)
    : QObject(parent)
{
}

PdfAnnotationManager::~PdfAnnotationManager() = default;

QVariantList PdfAnnotationManager::annotations() const
{
    QVariantList result;
    result.reserve(m_annotations.size());
    for (const PdfAnnotation *annotation : m_annotations) {
        if (annotation) {
            result.append(annotation->toMap());
        }
    }
    return result;
}

int PdfAnnotationManager::count() const
{
    return m_annotations.size();
}

bool PdfAnnotationManager::canUndo() const
{
    return !m_undoStack.isEmpty();
}

bool PdfAnnotationManager::canRedo() const
{
    return !m_redoStack.isEmpty();
}

QString PdfAnnotationManager::addAnnotation(int pageNumber,
                                            int toolType,
                                            const QRectF &rect,
                                            const QColor &color,
                                            const QString &contents,
                                            const QString &author)
{
    auto *annotation = new PdfAnnotation(this);
    const QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    annotation->setId(id);
    annotation->setPageNumber(pageNumber);
    annotation->setType(static_cast<PdfEditorTools::ToolType>(toolType));
    annotation->setRect(rect.normalized());
    annotation->setColor(color.isValid() ? color : QColor(Qt::yellow));
    annotation->setContents(contents);
    annotation->setAuthor(author.isEmpty() ? QStringLiteral("Baytevora PDF Studio") : author);
    annotation->setCreationDate(QDateTime::currentDateTimeUtc());
    annotation->setSelected(false);

    m_annotations.append(annotation);

    Change change;
    change.type = Change::Type::Add;
    change.id = id;
    change.data = annotation->toMap();
    pushUndo(change);

    notifyChanges();
    return id;
}

void PdfAnnotationManager::moveAnnotation(const QString &id, const QRectF &rect)
{
    PdfAnnotation *annotation = findAnnotation(id);
    if (!annotation) {
        return;
    }

    const QRectF oldRect = annotation->rect();
    if (oldRect == rect.normalized()) {
        return;
    }

    annotation->setRect(rect.normalized());

    Change change;
    change.type = Change::Type::Move;
    change.id = id;
    change.oldRect = oldRect;
    change.newRect = annotation->rect();
    pushUndo(change);

    notifyChanges();
}

void PdfAnnotationManager::resizeAnnotation(const QString &id, const QRectF &rect)
{
    // Resize is implemented as a rect change with a different semantic in QML.
    moveAnnotation(id, rect);
}

void PdfAnnotationManager::deleteAnnotation(const QString &id)
{
    PdfAnnotation *annotation = findAnnotation(id);
    if (!annotation) {
        return;
    }

    Change change;
    change.type = Change::Type::Delete;
    change.id = id;
    change.data = annotation->toMap();
    pushUndo(change);

    m_annotations.removeOne(annotation);
    annotation->deleteLater();

    notifyChanges();
}

void PdfAnnotationManager::selectAnnotation(const QString &id)
{
    PdfAnnotation *target = findAnnotation(id);
    if (!target) {
        return;
    }

    for (PdfAnnotation *annotation : m_annotations) {
        if (annotation) {
            annotation->setSelected(false);
        }
    }
    target->setSelected(true);

    emit selectionChanged(id);
    emit annotationsChanged();
}

void PdfAnnotationManager::deselectAllAnnotations()
{
    bool changed = false;
    for (PdfAnnotation *annotation : m_annotations) {
        if (annotation && annotation->selected()) {
            annotation->setSelected(false);
            changed = true;
        }
    }
    if (changed) {
        emit annotationsChanged();
    }
}

void PdfAnnotationManager::undo()
{
    if (m_undoStack.isEmpty()) {
        return;
    }

    const Change change = m_undoStack.pop();
    m_redoStack.push(change);

    switch (change.type) {
    case Change::Type::Add: {
        PdfAnnotation *annotation = findAnnotation(change.id);
        if (annotation) {
            m_annotations.removeOne(annotation);
            annotation->deleteLater();
        }
        break;
    }
    case Change::Type::Move: {
        PdfAnnotation *annotation = findAnnotation(change.id);
        if (annotation) {
            annotation->setRect(change.oldRect);
        }
        break;
    }
    case Change::Type::Delete: {
        PdfAnnotation *annotation = PdfAnnotation::fromMap(change.data, this);
        annotation->setId(change.id);
        m_annotations.append(annotation);
        break;
    }
    }

    notifyChanges();
}

void PdfAnnotationManager::redo()
{
    if (m_redoStack.isEmpty()) {
        return;
    }

    const Change change = m_redoStack.pop();
    m_undoStack.push(change);

    switch (change.type) {
    case Change::Type::Add: {
        PdfAnnotation *annotation = PdfAnnotation::fromMap(change.data, this);
        annotation->setId(change.id);
        m_annotations.append(annotation);
        break;
    }
    case Change::Type::Move: {
        PdfAnnotation *annotation = findAnnotation(change.id);
        if (annotation) {
            annotation->setRect(change.newRect);
        }
        break;
    }
    case Change::Type::Delete: {
        PdfAnnotation *annotation = findAnnotation(change.id);
        if (annotation) {
            m_annotations.removeOne(annotation);
            annotation->deleteLater();
        }
        break;
    }
    }

    notifyChanges();
}

void PdfAnnotationManager::clearAnnotations()
{
    for (PdfAnnotation *annotation : m_annotations) {
        if (annotation) {
            annotation->deleteLater();
        }
    }
    m_annotations.clear();
    m_undoStack.clear();
    m_redoStack.clear();
    notifyChanges();
}

PdfAnnotation *PdfAnnotationManager::findAnnotation(const QString &id) const
{
    for (PdfAnnotation *annotation : m_annotations) {
        if (annotation && annotation->id() == id) {
            return annotation;
        }
    }
    return nullptr;
}

void PdfAnnotationManager::pushUndo(const Change &change)
{
    m_undoStack.push(change);
    m_redoStack.clear();
}

void PdfAnnotationManager::notifyChanges()
{
    emit annotationsChanged();
    emit undoChanged();
}

} // namespace bos::shell
