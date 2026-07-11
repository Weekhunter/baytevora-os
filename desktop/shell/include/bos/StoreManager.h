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
 * @brief Coordinates the Baytevora Store Foundation (BSF) catalog.
 *
 * StoreManager owns the StoreCatalog and exposes the store data model to QML.
 * All install requests delegate to PackageManager and therefore remain
 * placeholder operations.
 */
class StoreManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList featuredItems READ featuredItems NOTIFY catalogChanged)
    Q_PROPERTY(QVariantList allItems READ allItems NOTIFY catalogChanged)
    Q_PROPERTY(QStringList categories READ categories NOTIFY catalogChanged)

public:
    explicit StoreManager(QObject *parent = nullptr);
    ~StoreManager() override;

    void setPackageManager(PackageManager *packageManager);
    void setNotificationManager(NotificationManager *notificationManager);

    QVariantList featuredItems() const;
    QVariantList allItems() const;
    QStringList categories() const;

    Q_INVOKABLE QVariantMap item(const QString &packageId) const;
    Q_INVOKABLE QVariantList search(const QString &query) const;
    Q_INVOKABLE QVariantList categoryItems(int category) const;
    Q_INVOKABLE void requestInstall(const QString &packageId);

    Q_INVOKABLE QString categoryName(int category) const;

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
