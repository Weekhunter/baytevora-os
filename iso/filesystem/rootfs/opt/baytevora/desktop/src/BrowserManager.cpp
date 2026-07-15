#include "bos/BrowserManager.h"

#include <QDebug>
#include <QUrl>
#include <QWebEngineDownloadRequest>

#include "bos/BrowserSession.h"
#include "bos/BrowserTab.h"
#include "bos/BrowserDownloadManager.h"
#include "bos/BrowserBookmarkManager.h"
#include "bos/BrowserHistoryManager.h"
#include "bos/BrowserPermissionManager.h"
#include "bos/BrowserPrivacySettings.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserManager::BrowserManager(QObject *parent)
    : QObject(parent)
    , m_session(new BrowserSession(this))
{
    initializeHomePage();

    // Open a single default home tab when the browser window is created.
    newTab(m_homeUrl);
}

BrowserManager::~BrowserManager() = default;

QString BrowserManager::currentUrl() const
{
    BrowserTab *tab = activeTab();
    return tab ? tab->url() : QString();
}

QString BrowserManager::pageTitle() const
{
    BrowserTab *tab = activeTab();
    return tab ? tab->title() : QString();
}

bool BrowserManager::loading() const
{
    BrowserTab *tab = activeTab();
    return tab ? tab->loading() : false;
}

bool BrowserManager::canGoBack() const
{
    BrowserTab *tab = activeTab();
    return tab ? tab->canGoBack() : false;
}

bool BrowserManager::canGoForward() const
{
    BrowserTab *tab = activeTab();
    return tab ? tab->canGoForward() : false;
}

QVariantList BrowserManager::tabs() const
{
    return m_session ? m_session->tabs() : QVariantList();
}

int BrowserManager::activeTabId() const
{
    return m_session ? m_session->activeTabId() : -1;
}

BrowserDownloadManager *BrowserManager::downloadManager() const
{
    return m_session ? m_session->downloadManager() : nullptr;
}

BrowserBookmarkManager *BrowserManager::bookmarkManager() const
{
    return m_session ? m_session->bookmarkManager() : nullptr;
}

BrowserHistoryManager *BrowserManager::historyManager() const
{
    return m_session ? m_session->historyManager() : nullptr;
}

BrowserPermissionManager *BrowserManager::permissionManager() const
{
    return m_session ? m_session->permissionManager() : nullptr;
}

BrowserPrivacySettings *BrowserManager::privacySettings() const
{
    return m_session ? m_session->privacySettings() : nullptr;
}

void BrowserManager::setNotificationManager(QObject *notificationManager)
{
    m_notificationManager = qobject_cast<NotificationManager *>(notificationManager);
    propagateNotificationManager();
}

void BrowserManager::navigate(const QString &url)
{
    BrowserTab *tab = activeTab();
    if (!tab || url.isEmpty()) {
        return;
    }
    setCurrentUrl(normalizeUrl(url));
}

void BrowserManager::reload()
{
    emit reloadRequested();
}

void BrowserManager::stop()
{
    emit stopRequested();
}

void BrowserManager::goHome()
{
    navigate(m_homeUrl);
    BrowserTab *tab = activeTab();
    if (tab) {
        tab->setTitle(QStringLiteral("Home"));
    }
    emitPageChanged();
}

void BrowserManager::goBack()
{
    emit backRequested();
}

void BrowserManager::goForward()
{
    emit forwardRequested();
}

int BrowserManager::newTab(const QString &url)
{
    if (!m_session) {
        return -1;
    }

    const QString target = url.isEmpty() ? m_homeUrl : normalizeUrl(url);
    BrowserTab *tab = m_session->addTab(target, QStringLiteral("New Tab"));
    if (!tab) {
        return -1;
    }

    m_session->setActiveTabId(tab->tabId());
    emitPageChanged();
    emitNavigationChanged();
    emit tabsChanged();
    emit activeTabIdChanged();

    emitNotification(QStringLiteral("New Tab Opened"), QStringLiteral("Tab %1 opened").arg(tab->tabId()));
    return tab->tabId();
}

void BrowserManager::closeTab(int tabId)
{
    if (!m_session || tabId < 0) {
        return;
    }

    if (m_session->tabCount() <= 1) {
        // Keep at least one tab open; reset it to home.
        BrowserTab *tab = m_session->activeTab();
        if (tab) {
            tab->setUrl(m_homeUrl);
            tab->setTitle(QStringLiteral("Home"));
            tab->setLoading(false);
            tab->setCanGoBack(false);
            tab->setCanGoForward(false);
            emitPageChanged();
            emitNavigationChanged();
            emit tabsChanged();
        }
        emitNotification(QStringLiteral("Tab Closed"),
                       QStringLiteral("Last tab reset to home"));
        return;
    }

    if (m_session->removeTab(tabId)) {
        emitPageChanged();
        emitNavigationChanged();
        emit tabsChanged();
        emit activeTabIdChanged();
        emitNotification(QStringLiteral("Tab Closed"),
                       QStringLiteral("Tab %1 closed").arg(tabId));
    }
}

void BrowserManager::switchTab(int tabId)
{
    if (!m_session || m_session->activeTabId() == tabId) {
        return;
    }
    m_session->setActiveTabId(tabId);
    emitPageChanged();
    emitNavigationChanged();
    emit activeTabIdChanged();
}

void BrowserManager::duplicateTab(int tabId)
{
    if (!m_session) {
        return;
    }
    BrowserTab *tab = m_session->duplicateTab(tabId);
    if (!tab) {
        return;
    }
    m_session->setActiveTabId(tab->tabId());
    emitPageChanged();
    emitNavigationChanged();
    emit tabsChanged();
    emit activeTabIdChanged();
    emitNotification(QStringLiteral("New Tab Opened"),
                   QStringLiteral("Tab %1 duplicated").arg(tab->tabId()));
}

void BrowserManager::moveTab(int fromIndex, int toIndex)
{
    if (!m_session) {
        return;
    }
    m_session->moveTab(fromIndex, toIndex);
}

void BrowserManager::restoreClosedTab()
{
    if (!m_session) {
        return;
    }
    BrowserTab *tab = m_session->takeLastClosed();
    if (!tab) {
        return;
    }
    emitPageChanged();
    emitNavigationChanged();
    emit tabsChanged();
    emit activeTabIdChanged();
    emitNotification(QStringLiteral("New Tab Opened"),
                   QStringLiteral("Closed tab restored"));
}

void BrowserManager::setCurrentUrl(const QString &url)
{
    BrowserTab *tab = activeTab();
    if (!tab || tab->url() == url) {
        return;
    }
    tab->setUrl(url);
    emitPageChanged();
}

void BrowserManager::setPageTitle(const QString &title)
{
    BrowserTab *tab = activeTab();
    if (!tab || tab->title() == title) {
        return;
    }
    tab->setTitle(title);
    emit pageTitleChanged();
    emit tabsChanged();
}

void BrowserManager::setLoading(bool loading)
{
    BrowserTab *tab = activeTab();
    if (!tab || tab->loading() == loading) {
        return;
    }
    tab->setLoading(loading);
    emit loadingChanged();
    emit tabsChanged();
}

void BrowserManager::setCanGoBack(bool canGoBack)
{
    BrowserTab *tab = activeTab();
    if (!tab || tab->canGoBack() == canGoBack) {
        return;
    }
    tab->setCanGoBack(canGoBack);
    emitNavigationChanged();
    emit tabsChanged();
}

void BrowserManager::setCanGoForward(bool canGoForward)
{
    BrowserTab *tab = activeTab();
    if (!tab || tab->canGoForward() == canGoForward) {
        return;
    }
    tab->setCanGoForward(canGoForward);
    emitNavigationChanged();
    emit tabsChanged();
}

void BrowserManager::recordHistory(const QString &title, const QString &url)
{
    if (!m_session || !m_session->historyManager()) {
        return;
    }
    const QString target = url.isEmpty() ? currentUrl() : url;
    m_session->historyManager()->recordVisit(title, target);
}

void BrowserManager::acceptDownloadRequest(QWebEngineDownloadRequest *request)
{
    if (!m_session || !m_session->downloadManager()) {
        return;
    }
    m_session->downloadManager()->acceptDownloadRequest(request);
}

int BrowserManager::startDownload(const QString &url)
{
    if (!m_session || !m_session->downloadManager()) {
        return -1;
    }
    return m_session->downloadManager()->startDownload(url);
}

void BrowserManager::cancelDownload(int downloadId)
{
    if (!m_session || !m_session->downloadManager()) {
        return;
    }
    m_session->downloadManager()->cancelDownload(downloadId);
}

void BrowserManager::pauseDownload(int downloadId)
{
    if (!m_session || !m_session->downloadManager()) {
        return;
    }
    m_session->downloadManager()->pauseDownload(downloadId);
}

void BrowserManager::resumeDownload(int downloadId)
{
    if (!m_session || !m_session->downloadManager()) {
        return;
    }
    m_session->downloadManager()->resumeDownload(downloadId);
}

void BrowserManager::clearCompletedDownloads()
{
    if (!m_session || !m_session->downloadManager()) {
        return;
    }
    m_session->downloadManager()->clearCompleted();
}

void BrowserManager::setDoNotTrack(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setDoNotTrackEnabled(enabled);
}

void BrowserManager::setThirdPartyCookies(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setBlockThirdPartyCookies(enabled);
}

void BrowserManager::setClearHistoryOnExit(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setClearHistoryOnExit(enabled);
}

void BrowserManager::setClearCookiesOnExit(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setClearCookiesOnExit(enabled);
}

void BrowserManager::setSendReferrer(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setSendReferrer(enabled);
}

void BrowserManager::setJavascriptEnabled(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setJavascriptEnabled(enabled);
}

void BrowserManager::setPopupBlocking(bool enabled)
{
    if (!m_session || !m_session->privacySettings()) {
        return;
    }
    m_session->privacySettings()->setPopupsBlocked(enabled);
}

void BrowserManager::setActiveTabId(int tabId)
{
    if (!m_session) {
        return;
    }
    m_session->setActiveTabId(tabId);
    emitPageChanged();
    emitNavigationChanged();
    emit activeTabIdChanged();
}

void BrowserManager::initializeHomePage()
{
    const QString html = QStringLiteral(
        "<!DOCTYPE html>"
        "<html><head><meta charset=\"UTF-8\"><title>Home</title>"
        "<style>"
        "body{font-family:system-ui,-apple-system,sans-serif;background:#0f172a;color:#f8fafc;"
        "display:flex;flex-direction:column;align-items:center;justify-content:center;height:100vh;margin:0;}"
        "h1{font-size:2.5rem;font-weight:700;margin:0 0 0.5rem;}"
        "h2{font-size:1.25rem;font-weight:500;color:#94a3b8;margin:0 0 1.5rem;}"
        "p{font-size:1rem;color:#cbd5e1;}"
        "</style></head><body>"
        "<h1>Baytevora Browser</h1>"
        "<h2>BOS Alpha</h2>"
        "<p>Welcome to the Baytevora Browser Foundation.</p>"
        "</body></html>");

    m_homeUrl = QStringLiteral("data:text/html;charset=utf-8,") + QUrl::toPercentEncoding(html);
}

void BrowserManager::emitPageChanged()
{
    emit currentUrlChanged();
    emit pageTitleChanged();
    emit loadingChanged();
    emit tabsChanged();
}

void BrowserManager::emitNavigationChanged()
{
    emit canGoBackChanged();
    emit canGoForwardChanged();
    emit tabsChanged();
}

void BrowserManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Browser"),
                                              QStringLiteral("info"));
}

void BrowserManager::propagateNotificationManager()
{
    if (!m_session) {
        return;
    }
    if (m_session->downloadManager()) {
        m_session->downloadManager()->setNotificationManager(m_notificationManager);
    }
    if (m_session->bookmarkManager()) {
        m_session->bookmarkManager()->setNotificationManager(m_notificationManager);
    }
    if (m_session->historyManager()) {
        m_session->historyManager()->setNotificationManager(m_notificationManager);
    }
    if (m_session->permissionManager()) {
        m_session->permissionManager()->setNotificationManager(m_notificationManager);
    }
    if (m_session->privacySettings()) {
        m_session->privacySettings()->setNotificationManager(m_notificationManager);
    }
}

QString BrowserManager::normalizeUrl(const QString &url) const
{
    if (url.isEmpty()) {
        return m_homeUrl;
    }
    if (url.startsWith(QStringLiteral("data:"))) {
        return url;
    }
    if (!url.contains(QStringLiteral("://")) && !url.startsWith(QStringLiteral("about:"))) {
        return QStringLiteral("https://") + url;
    }
    return url;
}

BrowserTab *BrowserManager::activeTab() const
{
    return m_session ? m_session->activeTab() : nullptr;
}

} // namespace bos::shell
