#include "bos/BrowserSession.h"

#include "bos/BrowserTab.h"
#include "bos/BrowserDownloadManager.h"
#include "bos/BrowserBookmarkManager.h"
#include "bos/BrowserHistoryManager.h"
#include "bos/BrowserPermissionManager.h"
#include "bos/BrowserPrivacySettings.h"

namespace bos::shell {

BrowserSession::BrowserSession(QObject *parent)
    : QObject(parent)
    , m_downloadManager(new BrowserDownloadManager(this))
    , m_bookmarkManager(new BrowserBookmarkManager(this))
    , m_historyManager(new BrowserHistoryManager(this))
    , m_permissionManager(new BrowserPermissionManager(this))
    , m_privacySettings(new BrowserPrivacySettings(this))
{
}

BrowserSession::~BrowserSession()
{
    // Apply exit privacy policies while the history manager is still alive.
    if (m_privacySettings) {
        m_privacySettings->applyExitPolicy(m_historyManager);
    }

    qDeleteAll(m_tabs);
    m_tabs.clear();
    qDeleteAll(m_closedTabs);
    m_closedTabs.clear();
}

QVariantList BrowserSession::tabs() const
{
    QVariantList list;
    list.reserve(m_tabs.size());
    for (const BrowserTab *tab : m_tabs) {
        if (!tab) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("tabId"), tab->tabId());
        map.insert(QStringLiteral("title"), tab->title());
        map.insert(QStringLiteral("url"), tab->url());
        map.insert(QStringLiteral("loading"), tab->loading());
        map.insert(QStringLiteral("canGoBack"), tab->canGoBack());
        map.insert(QStringLiteral("canGoForward"), tab->canGoForward());
        list.append(map);
    }
    return list;
}

int BrowserSession::activeTabId() const { return m_activeTabId; }

BrowserDownloadManager *BrowserSession::downloadManager() const
{
    return m_downloadManager;
}

BrowserBookmarkManager *BrowserSession::bookmarkManager() const
{
    return m_bookmarkManager;
}

BrowserHistoryManager *BrowserSession::historyManager() const
{
    return m_historyManager;
}

BrowserPermissionManager *BrowserSession::permissionManager() const
{
    return m_permissionManager;
}

BrowserPrivacySettings *BrowserSession::privacySettings() const
{
    return m_privacySettings;
}

BrowserTab *BrowserSession::activeTab() const
{
    return tabById(m_activeTabId);
}

BrowserTab *BrowserSession::tabById(int tabId) const
{
    for (BrowserTab *tab : m_tabs) {
        if (tab && tab->tabId() == tabId) {
            return tab;
        }
    }
    return nullptr;
}

int BrowserSession::tabCount() const
{
    return m_tabs.size();
}

int BrowserSession::indexOfTab(int tabId) const
{
    for (int i = 0; i < m_tabs.size(); ++i) {
        BrowserTab *tab = m_tabs.at(i);
        if (tab && tab->tabId() == tabId) {
            return i;
        }
    }
    return -1;
}

BrowserTab *BrowserSession::addTab(const QString &url, const QString &title)
{
    return addTabWithId(generateTabId(), url, title);
}

BrowserTab *BrowserSession::addTabWithId(int tabId, const QString &url, const QString &title)
{
    auto *tab = new BrowserTab(tabId, this);
    tab->setUrl(url);
    tab->setTitle(title);
    m_tabs.append(tab);

    if (m_nextTabId <= tabId) {
        m_nextTabId = tabId + 1;
    }

    emit tabsChanged();

    if (m_activeTabId < 0) {
        setActiveTabId(tabId);
    }

    return tab;
}

BrowserTab *BrowserSession::duplicateTab(int tabId)
{
    BrowserTab *source = tabById(tabId);
    if (!source) {
        return nullptr;
    }
    return addTab(source->url(), source->title());
}

bool BrowserSession::removeTab(int tabId)
{
    const int index = indexOfTab(tabId);
    if (index < 0) {
        return false;
    }

    BrowserTab *tab = m_tabs.takeAt(index);
    if (tab) {
        tab->setParent(nullptr);
        m_closedTabs.append(tab);
        if (m_closedTabs.size() > 10) {
            BrowserTab *old = m_closedTabs.takeFirst();
            delete old;
        }
    }

    if (m_activeTabId == tabId) {
        if (m_tabs.isEmpty()) {
            setActiveTabId(-1);
        } else if (index < m_tabs.size()) {
            setActiveTabId(m_tabs.at(index)->tabId());
        } else if (!m_tabs.isEmpty()) {
            setActiveTabId(m_tabs.at(qMax(0, index - 1))->tabId());
        }
    }

    emit tabsChanged();
    return true;
}

void BrowserSession::moveTab(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex >= m_tabs.size()) {
        return;
    }
    if (toIndex < 0 || toIndex >= m_tabs.size()) {
        return;
    }
    if (fromIndex == toIndex) {
        return;
    }
    m_tabs.move(fromIndex, toIndex);
    emit tabsChanged();
}

BrowserTab *BrowserSession::takeLastClosed()
{
    if (m_closedTabs.isEmpty()) {
        return nullptr;
    }
    BrowserTab *tab = m_closedTabs.takeLast();
    tab->setParent(this);
    m_tabs.append(tab);
    setActiveTabId(tab->tabId());
    emit tabsChanged();
    return tab;
}

void BrowserSession::setActiveTabId(int tabId)
{
    if (m_activeTabId == tabId) {
        return;
    }
    m_activeTabId = tabId;
    emit activeTabIdChanged();
}

void BrowserSession::notifyTabChanged(BrowserTab *tab)
{
    if (!tab) {
        return;
    }
    emit tabsChanged();
}

int BrowserSession::generateTabId() const
{
    return m_nextTabId++;
}

} // namespace bos::shell
