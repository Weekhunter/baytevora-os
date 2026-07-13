#pragma once

#include <QAbstractListModel>
#include <QDateTime>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QStringList>

namespace bos::shell {

struct FileSystemEntry;
class FileFavoriteManager;
class RecentFileManager;
class FileSearchManager;
class NotificationManager;

/**
 * @brief Lightweight model representing a single file or folder entry.
 *
 * FileSystemEntry holds the data required by the File Manager list view.
 * It does not perform any I/O itself; FileSystemModel populates entries.
 */
struct FileSystemEntry {
    QString name;
    QString type;
    qint64 size = 0;
    QDateTime lastModified;
    bool isFolder = false;
};

/**
 * @brief Model exposing a directory listing for use by QML views.
 *
 * FileSystemModel is a QAbstractListModel that reads the current directory
 * using Qt's filesystem APIs. It exposes Name, Type, Size, LastModified, and
 * IsFolder roles. Hidden files are omitted, and folders are listed before files.
 *
 * The current directory is set from QML via the `path` property. Setting an
 * invalid or non-existent path leaves the model empty without raising errors.
 *
 * In Sprint 45 the model also owns a per-window navigation history,
 * FileFavoriteManager, RecentFileManager, and FileSearchManager for
 * Favorites, Recent Files, and in-session search.
 */
class FileSystemModel : public QAbstractListModel {
    Q_OBJECT

    /**
     * @brief Current directory path. Setting this reloads the model and records
     *        the previous path in the navigation history.
     */
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

    /**
     * @brief Number of items in the current directory.
     */
    Q_PROPERTY(int itemCount READ itemCount NOTIFY itemCountChanged)

    /**
     * @brief The name of the current folder (empty string for the root).
     */
    Q_PROPERTY(QString currentFolderName READ currentFolderName NOTIFY currentFolderNameChanged)

    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY canGoForwardChanged)
    Q_PROPERTY(FileFavoriteManager *favoriteManager READ favoriteManager CONSTANT FINAL)
    Q_PROPERTY(RecentFileManager *recentFileManager READ recentFileManager CONSTANT FINAL)
    Q_PROPERTY(FileSearchManager *searchManager READ searchManager CONSTANT FINAL)

public:
    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        SizeRole,
        LastModifiedRole,
        IsFolderRole
    };
    Q_ENUM(FileRoles)

    explicit FileSystemModel(QObject *parent = nullptr);
    ~FileSystemModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QString path() const;
    void setPath(const QString &path);

    int itemCount() const;
    QString currentFolderName() const;

    bool canGoBack() const;
    bool canGoForward() const;

    FileFavoriteManager *favoriteManager() const;
    RecentFileManager *recentFileManager() const;
    FileSearchManager *searchManager() const;

    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Reloads the current directory contents.
     */
    Q_INVOKABLE void refresh();

    /**
     * @brief Returns the names of all visible entries in the current directory.
     */
    Q_INVOKABLE QStringList fileNames() const;

    /**
     * @brief Moves up one directory level.
     *
     * If the current path is already the root, the path is unchanged.
     */
    Q_INVOKABLE void cdUp();

    /**
     * @brief Navigates back in the per-window navigation history.
     */
    Q_INVOKABLE void goBack();

    /**
     * @brief Navigates forward in the per-window navigation history.
     */
    Q_INVOKABLE void goForward();

    /**
     * @brief Navigates to the user's home directory.
     */
    Q_INVOKABLE void goHome();

    /**
     * @brief Adds the current file path to the Recent Files list.
     */
    Q_INVOKABLE void addRecentFile(const QString &filePath);

    /**
     * @return The size string formatted for display.
     */
    static QString formatSize(qint64 bytes);

signals:
    void pathChanged();
    void itemCountChanged();
    void currentFolderNameChanged();
    void canGoBackChanged();
    void canGoForwardChanged();

private:
    void loadDirectory();
    void updateHistory();
    void emitNotification(const QString &title, const QString &message);
    QString homeDirectory() const;

    QString m_path;
    QList<FileSystemEntry> m_entries;

    QStringList m_history;
    int m_historyIndex = -1;
    bool m_navigatingHistory = false;

    FileFavoriteManager *m_favoriteManager = nullptr;
    RecentFileManager *m_recentFileManager = nullptr;
    FileSearchManager *m_searchManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
