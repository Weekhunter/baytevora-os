#include "bos/BrowserBookmark.h"

namespace bos::shell {

BrowserBookmark::BrowserBookmark(int bookmarkId, QObject *parent)
    : QObject(parent)
    , m_bookmarkId(bookmarkId)
{
}

BrowserBookmark::~BrowserBookmark() = default;

int BrowserBookmark::bookmarkId() const { return m_bookmarkId; }
QString BrowserBookmark::title() const { return m_title; }
QString BrowserBookmark::url() const { return m_url; }
QString BrowserBookmark::folder() const { return m_folder; }
QDateTime BrowserBookmark::createdAt() const { return m_createdAt; }
QDateTime BrowserBookmark::lastVisited() const { return m_lastVisited; }

void BrowserBookmark::setTitle(const QString &title)
{
    if (m_title == title) {
        return;
    }
    m_title = title;
    emit titleChanged();
}

void BrowserBookmark::setUrl(const QString &url)
{
    if (m_url == url) {
        return;
    }
    m_url = url;
    emit urlChanged();
}

void BrowserBookmark::setFolder(const QString &folder)
{
    if (m_folder == folder) {
        return;
    }
    m_folder = folder;
    emit folderChanged();
}

void BrowserBookmark::setCreatedAt(const QDateTime &createdAt)
{
    if (m_createdAt == createdAt) {
        return;
    }
    m_createdAt = createdAt;
    emit createdAtChanged();
}

void BrowserBookmark::setLastVisited(const QDateTime &lastVisited)
{
    if (m_lastVisited == lastVisited) {
        return;
    }
    m_lastVisited = lastVisited;
    emit lastVisitedChanged();
}

} // namespace bos::shell
