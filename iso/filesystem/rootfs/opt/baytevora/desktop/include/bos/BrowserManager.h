#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>

QT_BEGIN_NAMESPACE
class QWebEngineDownloadRequest;
QT_END_NAMESPACE

namespace bos::shell {

class BrowserSession;
class BrowserTab;
class BrowserDownloadManager;
class BrowserBookmarkManager;
class BrowserHistoryManager;
class BrowserPermissionManager;
class BrowserPrivacySettings;
class NotificationManager;

/**
 * @brief Manages tabs, downloads, bookmarks, history, permissions, privacy,
 *        session state, and navigation for a browser window.
 *
 * BrowserManager owns a BrowserSession and exposes the active tab's state
 * together with the session's managers and privacy settings to QML. Each
 * BrowserWindow creates its own BrowserManager so windows remain isolated.
 */
class BrowserManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentUrl READ currentUrl NOTIFY currentUrlChanged FINAL)
    Q_PROPERTY(QString pageTitle READ pageTitle NOTIFY pageTitleChanged FINAL)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged FINAL)
    Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY canGoBackChanged FINAL)
    Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY canGoForwardChanged FINAL)
    Q_PROPERTY(QVariantList tabs READ tabs NOTIFY tabsChanged FINAL)
    Q_PROPERTY(int activeTabId READ activeTabId WRITE setActiveTabId NOTIFY activeTabIdChanged FINAL)
    Q_PROPERTY(BrowserDownloadManager *downloadManager READ downloadManager CONSTANT FINAL)
    Q_PROPERTY(BrowserBookmarkManager *bookmarkManager READ bookmarkManager CONSTANT FINAL)
    Q_PROPERTY(BrowserHistoryManager *historyManager READ historyManager CONSTANT FINAL)
    Q_PROPERTY(BrowserPermissionManager *permissionManager READ permissionManager CONSTANT FINAL)
    Q_PROPERTY(BrowserPrivacySettings *privacySettings READ privacySettings CONSTANT FINAL)

public:
    explicit BrowserManager(QObject *parent = nullptr);
    ~BrowserManager() override;

    QString currentUrl() const;
    QString pageTitle() const;
    bool loading() const;
    bool canGoBack() const;
    bool canGoForward() const;
    QVariantList tabs() const;
    int activeTabId() const;
    BrowserDownloadManager *downloadManager() const;
    BrowserBookmarkManager *bookmarkManager() const;
    BrowserHistoryManager *historyManager() const;
    BrowserPermissionManager *permissionManager() const;
    BrowserPrivacySettings *privacySettings() const;

    Q_INVOKABLE void setNotificationManager(QObject *notificationManager);

    Q_INVOKABLE void navigate(const QString &url);
    Q_INVOKABLE void reload();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void goHome();
    Q_INVOKABLE void goBack();
    Q_INVOKABLE void goForward();

    Q_INVOKABLE int newTab(const QString &url = QString());
    Q_INVOKABLE void closeTab(int tabId);
    Q_INVOKABLE void switchTab(int tabId);
    Q_INVOKABLE void duplicateTab(int tabId);
    Q_INVOKABLE void moveTab(int fromIndex, int toIndex);
    Q_INVOKABLE void restoreClosedTab();

    Q_INVOKABLE void setCurrentUrl(const QString &url);
    Q_INVOKABLE void setPageTitle(const QString &title);
    Q_INVOKABLE void setLoading(bool loading);
    Q_INVOKABLE void setCanGoBack(bool canGoBack);
    Q_INVOKABLE void setCanGoForward(bool canGoForward);

    Q_INVOKABLE void recordHistory(const QString &title, const QString &url = QString());

    Q_INVOKABLE void acceptDownloadRequest(QWebEngineDownloadRequest *request);
    Q_INVOKABLE int startDownload(const QString &url);
    Q_INVOKABLE void cancelDownload(int downloadId);
    Q_INVOKABLE void pauseDownload(int downloadId);
    Q_INVOKABLE void resumeDownload(int downloadId);
    Q_INVOKABLE void clearCompletedDownloads();

    // Privacy settings convenience invokables
    Q_INVOKABLE void setDoNotTrack(bool enabled);
    Q_INVOKABLE void setThirdPartyCookies(bool enabled);
    Q_INVOKABLE void setClearHistoryOnExit(bool enabled);
    Q_INVOKABLE void setClearCookiesOnExit(bool enabled);
    Q_INVOKABLE void setSendReferrer(bool enabled);
    Q_INVOKABLE void setJavascriptEnabled(bool enabled);
    Q_INVOKABLE void setPopupBlocking(bool enabled);

    void setActiveTabId(int tabId);

signals:
    void currentUrlChanged();
    void pageTitleChanged();
    void loadingChanged();
    void canGoBackChanged();
    void canGoForwardChanged();
    void tabsChanged();
    void activeTabIdChanged();

    void reloadRequested();
    void stopRequested();
    void backRequested();
    void forwardRequested();

private:
    void initializeHomePage();
    void emitPageChanged();
    void emitNavigationChanged();
    void emitNotification(const QString &title, const QString &message);
    void propagateNotificationManager();
    QString normalizeUrl(const QString &url) const;
    BrowserTab *activeTab() const;

    BrowserSession *m_session = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QString m_homeUrl;
};

} // namespace bos::shell
