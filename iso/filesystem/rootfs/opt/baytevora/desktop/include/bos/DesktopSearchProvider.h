#pragma once

#include <QList>
#include <QString>

#include "bos/SearchItem.h"
#include "bos/SearchProvider.h"

namespace bos::shell {

/**
 * @brief Search provider for desktop locations.
 *
 * Registers standard desktop shortcuts such as Home, Documents, and Trash.
 */
class DesktopSearchProvider : public SearchProvider {
public:
    QString providerName() const override;
    QList<SearchItem> registerItems() override;
};

} // namespace bos::shell
