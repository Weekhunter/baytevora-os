#pragma once

#include <QHash>
#include <QList>
#include <QString>

#include "bos/StoreCategory.h"
#include "bos/StoreItem.h"

namespace bos::shell {

/**
 * @brief Owns the visible Baytevora Store catalog.
 *
 * StoreCatalog stores placeholder StoreItem entries. No network or filesystem
 * access is performed.
 */
class StoreCatalog {
public:
    StoreCatalog();

    QList<StoreItem> allItems() const;
    QList<StoreItem> featuredItems() const;
    QList<StoreItem> categoryItems(StoreCategoryEnum::Value category) const;
    StoreItem item(const QString &applicationId) const;
    bool contains(const QString &applicationId) const;

    QList<StoreCategory> categories() const;

    void updateInstalledState(const QString &applicationId, bool installed);
    void updateInstalledVersion(const QString &applicationId, const QString &installedVersion);

private:
    void seedCatalog();
    static int categoryId(StoreCategoryEnum::Value category);

    QHash<QString, StoreItem> m_items;
};

} // namespace bos::shell
