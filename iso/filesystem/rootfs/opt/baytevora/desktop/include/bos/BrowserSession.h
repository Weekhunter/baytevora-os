#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class BrowserTab;
class BrowserDownloadManager;
class BrowserBookmarkManager;
class BrowserHistoryManager;
class BrowserPermissionManager;
class BrowserPrivacySettings;

/**
 * @brief Holds the open tabs, active tab, downloads, bookmarks, history,
 *        permissions, and privacy settings for a single browser window.
 *
 * BrowserSession lives only while its browser window is open. Persistent
 * session restore is intentionally outside the scope of this sprint.
 */
class BrowserSession : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList tabs READ tabs NOTIFY tabsChanged FINAL)
    Q_PROPERTY(int activeTabId READ activeTabId NOTIFY activeTabIdChanged FINAL)
    Q_PROPERTY(BrowserDownloadManager *downloadManager READ downloadManager CONSTANT FINAL)
    Q_PROPERTY(BrowserBookmarkManager *bookmarkManager READ bookmarkManager CONSTANT FINAL)
    Q_PROPERTY(BrowserHistoryManager *historyManager READ historyManager CONSTANT FINAL)
    Q_PROPERTY(BrowserPermissionManager *permissionManager READ permissionManager CONSTANT FINAL)
    Q_PROPERTY(BrowserPrivacySettings *privacySettings READ privacySettings CONSTANT FINAL)

public:
    explicit BrowserSession(QObject *parent = nullptr);
    ~BrowserSession() override;

    QVariantList tabs() const;
    int activeTabId() const;
    BrowserDownloadManager *downloadManager() const;
    BrowserBookmarkManager *bookmarkManager() const;
    BrowserHistoryManager *historyManager() const;
    BrowserPermissionManager *permissionManager() const;
    BrowserPrivacySettings *privacySettings() const;

    BrowserTab *activeTab() const;
    BrowserTab *tabById(int tabId) const;
    int tabCount() const;
    int indexOfTab(int tabId) const;

    BrowserTab *addTab(const QString &url, const QString &title);
    BrowserTab *addTabWithId(int tabId, const QString &url, const QString &title);
    BrowserTab *duplicateTab(int tabId);
    bool removeTab(int tabId);
    void moveTab(int fromIndex, int toIndex);
    BrowserTab *takeLastClosed();

    void setActiveTabId(int tabId);

    void notifyTabChanged(BrowserTab *tab);

signals:
    void tabsChanged();
    void activeTabIdChanged();

private:
    int generateTabId() const;

    QList<BrowserTab*> m_tabs;
    QList<BrowserTab*> m_closedTabs;
    BrowserDownloadManager *m_downloadManager = nullptr;
    BrowserBookmarkManager *m_bookmarkManager = nullptr;
    BrowserHistoryManager *m_historyManager = nullptr;
    BrowserPermissionManager *m_permissionManager = nullptr;
    BrowserPrivacySettings *m_privacySettings = nullptr;
    int m_activeTabId = -1;
    int m_nextTabId = 1;
};

} // namespace bos::shell
