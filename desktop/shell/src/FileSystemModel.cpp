#include "bos/FileSystemModel.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLocale>

namespace bos::shell {

FileSystemModel::FileSystemModel(QObject *parent)
    : QAbstractListModel(parent)
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

    emit pathChanged();
    emit itemCountChanged();
    emit currentFolderNameChanged();
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

} // namespace bos::shell
