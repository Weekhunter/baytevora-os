#pragma once

#include <memory>
#include <vector>

#include "bos/DesktopModule.h"
#include "bos/SearchProvider.h"

namespace bos::shell {

class SearchManager;

/**
 * @brief Desktop module that owns the Baytevora Search Service.
 *
 * SearchModule creates the SearchManager and registers the built-in search
 * providers (Application, Desktop, Settings) during the module lifecycle.
 */
class SearchModule : public DesktopModule {
public:
    SearchModule();
    ~SearchModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    SearchManager *searchManager() const;

private:
    std::unique_ptr<SearchManager> m_searchManager;
    std::vector<std::unique_ptr<SearchProvider>> m_providers;
};

} // namespace bos::shell
