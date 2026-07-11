#pragma once

#include <QList>
#include <QString>

#include "bos/SearchItem.h"

namespace bos::shell {

/**
 * @brief Abstract interface for search providers in the Baytevora Search Service.
 *
 * Each subsystem implements a SearchProvider to expose its own searchable items.
 * SearchManager indexes the items returned by registerItems() and removes them when
 * the provider is unregistered.
 */
class SearchProvider {
public:
    virtual ~SearchProvider() = default;

    /**
     * @brief Human-readable provider name used for logging and the Settings page.
     */
    virtual QString providerName() const = 0;

    /**
     * @brief Returns the list of searchable items offered by this provider.
     */
    virtual QList<SearchItem> registerItems() = 0;

    /**
     * @brief Called when the provider is removed from SearchManager.
     */
    virtual void unregisterItems() {}

    /**
     * @brief Called to refresh the provider's item list.
     */
    virtual void refresh() {}
};

} // namespace bos::shell
