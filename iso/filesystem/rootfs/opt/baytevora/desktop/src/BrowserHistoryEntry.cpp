#include "bos/BrowserHistoryEntry.h"

namespace bos::shell {

BrowserHistoryEntry::BrowserHistoryEntry(int historyId, QObject *parent)
    : QObject(parent)
    , m_historyId(historyId)
{
}

BrowserHistoryEntry::~BrowserHistoryEntry() = default;

int BrowserHistoryEntry::historyId() const { return m_historyId; }
QString BrowserHistoryEntry::title() const { return m_title; }
QString BrowserHistoryEntry::url() const { return m_url; }
QDateTime BrowserHistoryEntry::visitTime() const { return m_visitTime; }
int BrowserHistoryEntry::visitCount() const { return m_visitCount; }

void BrowserHistoryEntry::setTitle(const QString &title)
{
    if (m_title == title) {
        return;
    }
    m_title = title;
    emit titleChanged();
}

void BrowserHistoryEntry::setUrl(const QString &url)
{
    if (m_url == url) {
        return;
    }
    m_url = url;
    emit urlChanged();
}

void BrowserHistoryEntry::setVisitTime(const QDateTime &visitTime)
{
    if (m_visitTime == visitTime) {
        return;
    }
    m_visitTime = visitTime;
    emit visitTimeChanged();
}

void BrowserHistoryEntry::setVisitCount(int visitCount)
{
    if (m_visitCount == visitCount) {
        return;
    }
    m_visitCount = visitCount;
    emit visitCountChanged();
}

void BrowserHistoryEntry::incrementVisitCount()
{
    ++m_visitCount;
    emit visitCountChanged();
}

} // namespace bos::shell
