#include "bos/BrowserHistoryManager.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QUrl>

#include "bos/BrowserHistoryEntry.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserHistoryManager::BrowserHistoryManager(QObject *parent)
    : QObject(parent)
{
    load();
}

BrowserHistoryManager::~BrowserHistoryManager()
{
    qDeleteAll(m_history);
    m_history.clear();
}

QVariantList BrowserHistoryManager::history() const
{
    QVariantList list;
    list.reserve(m_history.size());
    for (const BrowserHistoryEntry *entry : m_history) {
        if (!entry) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("historyId"), entry->historyId());
        map.insert(QStringLiteral("title"), entry->title());
        map.insert(QStringLiteral("url"), entry->url());
        map.insert(QStringLiteral("visitTime"), entry->visitTime());
        map.insert(QStringLiteral("visitCount"), entry->visitCount());
        list.append(map);
    }
    return list;
}

QVariantList BrowserHistoryManager::recentHistory() const
{
    QVariantList list;
    const int limit = 50;
    for (int i = m_history.size() - 1; i >= 0 && list.size() < limit; --i) {
        const BrowserHistoryEntry *entry = m_history.at(i);
        if (!entry) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("historyId"), entry->historyId());
        map.insert(QStringLiteral("title"), entry->title());
        map.insert(QStringLiteral("url"), entry->url());
        map.insert(QStringLiteral("visitTime"), entry->visitTime());
        map.insert(QStringLiteral("visitCount"), entry->visitCount());
        list.append(map);
    }
    return list;
}

void BrowserHistoryManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void BrowserHistoryManager::recordVisit(const QString &title, const QString &url)
{
    if (url.isEmpty() || !shouldRecord(url)) {
        return;
    }

    BrowserHistoryEntry *entry = findEntry(url);
    if (entry) {
        entry->setTitle(title.isEmpty() ? entry->title() : title);
        entry->setVisitTime(QDateTime::currentDateTime());
        entry->incrementVisitCount();
    } else {
        const int id = generateHistoryId();
        entry = new BrowserHistoryEntry(id, this);
        entry->setTitle(title);
        entry->setUrl(url);
        entry->setVisitTime(QDateTime::currentDateTime());
        entry->setVisitCount(1);
        m_history.append(entry);
    }

    save();
    emit historyChanged();
}

void BrowserHistoryManager::clearHistory()
{
    qDeleteAll(m_history);
    m_history.clear();
    save();
    emit historyChanged();

    emitNotification(QStringLiteral("History Cleared"),
                   QStringLiteral("Browsing history has been cleared"));
}

bool BrowserHistoryManager::removeHistoryEntry(int historyId)
{
    BrowserHistoryEntry *entry = findEntryById(historyId);
    if (!entry) {
        return false;
    }
    m_history.removeOne(entry);
    delete entry;
    save();
    emit historyChanged();
    return true;
}

QVariantList BrowserHistoryManager::searchHistory(const QString &query) const
{
    const QString lowerQuery = query.toLowerCase();
    QVariantList list;
    for (const BrowserHistoryEntry *entry : m_history) {
        if (!entry) {
            continue;
        }
        if (!query.isEmpty()
            && !entry->title().toLowerCase().contains(lowerQuery)
            && !entry->url().toLowerCase().contains(lowerQuery)) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("historyId"), entry->historyId());
        map.insert(QStringLiteral("title"), entry->title());
        map.insert(QStringLiteral("url"), entry->url());
        map.insert(QStringLiteral("visitTime"), entry->visitTime());
        map.insert(QStringLiteral("visitCount"), entry->visitCount());
        list.append(map);
    }
    return list;
}

void BrowserHistoryManager::load()
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
    const QJsonArray historyArray = root.value(QStringLiteral("history")).toArray();

    qDeleteAll(m_history);
    m_history.clear();

    for (const QJsonValue &value : historyArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("historyId")).toInt(m_nextHistoryId);
        if (id >= m_nextHistoryId) {
            m_nextHistoryId = id + 1;
        }

        auto *entry = new BrowserHistoryEntry(id, this);
        entry->setTitle(obj.value(QStringLiteral("title")).toString());
        entry->setUrl(obj.value(QStringLiteral("url")).toString());
        entry->setVisitTime(QDateTime::fromString(obj.value(QStringLiteral("visitTime")).toString(), Qt::ISODate));
        entry->setVisitCount(obj.value(QStringLiteral("visitCount")).toInt(1));
        m_history.append(entry);
    }
}

void BrowserHistoryManager::save()
{
    QJsonArray historyArray;
    for (const BrowserHistoryEntry *entry : m_history) {
        if (!entry) {
            continue;
        }
        QJsonObject obj;
        obj.insert(QStringLiteral("historyId"), entry->historyId());
        obj.insert(QStringLiteral("title"), entry->title());
        obj.insert(QStringLiteral("url"), entry->url());
        obj.insert(QStringLiteral("visitTime"), entry->visitTime().toString(Qt::ISODate));
        obj.insert(QStringLiteral("visitCount"), entry->visitCount());
        historyArray.append(obj);
    }

    QJsonObject root;
    root.insert(QStringLiteral("history"), historyArray);

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

QString BrowserHistoryManager::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/browser");
}

QString BrowserHistoryManager::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/history.json");
}

int BrowserHistoryManager::generateHistoryId()
{
    return m_nextHistoryId++;
}

BrowserHistoryEntry *BrowserHistoryManager::findEntry(const QString &url) const
{
    for (BrowserHistoryEntry *entry : m_history) {
        if (entry && entry->url() == url) {
            return entry;
        }
    }
    return nullptr;
}

BrowserHistoryEntry *BrowserHistoryManager::findEntryById(int historyId) const
{
    for (BrowserHistoryEntry *entry : m_history) {
        if (entry && entry->historyId() == historyId) {
            return entry;
        }
    }
    return nullptr;
}

void BrowserHistoryManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Browser"),
                                              QStringLiteral("info"));
}

bool BrowserHistoryManager::shouldRecord(const QString &url) const
{
    if (url.isEmpty()) {
        return false;
    }
    if (url.startsWith(QStringLiteral("data:"))) {
        return false;
    }
    if (url.startsWith(QStringLiteral("about:"))) {
        return false;
    }
    if (url.startsWith(QStringLiteral("bos:")) || url.startsWith(QStringLiteral("file:"))) {
        return false;
    }
    if (url.contains(QStringLiteral("//error/")) || url.contains(QStringLiteral("//blank"))) {
        return false;
    }
    return true;
}

} // namespace bos::shell
