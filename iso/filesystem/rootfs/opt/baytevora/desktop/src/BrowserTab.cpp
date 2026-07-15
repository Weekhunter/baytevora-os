#include "bos/BrowserTab.h"

namespace bos::shell {

BrowserTab::BrowserTab(int tabId, QObject *parent)
    : QObject(parent)
    , m_tabId(tabId)
{
}

BrowserTab::~BrowserTab() = default;

int BrowserTab::tabId() const { return m_tabId; }
QString BrowserTab::title() const { return m_title; }
QString BrowserTab::url() const { return m_url; }
bool BrowserTab::loading() const { return m_loading; }
bool BrowserTab::canGoBack() const { return m_canGoBack; }
bool BrowserTab::canGoForward() const { return m_canGoForward; }

void BrowserTab::setTitle(const QString &title)
{
    if (m_title == title) {
        return;
    }
    m_title = title;
    emit titleChanged();
}

void BrowserTab::setUrl(const QString &url)
{
    if (m_url == url) {
        return;
    }
    m_url = url;
    emit urlChanged();
}

void BrowserTab::setLoading(bool loading)
{
    if (m_loading == loading) {
        return;
    }
    m_loading = loading;
    emit loadingChanged();
}

void BrowserTab::setCanGoBack(bool canGoBack)
{
    if (m_canGoBack == canGoBack) {
        return;
    }
    m_canGoBack = canGoBack;
    emit canGoBackChanged();
}

void BrowserTab::setCanGoForward(bool canGoForward)
{
    if (m_canGoForward == canGoForward) {
        return;
    }
    m_canGoForward = canGoForward;
    emit canGoForwardChanged();
}

} // namespace bos::shell
