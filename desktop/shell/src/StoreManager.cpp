#include "bos/StoreManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"
#include "bos/PackageManager.h"
#include "bos/StoreCatalog.h"

namespace bos::shell {

StoreManager::StoreManager(QObject *parent)
    : QObject(parent)
    , m_catalog(std::make_unique<StoreCatalog>())
{
    qDebug() << QStringLiteral("[BDE] StoreManager initialized");
}

StoreManager::~StoreManager() = default;

void StoreManager::setPackageManager(PackageManager *packageManager)
{
    m_packageManager = packageManager;
    syncInstalledState();
}

void StoreManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QVariantList StoreManager::featuredItems() const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->featuredItems()) {
        list.append(item.toMap());
    }
    return list;
}

QVariantList StoreManager::allItems() const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->allItems()) {
        list.append(item.toMap());
    }
    return list;
}

QStringList StoreManager::categories() const
{
    return m_catalog->categories();
}

QVariantMap StoreManager::item(const QString &packageId) const
{
    return m_catalog->item(packageId).toMap();
}

QVariantList StoreManager::search(const QString &query) const
{
    const QString trimmed = query.trimmed().toLower();
    QVariantList list;
    for (const StoreItem &item : m_catalog->allItems()) {
        if (trimmed.isEmpty() ||
            item.name.toLower().contains(trimmed) ||
            item.description.toLower().contains(trimmed) ||
            item.developer.toLower().contains(trimmed)) {
            list.append(item.toMap());
        }
    }
    return list;
}

QVariantList StoreManager::categoryItems(int category) const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->categoryItems(static_cast<StoreCategory::Value>(category))) {
        list.append(item.toMap());
    }
    return list;
}

void StoreManager::requestInstall(const QString &packageId)
{
    if (!m_catalog->contains(packageId)) {
        notify(QStringLiteral("Store"), QStringLiteral("Package unavailable."));
        return;
    }

    if (!m_packageManager) {
        notify(QStringLiteral("Store"), QStringLiteral("Package manager unavailable."));
        return;
    }

    const QVariantMap package = m_packageManager->package(packageId);
    if (!package.isEmpty() && package[QStringLiteral("installed")].toBool()) {
        notify(QStringLiteral("Store"),
               QStringLiteral("%1 is already installed.").arg(package.value(QStringLiteral("name")).toString()));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Store install request for") << packageId;
    m_packageManager->installPackage(packageId);
    syncInstalledState();
    notify(QStringLiteral("Store"), QStringLiteral("Install requested."));
}

QString StoreManager::categoryName(int category) const
{
    return StoreCategory::name(static_cast<StoreCategory::Value>(category));
}

void StoreManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                  QStringLiteral("Store"),
                                                  QStringLiteral("info"));
    }
}

void StoreManager::syncInstalledState()
{
    if (!m_packageManager) {
        return;
    }

    for (const StoreItem &item : m_catalog->allItems()) {
        const QVariantMap package = m_packageManager->package(item.packageId);
        if (!package.isEmpty()) {
            m_catalog->updateInstalledState(item.packageId,
                                            package[QStringLiteral("installed")].toBool());
        }
    }
    emit catalogChanged();
}

void StoreManager::emitChange()
{
    emit catalogChanged();
}

} // namespace bos::shell
