#include "bos/DesktopModel.h"

#include "bos/DesktopItem.h"

namespace bos::shell {

DesktopModel::DesktopModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

DesktopModel::~DesktopModel()
{
    qDeleteAll(m_items);
}

int DesktopModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_items.size();
}

QVariant DesktopModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size()) {
        return QVariant();
    }

    const DesktopItem *item = m_items.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return item->name();
    case IconRole:
        return item->icon();
    case TypeRole:
        return item->type();
    case PositionXRole:
        return item->positionX();
    case PositionYRole:
        return item->positionY();
    case SelectedRole:
        return item->selected();
    case VisibleRole:
        return item->visible();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DesktopModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[TypeRole] = "type";
    roles[PositionXRole] = "positionX";
    roles[PositionYRole] = "positionY";
    roles[SelectedRole] = "selected";
    roles[VisibleRole] = "visible";
    return roles;
}

void DesktopModel::addItem(DesktopItem *item)
{
    if (!item) {
        return;
    }

    const int row = m_items.size();
    beginInsertRows(QModelIndex(), row, row);
    m_items.append(item);
    item->setParent(this);
    endInsertRows();
}

DesktopItem *DesktopModel::itemAt(int row) const
{
    if (row < 0 || row >= m_items.size()) {
        return nullptr;
    }
    return m_items.at(row);
}

void DesktopModel::clear()
{
    if (m_items.isEmpty()) {
        return;
    }

    beginResetModel();
    qDeleteAll(m_items);
    m_items.clear();
    endResetModel();
}

} // namespace bos::shell
