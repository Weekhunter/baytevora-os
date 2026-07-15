#include "bos/BrowserBookmarkManager.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/BrowserBookmark.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserBookmarkManager::BrowserBookmarkManager(QObject *parent)
    : QObject(parent)
{
    load();
}

BrowserBookmarkManager::~BrowserBookmarkManager()
{
    qDeleteAll(m_bookmarks);
    m_bookmarks.clear();
}

QVariantList BrowserBookmarkManager::bookmarks() const
{
    QVariantList list;
    list.reserve(m_bookmarks.size());
    for (const BrowserBookmark *bookmark : m_bookmarks) {
        if (!bookmark) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("bookmarkId"), bookmark->bookmarkId());
        map.insert(QStringLiteral("title"), bookmark->title());
        map.insert(QStringLiteral("url"), bookmark->url());
        map.insert(QStringLiteral("folder"), bookmark->folder());
        map.insert(QStringLiteral("createdAt"), bookmark->createdAt());
        map.insert(QStringLiteral("lastVisited"), bookmark->lastVisited());
        list.append(map);
    }
    return list;
}

QStringList BrowserBookmarkManager::folders() const
{
    return m_folders;
}

void BrowserBookmarkManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int BrowserBookmarkManager::addBookmark(const QString &title, const QString &url,
                                       const QString &folder)
{
    if (title.isEmpty() || url.isEmpty()) {
        return -1;
    }

    const int id = generateBookmarkId();
    auto *bookmark = new BrowserBookmark(id, this);
    bookmark->setTitle(title);
    bookmark->setUrl(url);
    bookmark->setFolder(folder.isEmpty() ? QStringLiteral("Bookmarks") : folder);
    bookmark->setCreatedAt(QDateTime::currentDateTime());
    bookmark->setLastVisited(QDateTime::currentDateTime());
    m_bookmarks.append(bookmark);

    rebuildFolders();
    save();
    emit bookmarksChanged();
    emit foldersChanged();

    emitNotification(QStringLiteral("Bookmark Added"),
                   QStringLiteral("%1 added to bookmarks").arg(title));
    return id;
}

bool BrowserBookmarkManager::removeBookmark(int bookmarkId)
{
    BrowserBookmark *bookmark = findBookmark(bookmarkId);
    if (!bookmark) {
        return false;
    }
    m_bookmarks.removeOne(bookmark);
    delete bookmark;

    rebuildFolders();
    save();
    emit bookmarksChanged();
    emit foldersChanged();

    emitNotification(QStringLiteral("Bookmark Removed"),
                   QStringLiteral("Bookmark removed"));
    return true;
}

bool BrowserBookmarkManager::editBookmark(int bookmarkId, const QString &title,
                                         const QString &url, const QString &folder)
{
    BrowserBookmark *bookmark = findBookmark(bookmarkId);
    if (!bookmark) {
        return false;
    }
    bookmark->setTitle(title);
    bookmark->setUrl(url);
    bookmark->setFolder(folder);
    rebuildFolders();
    save();
    emit bookmarksChanged();
    emit foldersChanged();
    return true;
}

void BrowserBookmarkManager::createFolder(const QString &name)
{
    if (name.isEmpty() || m_folders.contains(name)) {
        return;
    }
    m_folders.append(name);
    emit foldersChanged();
}

bool BrowserBookmarkManager::moveBookmark(int bookmarkId, const QString &folder)
{
    BrowserBookmark *bookmark = findBookmark(bookmarkId);
    if (!bookmark) {
        return false;
    }
    bookmark->setFolder(folder);
    createFolder(folder);
    save();
    emit bookmarksChanged();
    return true;
}

QVariantList BrowserBookmarkManager::searchBookmarks(const QString &query) const
{
    const QString lowerQuery = query.toLowerCase();
    QVariantList list;
    for (const BrowserBookmark *bookmark : m_bookmarks) {
        if (!bookmark) {
            continue;
        }
        if (!query.isEmpty()
            && !bookmark->title().toLowerCase().contains(lowerQuery)
            && !bookmark->url().toLowerCase().contains(lowerQuery)
            && !bookmark->folder().toLowerCase().contains(lowerQuery)) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("bookmarkId"), bookmark->bookmarkId());
        map.insert(QStringLiteral("title"), bookmark->title());
        map.insert(QStringLiteral("url"), bookmark->url());
        map.insert(QStringLiteral("folder"), bookmark->folder());
        map.insert(QStringLiteral("createdAt"), bookmark->createdAt());
        map.insert(QStringLiteral("lastVisited"), bookmark->lastVisited());
        list.append(map);
    }
    return list;
}

void BrowserBookmarkManager::updateLastVisited(int bookmarkId)
{
    BrowserBookmark *bookmark = findBookmark(bookmarkId);
    if (!bookmark) {
        return;
    }
    bookmark->setLastVisited(QDateTime::currentDateTime());
    save();
    emit bookmarksChanged();
}

void BrowserBookmarkManager::load()
{
    const QString path = storageFilePath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        // First run: seed the default folder.
        createFolder(QStringLiteral("Bookmarks"));
        return;
    }

    const QByteArray data = file.readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        createFolder(QStringLiteral("Bookmarks"));
        return;
    }

    const QJsonObject root = doc.object();
    const QJsonArray bookmarksArray = root.value(QStringLiteral("bookmarks")).toArray();
    const QJsonArray foldersArray = root.value(QStringLiteral("folders")).toArray();

    qDeleteAll(m_bookmarks);
    m_bookmarks.clear();
    m_folders.clear();

    for (const QJsonValue &value : foldersArray) {
        const QString name = value.toString();
        if (!name.isEmpty() && !m_folders.contains(name)) {
            m_folders.append(name);
        }
    }
    if (m_folders.isEmpty()) {
        m_folders.append(QStringLiteral("Bookmarks"));
    }

    for (const QJsonValue &value : bookmarksArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("bookmarkId")).toInt(m_nextBookmarkId);
        if (id >= m_nextBookmarkId) {
            m_nextBookmarkId = id + 1;
        }

        auto *bookmark = new BrowserBookmark(id, this);
        bookmark->setTitle(obj.value(QStringLiteral("title")).toString());
        bookmark->setUrl(obj.value(QStringLiteral("url")).toString());
        bookmark->setFolder(obj.value(QStringLiteral("folder")).toString(QStringLiteral("Bookmarks")));
        bookmark->setCreatedAt(QDateTime::fromString(obj.value(QStringLiteral("createdAt")).toString(), Qt::ISODate));
        bookmark->setLastVisited(QDateTime::fromString(obj.value(QStringLiteral("lastVisited")).toString(), Qt::ISODate));
        m_bookmarks.append(bookmark);
    }
}

void BrowserBookmarkManager::save()
{
    QJsonArray bookmarksArray;
    for (const BrowserBookmark *bookmark : m_bookmarks) {
        if (!bookmark) {
            continue;
        }
        QJsonObject obj;
        obj.insert(QStringLiteral("bookmarkId"), bookmark->bookmarkId());
        obj.insert(QStringLiteral("title"), bookmark->title());
        obj.insert(QStringLiteral("url"), bookmark->url());
        obj.insert(QStringLiteral("folder"), bookmark->folder());
        obj.insert(QStringLiteral("createdAt"), bookmark->createdAt().toString(Qt::ISODate));
        obj.insert(QStringLiteral("lastVisited"), bookmark->lastVisited().toString(Qt::ISODate));
        bookmarksArray.append(obj);
    }

    QJsonArray foldersArray;
    for (const QString &folder : m_folders) {
        foldersArray.append(folder);
    }

    QJsonObject root;
    root.insert(QStringLiteral("bookmarks"), bookmarksArray);
    root.insert(QStringLiteral("folders"), foldersArray);

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

QString BrowserBookmarkManager::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/browser");
}

QString BrowserBookmarkManager::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/bookmarks.json");
}

int BrowserBookmarkManager::generateBookmarkId()
{
    return m_nextBookmarkId++;
}

BrowserBookmark *BrowserBookmarkManager::findBookmark(int bookmarkId) const
{
    for (BrowserBookmark *bookmark : m_bookmarks) {
        if (bookmark && bookmark->bookmarkId() == bookmarkId) {
            return bookmark;
        }
    }
    return nullptr;
}

void BrowserBookmarkManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Browser"),
                                              QStringLiteral("info"));
}

void BrowserBookmarkManager::rebuildFolders()
{
    for (const BrowserBookmark *bookmark : m_bookmarks) {
        if (!bookmark || bookmark->folder().isEmpty()) {
            continue;
        }
        if (!m_folders.contains(bookmark->folder())) {
            m_folders.append(bookmark->folder());
        }
    }
}

} // namespace bos::shell
