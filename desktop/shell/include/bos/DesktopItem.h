#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Data model for a single desktop icon.
 *
 * DesktopItem holds the metadata for one icon on the desktop surface. It does
 * not integrate with the filesystem; it only stores identity, display name,
 * icon identifier, type, position, selection state, and visibility.
 */
class DesktopItem : public QObject {
    Q_OBJECT

    Q_PROPERTY(int itemId READ itemId CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int positionX READ positionX WRITE setPositionX NOTIFY positionXChanged)
    Q_PROPERTY(int positionY READ positionY WRITE setPositionY NOTIFY positionYChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit DesktopItem(int itemId, const QString &name, const QString &icon,
                         const QString &type, int x, int y, QObject *parent = nullptr);
    ~DesktopItem() override;

    int itemId() const;
    QString name() const;
    void setName(const QString &name);
    QString icon() const;
    void setIcon(const QString &icon);
    QString type() const;
    void setType(const QString &type);
    int positionX() const;
    void setPositionX(int x);
    int positionY() const;
    void setPositionY(int y);
    bool selected() const;
    void setSelected(bool selected);
    bool visible() const;
    void setVisible(bool visible);

signals:
    void nameChanged();
    void iconChanged();
    void typeChanged();
    void positionXChanged();
    void positionYChanged();
    void selectedChanged();
    void visibleChanged();

private:
    int m_itemId;
    QString m_name;
    QString m_icon;
    QString m_type;
    int m_positionX;
    int m_positionY;
    bool m_selected;
    bool m_visible;
};

} // namespace bos::shell
