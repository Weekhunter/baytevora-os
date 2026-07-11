#pragma once

#include <QList>
#include <QString>

#include "bos/SearchItem.h"
#include "bos/SearchProvider.h"

namespace bos::shell {

/**
 * @brief Search provider for installed applications.
 *
 * Registers the built-in BOS applications that should be searchable from the
 * launcher.
 */
class ApplicationSearchProvider : public SearchProvider {
public:
    QString providerName() const override;
    QList<SearchItem> registerItems() override;
};

} // namespace bos::shell
