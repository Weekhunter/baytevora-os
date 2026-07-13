#include "bos/FileSystemModel.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLocale>
#include <QStandardPaths>

#include "bos/FileFavoriteManager.h"
#include "bos/RecentFileManager.h"
#include "bos/FileSearchManager.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

FileSystemModel::FileSystemModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_favoriteManager(new FileFavoriteManager(this))
    , m_recentFileManager(new RecentFileManager(this))
    , m_searchManager(new FileSearchManager(this))
{
}

FileSystemModel::~FileSystemModel() = default;

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_entries.size();
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_entries.size()) {
        return {};
    }

    const FileSystemEntry &entry = m_entries.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return entry.name;
    case TypeRole:
        return entry.type;
    case SizeRole:
        return entry.isFolder ? QStringLiteral("--") : formatSize(entry.size);
    case LastModifiedRole:
        return entry.lastModified;
    case IsFolderRole:
        return entry.isFolder;
    default:
        return {};
    }
}

QHash<int, QByteArray> FileSystemModel::roleNames() const
{
    return {
        {NameRole, "name"},
        {TypeRole, "type"},
        {SizeRole, "size"},
        {LastModifiedRole, "lastModified"},
        {IsFolderRole, "isFolder"}
    };
}

QString FileSystemModel::path() const
{
    return m_path;
}

void FileSystemModel::setPath(const QString &path)
{
    if (m_path == path) {
        return;
    }

    m_path = path;
    loadDirectory();

    if (!m_navigatingHistory) {
        updateHistory();
    }

    emit pathChanged();
    emit itemCountChanged();
    emit currentFolderNameChanged();
    emit canGoBackChanged();
    emit canGoForwardChanged();
}

int FileSystemModel::itemCount() const
{
    return m_entries.size();
}

QString FileSystemModel::currentFolderName() const
{
    if (m_path.isEmpty()) {
        return {};
    }

    const QString cleanPath = QDir::cleanPath(m_path);
    const QDir dir(cleanPath);
    return dir.dirName();
}

bool FileSystemModel::canGoBack() const
{
    return m_historyIndex > 0;
}

bool FileSystemModel::canGoForward() const
{
    return m_historyIndex >= 0 && m_historyIndex < m_history.size() - 1;
}

FileFavoriteManager *FileSystemModel::favoriteManager() const
{
    return m_favoriteManager;
}

RecentFileManager *FileSystemModel::recentFileManager() const
{
    return m_recentFileManager;
}

FileSearchManager *FileSystemModel::searchManager() const
{
    return m_searchManager;
}

void FileSystemModel::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
    if (m_favoriteManager) {
        m_favoriteManager->setNotificationManager(notificationManager);
    }
    if (m_recentFileManager) {
        m_recentFileManager->setNotificationManager(notificationManager);
    }
}

void FileSystemModel::refresh()
{
    qDebug() << QStringLiteral("[BDE] Refresh requested");
    loadDirectory();
    emit itemCountChanged();
    emit currentFolderNameChanged();
}

QStringList FileSystemModel::fileNames() const
{
    QStringList names;
    names.reserve(m_entries.size());
    for (const FileSystemEntry &entry : m_entries) {
        names.append(entry.name);
    }
    return names;
}

void FileSystemModel::cdUp()
{
    QDir dir(m_path);
    if (!dir.cdUp()) {
        return;
    }

    setPath(dir.absolutePath());
    qDebug() << QStringLiteral("[BDE] Folder entered");
}

void FileSystemModel::goBack()
{
    if (!canGoBack()) {
        return;
    }

    --m_historyIndex;
    const QString target = m_history.at(m_historyIndex);

    m_navigatingHistory = true;
    setPath(target);
    m_navigatingHistory = false;
}

void FileSystemModel::goForward()
{
    if (!canGoForward()) {
        return;
    }

    ++m_historyIndex;
    const QString target = m_history.at(m_historyIndex);

    m_navigatingHistory = true;
    setPath(target);
    m_navigatingHistory = false;
}

void FileSystemModel::goHome()
{
    const QString home = homeDirectory();
    if (!home.isEmpty()) {
        setPath(home);
    }
}

void FileSystemModel::addRecentFile(const QString &filePath)
{
    if (!m_recentFileManager || filePath.isEmpty()) {
        return;
    }
    m_recentFileManager->addRecentFile(filePath);
}

QString FileSystemModel::formatSize(qint64 bytes)
{
    static const QStringList units = {
        QStringLiteral("B"),
        QStringLiteral("KB"),
        QStringLiteral("MB"),
        QStringLiteral("GB"),
        QStringLiteral("TB")
    };

    if (bytes < 0) {
        return QStringLiteral("--");
    }

    int unitIndex = 0;
    double size = static_cast<double>(bytes);
    while (size >= 1024.0 && unitIndex < units.size() - 1) {
        size /= 1024.0;
        ++unitIndex;
    }

    return QStringLiteral("%1 %2").arg(size, 0, 'f', unitIndex > 0 ? 1 : 0).arg(units.at(unitIndex));
}

void FileSystemModel::loadDirectory()
{
    beginResetModel();
    m_entries.clear();

    QDir dir(m_path);
    if (!dir.exists()) {
        endResetModel();
        return;
    }

    const QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files,
                                                    QDir::Name | QDir::IgnoreCase);
    m_entries.reserve(entries.size());

    // Collect folders first to ensure they appear before files.
    for (const QFileInfo &info : entries) {
        if (info.isDir()) {
            m_entries.append({info.fileName(),
                              QStringLiteral("Folder"),
                              0,
                              info.lastModified(),
                              true});
        }
    }

    for (const QFileInfo &info : entries) {
        if (info.isFile()) {
            const QString suffix = info.suffix();
            const QString type = suffix.isEmpty() ? QStringLiteral("File")
                                                  : suffix + QStringLiteral(" File");
            m_entries.append({info.fileName(), type, info.size(), info.lastModified(), false});
        }
    }

    endResetModel();
    qDebug() << QStringLiteral("[BDE] Directory opened");
}

void FileSystemModel::updateHistory()
{
    if (m_historyIndex >= 0 && m_historyIndex < m_history.size() - 1) {
        // Remove forward entries when a new path is set.
        m_history = m_history.mid(0, m_historyIndex + 1);
    }

    if (m_history.isEmpty() || m_history.last() != m_path) {
        m_history.append(m_path);
        m_historyIndex = m_history.size() - 1;
    }
}

void FileSystemModel::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("File Manager"),
                                              QStringLiteral("info"));
}

QString FileSystemModel::homeDirectory() const
{
    const QStringList locations = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    return locations.isEmpty() ? QString() : locations.first();
}

} // namespace bos::shell
