#include "bos/RecentFileManager.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/RecentFile.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

RecentFileManager::RecentFileManager(QObject *parent)
    : QObject(parent)
{
    load();
}

RecentFileManager::~RecentFileManager()
{
    qDeleteAll(m_recentFiles);
    m_recentFiles.clear();
}

QVariantList RecentFileManager::recentFiles() const
{
    QVariantList list;
    list.reserve(m_recentFiles.size());
    for (const RecentFile *recent : m_recentFiles) {
        if (!recent) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("recentId"), recent->recentId());
        map.insert(QStringLiteral("fileName"), recent->fileName());
        map.insert(QStringLiteral("path"), recent->path());
        map.insert(QStringLiteral("fileType"), recent->fileType());
        map.insert(QStringLiteral("lastOpened"), recent->lastOpened());
        list.append(map);
    }
    return list;
}

void RecentFileManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void RecentFileManager::addRecentFile(const QString &path)
{
    if (path.isEmpty()) {
        return;
    }

    const QFileInfo info(path);
    if (!info.exists() || info.isDir()) {
        return;
    }

    for (RecentFile *recent : m_recentFiles) {
        if (recent && recent->path() == path) {
            recent->setLastOpened(QDateTime::currentDateTime());
            save();
            emit recentFilesChanged();
            return;
        }
    }

    auto *recent = new RecentFile(generateRecentId(), this);
    recent->setFileName(info.fileName());
    recent->setPath(path);
    recent->setFileType(info.suffix());
    recent->setLastOpened(QDateTime::currentDateTime());
    m_recentFiles.prepend(recent);

    // Keep only the 20 most recent files.
    while (m_recentFiles.size() > 20) {
        RecentFile *old = m_recentFiles.takeLast();
        delete old;
    }

    save();
    emit recentFilesChanged();
}

void RecentFileManager::clearRecentFiles()
{
    qDeleteAll(m_recentFiles);
    m_recentFiles.clear();
    save();
    emit recentFilesChanged();
    emitNotification(QStringLiteral("Recent Files Cleared"),
                   QStringLiteral("The recent files list has been cleared"));
}

void RecentFileManager::load()
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
    const QJsonArray recentArray = root.value(QStringLiteral("recentFiles")).toArray();

    qDeleteAll(m_recentFiles);
    m_recentFiles.clear();

    for (const QJsonValue &value : recentArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("recentId")).toInt(m_nextRecentId);
        if (id >= m_nextRecentId) {
            m_nextRecentId = id + 1;
        }

        auto *recent = new RecentFile(id, this);
        recent->setFileName(obj.value(QStringLiteral("fileName")).toString());
        recent->setPath(obj.value(QStringLiteral("path")).toString());
        recent->setFileType(obj.value(QStringLiteral("fileType")).toString());
        recent->setLastOpened(QDateTime::fromString(obj.value(QStringLiteral("lastOpened")).toString(), Qt::ISODate));
        m_recentFiles.append(recent);
    }
}

void RecentFileManager::save()
{
    QJsonArray recentArray;
    for (const RecentFile *recent : m_recentFiles) {
        if (!recent) {
            continue;
        }
        QJsonObject obj;
        obj.insert(QStringLiteral("recentId"), recent->recentId());
        obj.insert(QStringLiteral("fileName"), recent->fileName());
        obj.insert(QStringLiteral("path"), recent->path());
        obj.insert(QStringLiteral("fileType"), recent->fileType());
        obj.insert(QStringLiteral("lastOpened"), recent->lastOpened().toString(Qt::ISODate));
        recentArray.append(obj);
    }

    QJsonObject root;
    root.insert(QStringLiteral("recentFiles"), recentArray);

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

int RecentFileManager::generateRecentId()
{
    return m_nextRecentId++;
}

void RecentFileManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("File Manager"),
                                              QStringLiteral("info"));
}

QString RecentFileManager::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/filemanager");
}

QString RecentFileManager::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/recent.json");
}

} // namespace bos::shell
