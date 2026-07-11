#include "bos/SearchManager.h"

#include <QDebug>
#include <QVariantMap>

#include "bos/SearchProvider.h"

namespace bos::shell {

SearchManager::SearchManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << QStringLiteral("[BDE] Search manager initialized");
}

SearchManager::~SearchManager()
{
    m_results.clear();
    m_items.clear();
    m_itemIds.clear();
    m_providers.clear();
}

void SearchManager::registerProvider(SearchProvider *provider)
{
    if (!provider) {
        return;
    }

    if (m_providers.contains(provider)) {
        qDebug() << QStringLiteral("[BDE] Search provider already registered:") << provider->providerName();
        return;
    }

    m_providers.append(provider);
    indexItems(provider);

    emit providerRegistered(provider->providerName());
    qDebug() << QStringLiteral("[BDE] Search provider registered:") << provider->providerName();
}

void SearchManager::removeProvider(SearchProvider *provider)
{
    if (!provider || !m_providers.contains(provider)) {
        return;
    }

    removeItems(provider);
    m_providers.removeOne(provider);
    provider->unregisterItems();

    emit providerRemoved(provider->providerName());
    qDebug() << QStringLiteral("[BDE] Search provider removed:") << provider->providerName();
}

void SearchManager::search(const QString &text)
{
    clearResults();

    if (text.isEmpty()) {
        emit resultsChanged();
        return;
    }

    const QString query = text.toLower();
    qDebug() << QStringLiteral("[BDE] Search:") << text;

    for (const SearchItem &item : m_items) {
        if (!item.enabled) {
            continue;
        }
        const int score = scoreItem(item, query);
        if (score >= 0) {
            m_results.append(item);
        }
    }

    std::sort(m_results.begin(), m_results.end(),
              [this, &query](const SearchItem &a, const SearchItem &b) {
                  const int scoreA = scoreItem(a, query);
                  const int scoreB = scoreItem(b, query);
                  if (scoreA != scoreB) {
                      return scoreA < scoreB;
                  }
                  return a.title.toLower() < b.title.toLower();
              });

    qDebug() << QStringLiteral("[BDE] Results:") << m_results.size();
    emit resultsChanged();
}

void SearchManager::clearResults()
{
    if (m_results.isEmpty()) {
        return;
    }
    m_results.clear();
    emit resultsChanged();
}

QVariantList SearchManager::results() const
{
    QVariantList list;
    list.reserve(m_results.size());
    for (const SearchItem &item : m_results) {
        list.append(item.toMap());
    }
    return list;
}

int SearchManager::providerCount() const
{
    return m_providers.size();
}

int SearchManager::itemCount() const
{
    return m_items.size();
}

void SearchManager::indexItems(SearchProvider *provider)
{
    const QList<SearchItem> items = provider->registerItems();
    int accepted = 0;
    int rejected = 0;

    for (const SearchItem &item : items) {
        if (!item.enabled) {
            continue;
        }
        if (m_itemIds.contains(item.id)) {
            ++rejected;
            continue;
        }
        m_itemIds.insert(item.id);
        m_items.append(item);
        ++accepted;
    }

    if (rejected > 0) {
        qDebug() << QStringLiteral("[BDE] Duplicate search item rejected");
    }

    Q_UNUSED(accepted)
    logIndexedCount();
}

void SearchManager::removeItems(SearchProvider *provider)
{
    const QList<SearchItem> items = provider->registerItems();
    for (const SearchItem &item : items) {
        m_itemIds.remove(item.id);
    }

    auto it = m_items.begin();
    while (it != m_items.end()) {
        if (it->provider == provider->providerName()) {
            m_itemIds.remove(it->id);
            it = m_items.erase(it);
        } else {
            ++it;
        }
    }

    logIndexedCount();
}

int SearchManager::scoreItem(const SearchItem &item, const QString &query) const
{
    const QString title = item.title.toLower();
    if (title == query) {
        return 0;
    }
    if (title.startsWith(query)) {
        return 1;
    }
    if (title.contains(query)) {
        return 2;
    }

    bool keywordExact = false;
    bool keywordContains = false;
    for (const QString &keyword : item.keywords) {
        const QString lowerKeyword = keyword.toLower();
        if (lowerKeyword == query) {
            keywordExact = true;
        } else if (lowerKeyword.contains(query)) {
            keywordContains = true;
        }
    }
    if (keywordExact) {
        return 3;
    }
    if (keywordContains) {
        return 4;
    }

    if (item.subtitle.toLower().contains(query)) {
        return 5;
    }

    return -1;
}

void SearchManager::logIndexedCount()
{
    qDebug() << QStringLiteral("[BDE] Indexed items:") << m_items.size();
}

} // namespace bos::shell
