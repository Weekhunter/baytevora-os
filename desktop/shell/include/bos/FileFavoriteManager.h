#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class FavoriteLocation;
class NotificationManager;

/**
 * @brief Manages favorite locations for the File Manager with local JSON persistence.
 */
class FileFavoriteManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList favorites READ favorites NOTIFY favoritesChanged FINAL)

public:
    explicit FileFavoriteManager(QObject *parent = nullptr);
    ~FileFavoriteManager() override;

    QVariantList favorites() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE void addFavorite(const QString &path, const QString &displayName,
                                const QString &icon = QString(), bool pinned = false);
    Q_INVOKABLE void removeFavorite(int favoriteId);
    Q_INVOKABLE void pinFavorite(int favoriteId, bool pinned);
    Q_INVOKABLE void moveFavorite(int fromIndex, int toIndex);
    Q_INVOKABLE void togglePin(int favoriteId);

private:
    void load();
    void save();
    int generateFavoriteId();
    FavoriteLocation *findById(int favoriteId) const;
    void emitNotification(const QString &title, const QString &message);
    QString storageDirectory() const;
    QString storageFilePath() const;

    QList<FavoriteLocation*> m_favorites;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextFavoriteId = 1;
};

} // namespace bos::shell
