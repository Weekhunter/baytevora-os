#include "bos/BrowserDownloadManager.h"

#include <QDir>
#include <QStandardPaths>
#include <QWebEngineDownloadRequest>

#include "bos/BrowserDownload.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

BrowserDownloadManager::BrowserDownloadManager(QObject *parent)
    : QObject(parent)
{
}

BrowserDownloadManager::~BrowserDownloadManager()
{
    qDeleteAll(m_downloads);
    m_downloads.clear();
}

QVariantList BrowserDownloadManager::downloads() const
{
    QVariantList list;
    list.reserve(m_downloads.size());
    for (const BrowserDownload *download : m_downloads) {
        if (!download) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("downloadId"), download->downloadId());
        map.insert(QStringLiteral("fileName"), download->fileName());
        map.insert(QStringLiteral("sourceUrl"), download->sourceUrl());
        map.insert(QStringLiteral("destinationPath"), download->destinationPath());
        map.insert(QStringLiteral("totalBytes"), download->totalBytes());
        map.insert(QStringLiteral("receivedBytes"), download->receivedBytes());
        map.insert(QStringLiteral("progress"), download->progress());
        map.insert(QStringLiteral("state"), download->state());
        map.insert(QStringLiteral("mimeType"), download->mimeType());
        map.insert(QStringLiteral("startTime"), download->startTime());
        map.insert(QStringLiteral("finishTime"), download->finishTime());
        list.append(map);
    }
    return list;
}

int BrowserDownloadManager::activeCount() const
{
    int count = 0;
    for (const BrowserDownload *download : m_downloads) {
        if (download && (download->state() == QStringLiteral("pending")
                         || download->state() == QStringLiteral("downloading"))) {
            ++count;
        }
    }
    return count;
}

int BrowserDownloadManager::completedCount() const
{
    int count = 0;
    for (const BrowserDownload *download : m_downloads) {
        if (download && download->state() == QStringLiteral("completed")) {
            ++count;
        }
    }
    return count;
}

void BrowserDownloadManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int BrowserDownloadManager::startDownload(const QString &url)
{
    if (url.isEmpty()) {
        return -1;
    }

    const int id = generateDownloadId();
    auto *download = new BrowserDownload(id, this);
    download->setSourceUrl(url);
    download->setState(QStringLiteral("pending"));
    download->setStartTime(QDateTime::currentDateTime());
    m_downloads.append(download);

    emit downloadsChanged();
    emit activeCountChanged();

    emit manualDownloadRequested(id, url);
    return id;
}

void BrowserDownloadManager::acceptDownloadRequest(QWebEngineDownloadRequest *request)
{
    if (!request) {
        return;
    }

    BrowserDownload *download = findPendingByUrl(request->url().toString());
    if (!download) {
        const int id = generateDownloadId();
        download = new BrowserDownload(id, this);
        download->setSourceUrl(request->url().toString());
        download->setStartTime(QDateTime::currentDateTime());
        m_downloads.append(download);
    }

    const QString fileName = request->downloadFileName();
    download->setFileName(fileName);
    download->setMimeType(request->mimeType());

    QString directory = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    if (directory.isEmpty()) {
        directory = QDir::homePath() + QStringLiteral("/Downloads");
    }
    QDir dir(directory);
    if (!dir.exists() && !dir.mkpath(QStringLiteral("."))) {
        directory = QDir::homePath();
    }

    const QString fullPath = QDir(directory).absoluteFilePath(fileName);
    download->setDestinationPath(fullPath);
    download->setState(QStringLiteral("downloading"));

    download->setRequest(request);
    request->acceptWithPath(fullPath);

    emit downloadsChanged();
    emit activeCountChanged();
    emit completedCountChanged();

    emitNotification(QStringLiteral("Download Started"),
                     QStringLiteral("%1 started").arg(fileName));

    connect(download, &BrowserDownload::stateChanged, this, [this, download]() {
        if (!download) {
            return;
        }
        const QString state = download->state();
        if (state == QStringLiteral("completed")) {
            emitNotification(QStringLiteral("Download Completed"),
                           QStringLiteral("%1 finished").arg(download->fileName()));
        } else if (state == QStringLiteral("failed")) {
            emitNotification(QStringLiteral("Download Failed"),
                           QStringLiteral("%1 failed").arg(download->fileName()));
        } else if (state == QStringLiteral("cancelled")) {
            emitNotification(QStringLiteral("Download Cancelled"),
                           QStringLiteral("%1 cancelled").arg(download->fileName()));
        }
        emit downloadsChanged();
        emit activeCountChanged();
        emit completedCountChanged();
    });

    connect(download, &BrowserDownload::progressChanged, this, [this, download]() {
        if (download && download->state() == QStringLiteral("downloading")) {
            emit downloadsChanged();
        }
    });
}

void BrowserDownloadManager::cancelDownload(int downloadId)
{
    BrowserDownload *download = findDownload(downloadId);
    if (!download) {
        return;
    }
    download->cancel();
}

void BrowserDownloadManager::pauseDownload(int downloadId)
{
    BrowserDownload *download = findDownload(downloadId);
    if (!download) {
        return;
    }
    download->pause();
}

void BrowserDownloadManager::resumeDownload(int downloadId)
{
    BrowserDownload *download = findDownload(downloadId);
    if (!download) {
        return;
    }
    download->resume();
}

void BrowserDownloadManager::clearCompleted()
{
    for (int i = m_downloads.size() - 1; i >= 0; --i) {
        BrowserDownload *download = m_downloads.at(i);
        if (download && download->isTerminalState()) {
            m_downloads.removeAt(i);
            delete download;
        }
    }
    emit downloadsChanged();
    emit activeCountChanged();
    emit completedCountChanged();
}

BrowserDownload *BrowserDownloadManager::findDownload(int downloadId) const
{
    for (BrowserDownload *download : m_downloads) {
        if (download && download->downloadId() == downloadId) {
            return download;
        }
    }
    return nullptr;
}

BrowserDownload *BrowserDownloadManager::findPendingByUrl(const QString &url) const
{
    for (BrowserDownload *download : m_downloads) {
        if (download
            && download->state() == QStringLiteral("pending")
            && download->sourceUrl() == url) {
            return download;
        }
    }
    return nullptr;
}

int BrowserDownloadManager::generateDownloadId()
{
    return m_nextDownloadId++;
}

void BrowserDownloadManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                            QStringLiteral("Browser"),
                                            QStringLiteral("info"));
}

} // namespace bos::shell
