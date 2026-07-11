#pragma once

#include <QList>
#include <QString>

#include "bos/SearchItem.h"
#include "bos/SearchProvider.h"

namespace bos::shell {

/**
 * @brief Search provider for Settings pages.
 *
 * Registers each top-level Settings page so users can jump directly to it from
 * the launcher.
 */
class SettingsSearchProvider : public SearchProvider {
public:
    QString providerName() const override;
    QList<SearchItem> registerItems() override;
};

} // namespace bos::shell
