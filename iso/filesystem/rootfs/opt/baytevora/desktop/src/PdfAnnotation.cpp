#include "bos/PdfAnnotation.h"

#include <QUuid>

namespace bos::shell {

PdfAnnotation::PdfAnnotation(QObject *parent)
    : QObject(parent)
{
}

QString PdfAnnotation::id() const
{
    return m_id;
}

int PdfAnnotation::pageNumber() const
{
    return m_pageNumber;
}

PdfEditorTools::ToolType PdfAnnotation::type() const
{
    return m_type;
}

QRectF PdfAnnotation::rect() const
{
    return m_rect;
}

QColor PdfAnnotation::color() const
{
    return m_color;
}

QString PdfAnnotation::contents() const
{
    return m_contents;
}

QString PdfAnnotation::author() const
{
    return m_author;
}

QDateTime PdfAnnotation::creationDate() const
{
    return m_creationDate;
}

bool PdfAnnotation::selected() const
{
    return m_selected;
}

void PdfAnnotation::setId(const QString &id)
{
    if (m_id == id) {
        return;
    }
    m_id = id;
    emit changed();
}

void PdfAnnotation::setPageNumber(int page)
{
    if (m_pageNumber == page) {
        return;
    }
    m_pageNumber = page;
    emit changed();
}

void PdfAnnotation::setType(PdfEditorTools::ToolType type)
{
    if (m_type == type) {
        return;
    }
    m_type = type;
    emit changed();
}

void PdfAnnotation::setRect(const QRectF &rect)
{
    if (m_rect == rect) {
        return;
    }
    m_rect = rect;
    emit changed();
}

void PdfAnnotation::setColor(const QColor &color)
{
    if (m_color == color) {
        return;
    }
    m_color = color;
    emit changed();
}

void PdfAnnotation::setContents(const QString &contents)
{
    if (m_contents == contents) {
        return;
    }
    m_contents = contents;
    emit changed();
}

void PdfAnnotation::setAuthor(const QString &author)
{
    if (m_author == author) {
        return;
    }
    m_author = author;
    emit changed();
}

void PdfAnnotation::setCreationDate(const QDateTime &date)
{
    if (m_creationDate == date) {
        return;
    }
    m_creationDate = date;
    emit changed();
}

void PdfAnnotation::setSelected(bool selected)
{
    if (m_selected == selected) {
        return;
    }
    m_selected = selected;
    emit changed();
}

QVariantMap PdfAnnotation::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("id")] = m_id;
    map[QStringLiteral("pageNumber")] = m_pageNumber;
    map[QStringLiteral("type")] = QVariant::fromValue(m_type);
    map[QStringLiteral("x")] = m_rect.x();
    map[QStringLiteral("y")] = m_rect.y();
    map[QStringLiteral("width")] = m_rect.width();
    map[QStringLiteral("height")] = m_rect.height();
    map[QStringLiteral("color")] = m_color.name(QColor::HexArgb);
    map[QStringLiteral("contents")] = m_contents;
    map[QStringLiteral("author")] = m_author;
    map[QStringLiteral("creationDate")] = m_creationDate;
    map[QStringLiteral("selected")] = m_selected;
    return map;
}

PdfAnnotation *PdfAnnotation::fromMap(const QVariantMap &map, QObject *parent)
{
    auto *annotation = new PdfAnnotation(parent);
    annotation->setId(map.value(QStringLiteral("id"), QUuid::createUuid().toString(QUuid::WithoutBraces)).toString());
    annotation->setPageNumber(map.value(QStringLiteral("pageNumber"), 0).toInt());
    annotation->setType(map.value(QStringLiteral("type"), QVariant::fromValue(PdfEditorTools::ToolType::SelectionTool)).value<PdfEditorTools::ToolType>());
    const qreal x = map.value(QStringLiteral("x"), 0.0).toReal();
    const qreal y = map.value(QStringLiteral("y"), 0.0).toReal();
    const qreal w = map.value(QStringLiteral("width"), 0.0).toReal();
    const qreal h = map.value(QStringLiteral("height"), 0.0).toReal();
    annotation->setRect(QRectF(x, y, w, h));
    annotation->setColor(QColor(map.value(QStringLiteral("color"), QStringLiteral("yellow")).toString()));
    annotation->setContents(map.value(QStringLiteral("contents")).toString());
    annotation->setAuthor(map.value(QStringLiteral("author")).toString());
    annotation->setCreationDate(map.value(QStringLiteral("creationDate")).toDateTime());
    annotation->setSelected(map.value(QStringLiteral("selected"), false).toBool());
    return annotation;
}

} // namespace bos::shell
