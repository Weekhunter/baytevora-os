#include "bos/ClipboardItem.h"

namespace bos::shell {

ClipboardItem::ClipboardItem(int itemId, const QString &text, const QString &type,
                             const QDateTime &timestamp, QObject *parent)
    : QObject(parent)
    , m_itemId(itemId)
    , m_text(text)
    , m_type(type)
    , m_timestamp(timestamp)
{
}

ClipboardItem::~ClipboardItem() = default;

int ClipboardItem::itemId() const
{
    return m_itemId;
}

QString ClipboardItem::text() const
{
    return m_text;
}

QString ClipboardItem::type() const
{
    return m_type;
}

QDateTime ClipboardItem::timestamp() const
{
    return m_timestamp;
}

} // namespace bos::shell
