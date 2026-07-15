#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single favorite location entry in the File Manager.
 */
class FavoriteLocation : public QObject {
    Q_OBJECT

    Q_PROPERTY(int favoriteId READ favoriteId NOTIFY favoriteIdChanged FINAL)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged FINAL)
    Q_PROPERTY(QString path READ path NOTIFY pathChanged FINAL)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged FINAL)
    Q_PROPERTY(bool pinned READ pinned NOTIFY pinnedChanged FINAL)

public:
    explicit FavoriteLocation(int favoriteId, QObject *parent = nullptr);
    ~FavoriteLocation() override;

    int favoriteId() const;
    QString displayName() const;
    QString path() const;
    QString icon() const;
    bool pinned() const;

    void setDisplayName(const QString &displayName);
    void setPath(const QString &path);
    void setIcon(const QString &icon);
    void setPinned(bool pinned);

signals:
    void favoriteIdChanged();
    void displayNameChanged();
    void pathChanged();
    void iconChanged();
    void pinnedChanged();

private:
    int m_favoriteId = -1;
    QString m_displayName;
    QString m_path;
    QString m_icon;
    bool m_pinned = false;
};

} // namespace bos::shell
