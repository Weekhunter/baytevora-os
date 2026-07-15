#pragma once

#include <QList>
#include <QObject>
#include <QSet>
#include <QVariantList>

#include "bos/SearchItem.h"

namespace bos::shell {

class SearchProvider;

/**
 * @brief Central manager for the Baytevora Search Service (BSS).
 *
 * SearchManager registers search providers, indexes their SearchItems, and
 * performs case-insensitive searches over titles, subtitles, and keywords.
 * Results are ordered by priority: exact title match, title starts with query,
 * title contains query, keyword match, and subtitle contains query.
 *
 * The manager exposes the current result list to QML and logs all important
 * operations with the [BDE] prefix.
 */
class SearchManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList results READ results NOTIFY resultsChanged)

public:
    explicit SearchManager(QObject *parent = nullptr);
    ~SearchManager() override;

    void registerProvider(SearchProvider *provider);
    void removeProvider(SearchProvider *provider);

    Q_INVOKABLE void search(const QString &text);
    Q_INVOKABLE void clearResults();

    QVariantList results() const;

    Q_INVOKABLE int providerCount() const;
    Q_INVOKABLE int itemCount() const;

signals:
    void resultsChanged();
    void providerRegistered(const QString &name);
    void providerRemoved(const QString &name);

private:
    void indexItems(SearchProvider *provider);
    void removeItems(SearchProvider *provider);
    int scoreItem(const SearchItem &item, const QString &query) const;
    void logIndexedCount();

    QList<SearchProvider *> m_providers;
    QList<SearchItem> m_items;
    QList<SearchItem> m_results;
    QSet<QString> m_itemIds;
};

} // namespace bos::shell
