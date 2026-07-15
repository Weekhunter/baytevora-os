#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QObject>

namespace bos::shell {

class DesktopItem;

/**
 * @brief List model that backs the desktop icon grid.
 *
 * DesktopModel exposes the roles required by QML: name, icon, type,
 * positionX, positionY, selected, and visible. It owns the DesktopItem
 * instances and emits the standard model signals when items change.
 */
class DesktopModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        TypeRole,
        PositionXRole,
        PositionYRole,
        SelectedRole,
        VisibleRole
    };
    Q_ENUM(Roles)

    explicit DesktopModel(QObject *parent = nullptr);
    ~DesktopModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addItem(DesktopItem *item);
    DesktopItem *itemAt(int row) const;
    void clear();

private:
    QList<DesktopItem *> m_items;
};

} // namespace bos::shell
