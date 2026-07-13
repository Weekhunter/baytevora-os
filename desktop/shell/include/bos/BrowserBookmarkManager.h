#pragma once

#include <QList>
#include <QObject>
#include <QStringList>
#include <QVariantList>

namespace bos::shell {

class BrowserBookmark;
class NotificationManager;

/**
 * @brief Manages bookmarks and folders for a browser session.
 *
 * Bookmarks are persisted to a local JSON file under the application's
 * writable data location so they survive browser restarts.
 */
class BrowserBookmarkManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList bookmarks READ bookmarks NOTIFY bookmarksChanged FINAL)
    Q_PROPERTY(QStringList folders READ folders NOTIFY foldersChanged FINAL)

public:
    explicit BrowserBookmarkManager(QObject *parent = nullptr);
    ~BrowserBookmarkManager() override;

    QVariantList bookmarks() const;
    QStringList folders() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int addBookmark(const QString &title, const QString &url,
                                const QString &folder = QString());
    Q_INVOKABLE bool removeBookmark(int bookmarkId);
    Q_INVOKABLE bool editBookmark(int bookmarkId, const QString &title,
                                  const QString &url, const QString &folder);
    Q_INVOKABLE void createFolder(const QString &name);
    Q_INVOKABLE bool moveBookmark(int bookmarkId, const QString &folder);
    Q_INVOKABLE QVariantList searchBookmarks(const QString &query) const;

    Q_INVOKABLE void updateLastVisited(int bookmarkId);

private:
    void load();
    void save();
    QString storageDirectory() const;
    QString storageFilePath() const;
    int generateBookmarkId();
    BrowserBookmark *findBookmark(int bookmarkId) const;
    void emitNotification(const QString &title, const QString &message);
    void rebuildFolders();

    QList<BrowserBookmark*> m_bookmarks;
    QStringList m_folders;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextBookmarkId = 1;
};

} // namespace bos::shell
