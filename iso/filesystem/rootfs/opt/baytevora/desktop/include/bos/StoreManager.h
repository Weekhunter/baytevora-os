#pragma once

#include <QObject>
#include <QVariantList>

#include <memory>

#include "bos/StoreItem.h"

namespace bos::shell {

class NotificationManager;
class PackageManager;
class StoreCatalog;

/**
 * @brief Coordinates the Baytevora Store Phase 2 catalog and installed apps.
 *
 * StoreManager owns the StoreCatalog and exposes the store data model to QML.
 * All install/remove requests delegate to PackageManager as placeholder
 * operations. StoreManager computes installed applications, updates, categories,
 * and supports search, sort, and filtering.
 */
class StoreManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList featuredItems READ featuredItems NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList allItems READ allItems NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList categories READ categories NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList installedApplications READ installedApplications NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList updates READ updates NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList recentlyAdded READ recentlyAdded NOTIFY catalogChanged)

public:
    explicit StoreManager(QObject *parent = nullptr);
    ~StoreManager() override;

    void setPackageManager(PackageManager *packageManager);
    void setNotificationManager(NotificationManager *notificationManager);

    QVariantList featuredItems() const;
    QVariantList allItems() const;
    QVariantList categories() const;
    QVariantList installedApplications() const;
    QVariantList updates() const;
    QVariantList recentlyAdded() const;

    Q_INVOKABLE QVariantMap item(const QString &applicationId) const;
    Q_INVOKABLE QVariantList search(const QString &query) const;
    Q_INVOKABLE QVariantList categoryItems(int category) const;

    Q_INVOKABLE QVariantList filterInstalled(bool installed) const;
    Q_INVOKABLE QVariantList sortByName(const QVariantList &items) const;
    Q_INVOKABLE QVariantList sortByRating(const QVariantList &items) const;
    Q_INVOKABLE QVariantList sortByDownloads(const QVariantList &items) const;

    Q_INVOKABLE void requestInstall(const QString &applicationId);
    Q_INVOKABLE void requestRemove(const QString &applicationId);
    Q_INVOKABLE void refreshUpdates();

    Q_INVOKABLE QString categoryName(int category) const;
    Q_INVOKABLE QVariantList storeDependenciesFor(const QString &applicationId) const;
    Q_INVOKABLE QVariantMap packageMetadata(const QString &applicationId) const;
    Q_INVOKABLE bool storeUpdateAvailable(const QString &applicationId) const;
    Q_INVOKABLE QVariantList storeUpdatePlan() const;

signals:
    void catalogChanged();

private:
    void notify(const QString &title, const QString &message);
    void syncInstalledState();
    void emitChange();

    std::unique_ptr<StoreCatalog> m_catalog;
    PackageManager *m_packageManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
