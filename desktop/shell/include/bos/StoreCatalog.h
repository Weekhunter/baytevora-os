#pragma once

#include <QHash>
#include <QList>
#include <QString>

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
    QList<StoreItem> categoryItems(StoreCategory::Value category) const;
    StoreItem item(const QString &packageId) const;
    bool contains(const QString &packageId) const;

    QStringList categories() const;

    void updateInstalledState(const QString &packageId, bool installed);

private:
    void seedCatalog();

    QHash<QString, StoreItem> m_items;
};

} // namespace bos::shell
