#include "bos/BrowserDownload.h"

#include <QDir>
#include <QStandardPaths>
#include <QWebEngineDownloadRequest>

namespace bos::shell {

BrowserDownload::BrowserDownload(int downloadId, QObject *parent)
    : QObject(parent)
    , m_downloadId(downloadId)
{
}

BrowserDownload::~BrowserDownload() = default;

int BrowserDownload::downloadId() const { return m_downloadId; }
QString BrowserDownload::fileName() const { return m_fileName; }
QString BrowserDownload::sourceUrl() const { return m_sourceUrl; }
QString BrowserDownload::destinationPath() const { return m_destinationPath; }
qint64 BrowserDownload::totalBytes() const { return m_totalBytes; }
qint64 BrowserDownload::receivedBytes() const { return m_receivedBytes; }
int BrowserDownload::progress() const { return m_progress; }
QString BrowserDownload::state() const { return m_state; }
QString BrowserDownload::mimeType() const { return m_mimeType; }
QDateTime BrowserDownload::startTime() const { return m_startTime; }
QDateTime BrowserDownload::finishTime() const { return m_finishTime; }

void BrowserDownload::setFileName(const QString &fileName)
{
    if (m_fileName == fileName) {
        return;
    }
    m_fileName = fileName;
    emit fileNameChanged();
}

void BrowserDownload::setSourceUrl(const QString &sourceUrl)
{
    if (m_sourceUrl == sourceUrl) {
        return;
    }
    m_sourceUrl = sourceUrl;
    emit sourceUrlChanged();
}

void BrowserDownload::setDestinationPath(const QString &destinationPath)
{
    if (m_destinationPath == destinationPath) {
        return;
    }
    m_destinationPath = destinationPath;
    emit destinationPathChanged();
}

void BrowserDownload::setTotalBytes(qint64 totalBytes)
{
    if (m_totalBytes == totalBytes) {
        return;
    }
    m_totalBytes = totalBytes;
    emit totalBytesChanged();
    updateProgress();
}

void BrowserDownload::setReceivedBytes(qint64 receivedBytes)
{
    if (m_receivedBytes == receivedBytes) {
        return;
    }
    m_receivedBytes = receivedBytes;
    emit receivedBytesChanged();
    updateProgress();
}

void BrowserDownload::setState(const QString &state)
{
    if (m_state == state) {
        return;
    }
    m_state = state;
    emit stateChanged();
}

void BrowserDownload::setMimeType(const QString &mimeType)
{
    if (m_mimeType == mimeType) {
        return;
    }
    m_mimeType = mimeType;
    emit mimeTypeChanged();
}

void BrowserDownload::setStartTime(const QDateTime &startTime)
{
    if (m_startTime == startTime) {
        return;
    }
    m_startTime = startTime;
    emit startTimeChanged();
}

void BrowserDownload::setFinishTime(const QDateTime &finishTime)
{
    if (m_finishTime == finishTime) {
        return;
    }
    m_finishTime = finishTime;
    emit finishTimeChanged();
}

void BrowserDownload::setRequest(QWebEngineDownloadRequest *request)
{
    if (!request || m_request.data() == request) {
        return;
    }
    m_request = request;

    setFileName(request->downloadFileName());
    setMimeType(request->mimeType());
    setTotalBytes(request->totalBytes());
    setReceivedBytes(request->receivedBytes());
    onStateChanged();

    connect(request, &QWebEngineDownloadRequest::stateChanged,
            this, &BrowserDownload::onStateChanged);
    connect(request, &QWebEngineDownloadRequest::receivedBytesChanged,
            this, &BrowserDownload::onReceivedBytesChanged);
    connect(request, &QWebEngineDownloadRequest::totalBytesChanged,
            this, &BrowserDownload::onTotalBytesChanged);
}

void BrowserDownload::cancel()
{
    if (m_request && !isTerminalState()) {
        m_request->cancel();
    }
}

void BrowserDownload::pause()
{
    if (m_request && m_state == QStringLiteral("downloading")) {
        m_request->pause();
        setState(QStringLiteral("paused"));
    }
}

void BrowserDownload::resume()
{
    if (m_request && m_state == QStringLiteral("paused")) {
        m_request->resume();
        setState(QStringLiteral("downloading"));
    }
}

bool BrowserDownload::isTerminalState() const
{
    return m_state == QStringLiteral("completed")
           || m_state == QStringLiteral("cancelled")
           || m_state == QStringLiteral("failed");
}

void BrowserDownload::onStateChanged()
{
    QWebEngineDownloadRequest *request = m_request.data();
    if (!request) {
        return;
    }

    QString newState;
    switch (request->state()) {
    case QWebEngineDownloadRequest::DownloadRequested:
        newState = QStringLiteral("pending");
        break;
    case QWebEngineDownloadRequest::DownloadInProgress:
        newState = QStringLiteral("downloading");
        break;
    case QWebEngineDownloadRequest::DownloadCompleted:
        newState = QStringLiteral("completed");
        break;
    case QWebEngineDownloadRequest::DownloadCancelled:
        newState = QStringLiteral("cancelled");
        break;
    default:
        newState = QStringLiteral("failed");
        break;
    }

    setState(newState);
    setReceivedBytes(request->receivedBytes());
    setTotalBytes(request->totalBytes());

    if (isTerminalState()) {
        setFinishTime(QDateTime::currentDateTime());
    }
}

void BrowserDownload::onReceivedBytesChanged()
{
    QWebEngineDownloadRequest *request = m_request.data();
    if (request) {
        setReceivedBytes(request->receivedBytes());
    }
}

void BrowserDownload::onTotalBytesChanged()
{
    QWebEngineDownloadRequest *request = m_request.data();
    if (request) {
        setTotalBytes(request->totalBytes());
    }
}

void BrowserDownload::updateProgress()
{
    int progress = 0;
    if (m_totalBytes > 0) {
        progress = static_cast<int>((m_receivedBytes * 100) / m_totalBytes);
    } else if (m_state == QStringLiteral("completed")) {
        progress = 100;
    }
    if (progress > 100) {
        progress = 100;
    }
    if (m_progress != progress) {
        m_progress = progress;
        emit progressChanged();
    }
}

} // namespace bos::shell
