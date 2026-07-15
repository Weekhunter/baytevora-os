#include "bos/FileSearchManager.h"

#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QRegularExpression>

namespace bos::shell {

FileSearchManager::FileSearchManager(QObject *parent)
    : QObject(parent)
{
}

FileSearchManager::~FileSearchManager() = default;

QVariantList FileSearchManager::search(const QString &directory, const QString &query,
                                       const QString &extensionFilter, bool recursive) const
{
    QVariantList results;
    if (directory.isEmpty() || query.isEmpty()) {
        return results;
    }

    QDir dir(directory);
    if (!dir.exists()) {
        return results;
    }

    searchDirectory(results, directory, query, extensionFilter, recursive);
    return results;
}

QVariantList FileSearchManager::searchFileNames(const QString &directory, const QString &query,
                                               bool recursive) const
{
    return search(directory, query, QString(), recursive);
}

void FileSearchManager::searchDirectory(QVariantList &results, const QString &directory,
                                       const QString &query, const QString &extensionFilter,
                                       bool recursive) const
{
    const QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files;
    const QDir::SortFlags sortFlags = QDir::Name | QDir::IgnoreCase;

    if (recursive) {
        QDirIterator it(directory, filters, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            const QFileInfo info = it.fileInfo();
            const QString name = info.fileName();
            if (!matchesQuery(name, query)) {
                continue;
            }
            if (!matchesExtension(name, extensionFilter)) {
                continue;
            }

            QVariantMap map;
            map.insert(QStringLiteral("name"), name);
            map.insert(QStringLiteral("path"), info.absoluteFilePath());
            map.insert(QStringLiteral("type"), info.isDir() ? QStringLiteral("Folder") : (info.suffix().isEmpty() ? QStringLiteral("File") : info.suffix() + QStringLiteral(" File")));
            map.insert(QStringLiteral("size"), info.isDir() ? QStringLiteral("--") : FileSearchManager::formatSize(info.size()));
            map.insert(QStringLiteral("lastModified"), info.lastModified());
            map.insert(QStringLiteral("isFolder"), info.isDir());
            results.append(map);
        }
        return;
    }

    QDir dir(directory);
    const QFileInfoList entries = dir.entryInfoList(filters, sortFlags);
    for (const QFileInfo &info : entries) {
        const QString name = info.fileName();
        if (!matchesQuery(name, query)) {
            continue;
        }
        if (!matchesExtension(name, extensionFilter)) {
            continue;
        }

        QVariantMap map;
        map.insert(QStringLiteral("name"), name);
        map.insert(QStringLiteral("path"), info.absoluteFilePath());
        map.insert(QStringLiteral("type"), info.isDir() ? QStringLiteral("Folder") : (info.suffix().isEmpty() ? QStringLiteral("File") : info.suffix() + QStringLiteral(" File")));
        map.insert(QStringLiteral("size"), info.isDir() ? QStringLiteral("--") : FileSearchManager::formatSize(info.size()));
        map.insert(QStringLiteral("lastModified"), info.lastModified());
        map.insert(QStringLiteral("isFolder"), info.isDir());
        results.append(map);
    }
}

bool FileSearchManager::matchesQuery(const QString &fileName, const QString &query) const
{
    const QString lowerName = fileName.toLower();
    const QString lowerQuery = query.toLower();
    return lowerName.contains(lowerQuery);
}

bool FileSearchManager::matchesExtension(const QString &fileName, const QString &extensionFilter) const
{
    if (extensionFilter.isEmpty()) {
        return true;
    }
    const QString suffix = QFileInfo(fileName).suffix().toLower();
    const QString filter = extensionFilter.toLower();
    return suffix == filter || fileName.endsWith(QStringLiteral(".") + filter, Qt::CaseInsensitive);
}

QString FileSearchManager::formatSize(qint64 bytes)
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

} // namespace bos::shell
