#include "bos/StoreManager.h"

#include <QDebug>

#include "bos/InstalledApplication.h"
#include "bos/NotificationManager.h"
#include "bos/PackageManager.h"
#include "bos/PackageState.h"
#include "bos/StoreCatalog.h"
#include "bos/StoreUpdate.h"

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

QVariantList StoreManager::categories() const
{
    QVariantList list;
    for (const StoreCategory &category : m_catalog->categories()) {
        list.append(category.toMap());
    }
    return list;
}

QVariantList StoreManager::installedApplications() const
{
    QVariantList list;
    const QDateTime now = QDateTime::currentDateTimeUtc();

    for (const StoreItem &item : m_catalog->allItems()) {
        if (!item.installed) {
            continue;
        }
        InstalledApplication app;
        app.applicationId = item.applicationId;
        app.version = item.installedVersion.isEmpty() ? item.version : item.installedVersion;
        app.installDate = now.addDays(-30);
        app.lastUpdated = item.installedVersion != item.latestVersion
                              ? now.addDays(-2)
                              : app.installDate;
        list.append(app.toMap());
    }
    return list;
}

QVariantList StoreManager::updates() const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->allItems()) {
        if (!item.installed) {
            continue;
        }
        const QString current = item.installedVersion.isEmpty() ? item.version : item.installedVersion;
        const QString latest = item.latestVersion.isEmpty() ? item.version : item.latestVersion;
        if (current != latest) {
            StoreUpdate update;
            update.applicationId = item.applicationId;
            update.installedVersion = current;
            update.availableVersion = latest;
            update.updateAvailable = true;
            list.append(update.toMap());
        }
    }
    return list;
}

QVariantList StoreManager::recentlyAdded() const
{
    QVariantList list;
    const QList<StoreItem> items = m_catalog->allItems();
    int count = 0;
    for (auto it = items.crbegin(); it != items.crend() && count < 4; ++it, ++count) {
        list.append(it->toMap());
    }
    return list;
}

QVariantMap StoreManager::item(const QString &applicationId) const
{
    return m_catalog->item(applicationId).toMap();
}

QVariantList StoreManager::search(const QString &query) const
{
    const QString trimmed = query.trimmed().toLower();
    QVariantList list;
    for (const StoreItem &item : m_catalog->allItems()) {
        if (trimmed.isEmpty() ||
            item.name.toLower().contains(trimmed) ||
            item.shortDescription.toLower().contains(trimmed) ||
            item.developer.toLower().contains(trimmed)) {
            list.append(item.toMap());
        }
    }
    return list;
}

QVariantList StoreManager::categoryItems(int category) const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->categoryItems(static_cast<StoreCategoryEnum::Value>(category))) {
        list.append(item.toMap());
    }
    return list;
}

QVariantList StoreManager::filterInstalled(bool installed) const
{
    QVariantList list;
    for (const StoreItem &item : m_catalog->allItems()) {
        if (item.installed == installed) {
            list.append(item.toMap());
        }
    }
    return list;
}

QVariantList StoreManager::sortByName(const QVariantList &items) const
{
    QVariantList result = items;
    std::sort(result.begin(), result.end(), [](const QVariant &a, const QVariant &b) {
        return a.toMap().value(QStringLiteral("name")).toString().toLower()
               < b.toMap().value(QStringLiteral("name")).toString().toLower();
    });
    return result;
}

QVariantList StoreManager::sortByRating(const QVariantList &items) const
{
    QVariantList result = items;
    std::sort(result.begin(), result.end(), [](const QVariant &a, const QVariant &b) {
        return a.toMap().value(QStringLiteral("rating")).toDouble()
               > b.toMap().value(QStringLiteral("rating")).toDouble();
    });
    return result;
}

QVariantList StoreManager::sortByDownloads(const QVariantList &items) const
{
    QVariantList result = items;
    std::sort(result.begin(), result.end(), [](const QVariant &a, const QVariant &b) {
        return a.toMap().value(QStringLiteral("downloads")).toInt()
               > b.toMap().value(QStringLiteral("downloads")).toInt();
    });
    return result;
}

void StoreManager::requestInstall(const QString &applicationId)
{
    if (!m_catalog->contains(applicationId)) {
        notify(QStringLiteral("Store"), QStringLiteral("Application unavailable."));
        return;
    }

    if (!m_packageManager) {
        notify(QStringLiteral("Store"), QStringLiteral("Package manager unavailable."));
        return;
    }

    const QVariantMap package = m_packageManager->package(applicationId);
    if (!package.isEmpty() && package[QStringLiteral("installed")].toBool()) {
        notify(QStringLiteral("Store"),
               QStringLiteral("%1 is already installed.").arg(package.value(QStringLiteral("name")).toString()));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Store install request for") << applicationId;
    m_packageManager->installPackage(applicationId);
    syncInstalledState();
    notify(QStringLiteral("Application Installed"),
           QStringLiteral("%1 installed successfully.").arg(m_catalog->item(applicationId).name));
    emitChange();
}

void StoreManager::requestRemove(const QString &applicationId)
{
    if (!m_catalog->contains(applicationId)) {
        notify(QStringLiteral("Store"), QStringLiteral("Application unavailable."));
        return;
    }

    if (!m_packageManager) {
        notify(QStringLiteral("Store"), QStringLiteral("Package manager unavailable."));
        return;
    }

    const QVariantMap package = m_packageManager->package(applicationId);
    if (!package.isEmpty() && !package[QStringLiteral("installed")].toBool()) {
        notify(QStringLiteral("Store"),
               QStringLiteral("%1 is not installed.").arg(package.value(QStringLiteral("name")).toString()));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Store remove request for") << applicationId;
    m_packageManager->uninstallPackage(applicationId);
    syncInstalledState();
    notify(QStringLiteral("Application Removed"),
           QStringLiteral("%1 removed successfully.").arg(m_catalog->item(applicationId).name));
    emitChange();
}

void StoreManager::refreshUpdates()
{
    syncInstalledState();
    notify(QStringLiteral("Updates Refreshed"), QStringLiteral("Update status refreshed."));
    emitChange();
}

QString StoreManager::categoryName(int category) const
{
    return StoreCategoryEnum::name(static_cast<StoreCategoryEnum::Value>(category));
}

QVariantList StoreManager::storeDependenciesFor(const QString &applicationId) const
{
    if (!m_packageManager) {
        return QVariantList();
    }
    return m_packageManager->dependenciesFor(applicationId);
}

QVariantMap StoreManager::packageMetadata(const QString &applicationId) const
{
    if (!m_packageManager) {
        return QVariantMap();
    }
    return m_packageManager->applicationPackage(applicationId);
}

bool StoreManager::storeUpdateAvailable(const QString &applicationId) const
{
    if (!m_packageManager) {
        return false;
    }
    const QVariantMap pkg = m_packageManager->applicationPackage(applicationId);
    return pkg.value(QStringLiteral("installed")).toBool()
           && pkg.value(QStringLiteral("state")).toInt() == static_cast<int>(bos::shell::PackageState::UpdateAvailable);
}

QVariantList StoreManager::storeUpdatePlan() const
{
    if (!m_packageManager) {
        return QVariantList();
    }
    return m_packageManager->updatePlan();
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
        const QVariantMap package = m_packageManager->package(item.applicationId);
        if (!package.isEmpty()) {
            m_catalog->updateInstalledState(item.applicationId,
                                            package[QStringLiteral("installed")].toBool());
            m_catalog->updateInstalledVersion(item.applicationId,
                                              package[QStringLiteral("version")].toString());
        }
    }
    emit catalogChanged();
}

void StoreManager::emitChange()
{
    emit catalogChanged();
}

} // namespace bos::shell
