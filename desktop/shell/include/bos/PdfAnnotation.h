#pragma once

#include <QColor>
#include <QDateTime>
#include <QObject>
#include <QRectF>
#include <QString>
#include <QVariantMap>

#include "bos/PdfEditorTools.h"

namespace bos::shell {

/**
 * @brief Represents a single local annotation inside a PDF Studio document.
 *
 * PdfAnnotation stores the visual and metadata state for one annotation. The
 * manager serializes annotations to QVariantMap for QML consumption and
 * undo/redo handling.
 */
class PdfAnnotation : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString id READ id NOTIFY changed FINAL)
    Q_PROPERTY(int pageNumber READ pageNumber WRITE setPageNumber NOTIFY changed FINAL)
    Q_PROPERTY(PdfEditorTools::ToolType type READ type WRITE setType NOTIFY changed FINAL)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect NOTIFY changed FINAL)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY changed FINAL)
    Q_PROPERTY(QString contents READ contents WRITE setContents NOTIFY changed FINAL)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY changed FINAL)
    Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate NOTIFY changed FINAL)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY changed FINAL)

public:
    explicit PdfAnnotation(QObject *parent = nullptr);

    QString id() const;
    int pageNumber() const;
    PdfEditorTools::ToolType type() const;
    QRectF rect() const;
    QColor color() const;
    QString contents() const;
    QString author() const;
    QDateTime creationDate() const;
    bool selected() const;

    void setId(const QString &id);
    void setPageNumber(int page);
    void setType(PdfEditorTools::ToolType type);
    void setRect(const QRectF &rect);
    void setColor(const QColor &color);
    void setContents(const QString &contents);
    void setAuthor(const QString &author);
    void setCreationDate(const QDateTime &date);
    void setSelected(bool selected);

    QVariantMap toMap() const;
    static PdfAnnotation *fromMap(const QVariantMap &map, QObject *parent = nullptr);

signals:
    void changed();

private:
    QString m_id;
    int m_pageNumber = 0;
    PdfEditorTools::ToolType m_type = PdfEditorTools::ToolType::SelectionTool;
    QRectF m_rect;
    QColor m_color = QColor(Qt::yellow);
    QString m_contents;
    QString m_author;
    QDateTime m_creationDate;
    bool m_selected = false;
};

} // namespace bos::shell
