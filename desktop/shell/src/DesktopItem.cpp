#include "bos/DesktopItem.h"

namespace bos::shell {

DesktopItem::DesktopItem(int itemId, const QString &name, const QString &icon,
                         const QString &type, int x, int y, QObject *parent)
    : QObject(parent)
    , m_itemId(itemId)
    , m_name(name)
    , m_icon(icon)
    , m_type(type)
    , m_positionX(x)
    , m_positionY(y)
    , m_selected(false)
    , m_visible(true)
{
}

DesktopItem::~DesktopItem() = default;

int DesktopItem::itemId() const
{
    return m_itemId;
}

QString DesktopItem::name() const
{
    return m_name;
}

void DesktopItem::setName(const QString &name)
{
    if (m_name == name) {
        return;
    }
    m_name = name;
    emit nameChanged();
}

QString DesktopItem::icon() const
{
    return m_icon;
}

void DesktopItem::setIcon(const QString &icon)
{
    if (m_icon == icon) {
        return;
    }
    m_icon = icon;
    emit iconChanged();
}

QString DesktopItem::type() const
{
    return m_type;
}

void DesktopItem::setType(const QString &type)
{
    if (m_type == type) {
        return;
    }
    m_type = type;
    emit typeChanged();
}

int DesktopItem::positionX() const
{
    return m_positionX;
}

void DesktopItem::setPositionX(int x)
{
    if (m_positionX == x) {
        return;
    }
    m_positionX = x;
    emit positionXChanged();
}

int DesktopItem::positionY() const
{
    return m_positionY;
}

void DesktopItem::setPositionY(int y)
{
    if (m_positionY == y) {
        return;
    }
    m_positionY = y;
    emit positionYChanged();
}

bool DesktopItem::selected() const
{
    return m_selected;
}

void DesktopItem::setSelected(bool selected)
{
    if (m_selected == selected) {
        return;
    }
    m_selected = selected;
    emit selectedChanged();
}

bool DesktopItem::visible() const
{
    return m_visible;
}

void DesktopItem::setVisible(bool visible)
{
    if (m_visible == visible) {
        return;
    }
    m_visible = visible;
    emit visibleChanged();
}

} // namespace bos::shell
