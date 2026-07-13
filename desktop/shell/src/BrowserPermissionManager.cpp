#include "bos/BrowserPermissionManager.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "bos/BrowserPermission.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserPermissionManager::BrowserPermissionManager(QObject *parent)
    : QObject(parent)
{
    load();
}

BrowserPermissionManager::~BrowserPermissionManager()
{
    qDeleteAll(m_permissions);
    m_permissions.clear();
}

QVariantList BrowserPermissionManager::permissions() const
{
    QVariantList list;
    list.reserve(m_permissions.size());
    for (const BrowserPermission *permission : m_permissions) {
        if (!permission) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("permissionId"), permission->permissionId());
        map.insert(QStringLiteral("origin"), permission->origin());
        map.insert(QStringLiteral("permissionType"), permission->permissionType());
        map.insert(QStringLiteral("state"), permission->state());
        map.insert(QStringLiteral("lastModified"), permission->lastModified());
        list.append(map);
    }
    return list;
}

void BrowserPermissionManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QString BrowserPermissionManager::permission(const QString &origin,
                                            const QString &permissionType) const
{
    BrowserPermission *entry = findPermission(origin, permissionType);
    if (entry) {
        return entry->state();
    }
    return QStringLiteral("Ask");
}

void BrowserPermissionManager::setPermission(const QString &origin,
                                            const QString &permissionType,
                                            const QString &state)
{
    if (origin.isEmpty() || permissionType.isEmpty()) {
        return;
    }
    if (state != QStringLiteral("Ask")
        && state != QStringLiteral("Allow")
        && state != QStringLiteral("Block")) {
        return;
    }

    BrowserPermission *entry = findPermission(origin, permissionType);
    if (!entry) {
        const int id = generatePermissionId();
        entry = new BrowserPermission(id, this);
        entry->setOrigin(origin);
        entry->setPermissionType(permissionType);
        m_permissions.append(entry);
    }

    entry->setState(state);
    entry->setLastModified(QDateTime::currentDateTime());
    save();
    emit permissionsChanged();

    emitNotification(QStringLiteral("Permission Updated"),
                   QStringLiteral("%1 for %2 set to %3").arg(permissionType, origin, state));
}

void BrowserPermissionManager::resetPermission(const QString &origin,
                                            const QString &permissionType)
{
    BrowserPermission *entry = findPermission(origin, permissionType);
    if (!entry) {
        return;
    }
    m_permissions.removeOne(entry);
    delete entry;
    save();
    emit permissionsChanged();
}

void BrowserPermissionManager::resetAllPermissions()
{
    qDeleteAll(m_permissions);
    m_permissions.clear();
    save();
    emit permissionsChanged();
}

void BrowserPermissionManager::resetPermissionsForOrigin(const QString &origin)
{
    for (int i = m_permissions.size() - 1; i >= 0; --i) {
        BrowserPermission *entry = m_permissions.at(i);
        if (entry && entry->origin() == origin) {
            m_permissions.removeAt(i);
            delete entry;
        }
    }
    save();
    emit permissionsChanged();
}

QVariantList BrowserPermissionManager::permissionsForOrigin(const QString &origin) const
{
    QVariantList list;
    for (const BrowserPermission *entry : m_permissions) {
        if (entry && entry->origin() == origin) {
            QVariantMap map;
            map.insert(QStringLiteral("permissionId"), entry->permissionId());
            map.insert(QStringLiteral("origin"), entry->origin());
            map.insert(QStringLiteral("permissionType"), entry->permissionType());
            map.insert(QStringLiteral("state"), entry->state());
            map.insert(QStringLiteral("lastModified"), entry->lastModified());
            list.append(map);
        }
    }
    return list;
}

void BrowserPermissionManager::load()
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
    const QJsonArray permissionsArray = root.value(QStringLiteral("permissions")).toArray();

    qDeleteAll(m_permissions);
    m_permissions.clear();

    for (const QJsonValue &value : permissionsArray) {
        const QJsonObject obj = value.toObject();
        const int id = obj.value(QStringLiteral("permissionId")).toInt(m_nextPermissionId);
        if (id >= m_nextPermissionId) {
            m_nextPermissionId = id + 1;
        }

        auto *entry = new BrowserPermission(id, this);
        entry->setOrigin(obj.value(QStringLiteral("origin")).toString());
        entry->setPermissionType(obj.value(QStringLiteral("permissionType")).toString());
        entry->setState(obj.value(QStringLiteral("state")).toString(QStringLiteral("Ask")));
        entry->setLastModified(QDateTime::fromString(obj.value(QStringLiteral("lastModified")).toString(), Qt::ISODate));
        m_permissions.append(entry);
    }
}

void BrowserPermissionManager::save()
{
    QJsonArray permissionsArray;
    for (const BrowserPermission *permission : m_permissions) {
        if (!permission) {
            continue;
        }
        QJsonObject obj;
        obj.insert(QStringLiteral("permissionId"), permission->permissionId());
        obj.insert(QStringLiteral("origin"), permission->origin());
        obj.insert(QStringLiteral("permissionType"), permission->permissionType());
        obj.insert(QStringLiteral("state"), permission->state());
        obj.insert(QStringLiteral("lastModified"), permission->lastModified().toString(Qt::ISODate));
        permissionsArray.append(obj);
    }

    QJsonObject root;
    root.insert(QStringLiteral("permissions"), permissionsArray);

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

QString BrowserPermissionManager::storageDirectory() const
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (path.isEmpty()) {
        path = QDir::homePath() + QStringLiteral("/.baytevora");
    }
    return path + QStringLiteral("/browser");
}

QString BrowserPermissionManager::storageFilePath() const
{
    return storageDirectory() + QStringLiteral("/permissions.json");
}

int BrowserPermissionManager::generatePermissionId()
{
    return m_nextPermissionId++;
}

BrowserPermission *BrowserPermissionManager::findPermission(const QString &origin,
                                                          const QString &permissionType) const
{
    for (BrowserPermission *entry : m_permissions) {
        if (entry && entry->origin() == origin && entry->permissionType() == permissionType) {
            return entry;
        }
    }
    return nullptr;
}

void BrowserPermissionManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Browser"),
                                              QStringLiteral("info"));
}

} // namespace bos::shell
