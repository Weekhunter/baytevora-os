#include "bos/SearchModule.h"

#include <QDebug>

#include "bos/ApplicationSearchProvider.h"
#include "bos/DesktopSearchProvider.h"
#include "bos/SearchManager.h"
#include "bos/SettingsSearchProvider.h"

namespace bos::shell {

SearchModule::SearchModule()
{
}

SearchModule::~SearchModule() = default;

QString SearchModule::name() const
{
    return QStringLiteral("Search");
}

void SearchModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");

    m_searchManager = std::make_unique<SearchManager>();

    auto applicationProvider = std::make_unique<ApplicationSearchProvider>();
    auto desktopProvider = std::make_unique<DesktopSearchProvider>();
    auto settingsProvider = std::make_unique<SettingsSearchProvider>();

    m_searchManager->registerProvider(applicationProvider.get());
    m_searchManager->registerProvider(desktopProvider.get());
    m_searchManager->registerProvider(settingsProvider.get());

    m_providers.push_back(std::move(applicationProvider));
    m_providers.push_back(std::move(desktopProvider));
    m_providers.push_back(std::move(settingsProvider));
}

void SearchModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void SearchModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_providers.clear();
    m_searchManager.reset();
}

SearchManager *SearchModule::searchManager() const
{
    return m_searchManager.get();
}

} // namespace bos::shell
