#include "bos/FileFavoriteManager.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/FavoriteLocation.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

FileFavoriteManager::FileFavoriteManager(QObject *parent)
    : QObject(parent)
{
    load();
}

FileFavoriteManager::~FileFavoriteManager()
{
    qDeleteAll(m_favorites);
    m_favorites.clear();
}

QVariantList FileFavoriteManager::favorites() const
{
    QVariantList list;
    list.reserve(m_favorites.size());
    for (const FavoriteLocation *favorite : m_favorites) {
        if (!favorite) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("favoriteId"), favorite->favoriteId());
        map.insert(QStringLiteral("displayName"), favorite->displayName());
        map.insert(QStringLiteral("path"), favorite->path());
        map.insert(QStringLiteral("icon"), favorite->icon());
        map.insert(QStringLiteral("pinned"), favorite->pinned());
        list.append(map);
    }
    return list;
}

void FileFavoriteManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void FileFavoriteManager::addFavorite(const QString &path, const QString &displayName,
                                     const QString &icon, bool pinned)
{
    if (path.isEmpty()) {
        return;
    }
    const QFileInfo info(path);
    const QString actualName = displayName.isEmpty() ? info.fileName() : displayName;

    auto *favorite = new FavoriteLocation(generateFavoriteId(), this);
    favorite->setPath(path);
    favorite->setDisplayName(actualName);
    favorite->setIcon(icon);
    favorite->setPinned(pinned);

    m_favorites.append(favorite);
    save();
    emit favoritesChanged();
    emitNotification(QStringLiteral("Favorite Added"),
                   QStringLiteral("%1 added to favorites").arg(actualName));
}

void FileFavoriteManager::removeFavorite(int favoriteId)
{
    FavoriteLocation *favorite = findById(favoriteId);
    if (!favorite) {
        return;
    }
    const QString name = favorite->displayName();
    m_favorites.removeOne(favorite);
    delete favorite;
    save();
    emit favoritesChanged();
    emitNotification(QStringLiteral("Favorite Removed"),
                   QStringLiteral("%1 removed from favorites").arg(name));
}

void FileFavoriteManager::pinFavorite(int favoriteId, bool pinned)
{
    FavoriteLocation *favorite = findById(favoriteId);
    if (!favorite || favorite->pinned() == pinned) {
        return;
    }
    favorite->setPinned(pinned);
    save();
    emit favoritesChanged();
}

void FileFavoriteManager::moveFavorite(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex >= m_favorites.size()) {
        return;
    }
    if (toIndex < 0 || toIndex >= m_favorites.size()) {
        return;
    }
    if (fromIndex == toIndex) {
        return;
    }
    m_favorites.move(fromIndex, toIndex);
    save();
    emit favoritesChanged();
}

void FileFavoriteManager::togglePin(int favoriteId)
{
    FavoriteLocation *favorite = findById(favoriteId);
    if (!favorite) {
        return;
    }
    favorite->setPinned(!favorite->pinned());
    save();
    emit favoritesChanged();
}

void FileFavoriteManager::load()
{
    const QString path = storageFilePath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    const QByteArray data = file.readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        return;
    }

    const QJsonObject root = doc.object();
    const QJsonArray favoritesArray = root.value(QStringLiteral("favorites")).toArray();

    qDeleteAll(m_favorites);
    m_favorites.clear();

    for (const QJsonValue &value : favoritesArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("favoriteId")).toInt(m_nextFavoriteId);
        if (id >= m_nextFavoriteId) {
            m_nextFavoriteId = id + 1;
        }

        auto *favorite = new FavoriteLocation(id, this);
        favorite->setDisplayName(obj.value(QStringLiteral("displayName")).toString());
        favorite->setPath(obj.value(QStringLiteral("path")).toString());
        favorite->setIcon(obj.value(QStringLiteral("icon")).toString());
        favorite->setPinned(obj.value(QStringLiteral("pinned")).toBool(false));
        m_favorites.append(favorite);
    }
}

void FileFavoriteManager::save()
{
    QJsonArray favoritesArray;
    for (const FavoriteLocation *favorite : m_favorites) {
        if (!favorite) {
            continue;
        }
        QJsonObject obj;
        obj.insert(QStringLiteral("favoriteId"), favorite->favoriteId());
        obj.insert(QStringLiteral("displayName"), favorite->displayName());
        obj.insert(QStringLiteral("path"), favorite->path());
        obj.insert(QStringLiteral("icon"), favorite->icon());
        obj.insert(QStringLiteral("pinned"), favorite->pinned());
        favoritesArray.append(obj);
    }

    QJsonObject root;
    root.insert(QStringLiteral("favorites"), favoritesArray);

    const QString path = storageFilePath();
    QDir dir(storageDirectory());
    if (!dir.exists()) {
        dir.mkpath(QStringLiteral("."));
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
}

int FileFavoriteManager::generateFavoriteId()
{
    return m_nextFavoriteId++;
}

FavoriteLocation *FileFavoriteManager::findById(int favoriteId) const
{
    for (FavoriteLocation *favorite : m_favorites) {
        if (favorite && favorite->favoriteId() == favoriteId) {
            return favorite;
        }
    }
    return nullptr;
}

void FileFavoriteManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("File Manager"),
                                              QStringLiteral("info"));
}

QString FileFavoriteManager::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/filemanager");
}

QString FileFavoriteManager::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/favorites.json");
}

} // namespace bos::shell
