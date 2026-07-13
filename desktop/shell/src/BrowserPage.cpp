#include "bos/BrowserPage.h"

namespace bos::shell {

BrowserPage::BrowserPage(QObject *parent)
    : QObject(parent)
{
}

BrowserPage::~BrowserPage() = default;

QString BrowserPage::currentUrl() const
{
    return m_currentUrl;
}

void BrowserPage::setCurrentUrl(const QString &url)
{
    if (m_currentUrl == url) {
        return;
    }
    m_currentUrl = url;
    emit currentUrlChanged();
}

QString BrowserPage::pageTitle() const
{
    return m_pageTitle;
}

void BrowserPage::setPageTitle(const QString &title)
{
    if (m_pageTitle == title) {
        return;
    }
    m_pageTitle = title;
    emit pageTitleChanged();
}

bool BrowserPage::loading() const
{
    return m_loading;
}

void BrowserPage::setLoading(bool loading)
{
    if (m_loading == loading) {
        return;
    }
    m_loading = loading;
    emit loadingChanged();
}

} // namespace bos::shell
