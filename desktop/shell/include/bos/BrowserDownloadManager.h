#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

QT_BEGIN_NAMESPACE
class QWebEngineDownloadRequest;
QT_END_NAMESPACE

namespace bos::shell {

class BrowserDownload;
class NotificationManager;

/**
 * @brief Maintains the list of downloads for a single browser window/session.
 *
 * BrowserDownloadManager accepts download requests from WebEngine, tracks
 * progress, and exposes the download model to QML.
 */
class BrowserDownloadManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList downloads READ downloads NOTIFY downloadsChanged FINAL)
    Q_PROPERTY(int activeCount READ activeCount NOTIFY activeCountChanged FINAL)
    Q_PROPERTY(int completedCount READ completedCount NOTIFY completedCountChanged FINAL)

public:
    explicit BrowserDownloadManager(QObject *parent = nullptr);
    ~BrowserDownloadManager() override;

    QVariantList downloads() const;
    int activeCount() const;
    int completedCount() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int startDownload(const QString &url);
    Q_INVOKABLE void acceptDownloadRequest(QWebEngineDownloadRequest *request);
    Q_INVOKABLE void cancelDownload(int downloadId);
    Q_INVOKABLE void pauseDownload(int downloadId);
    Q_INVOKABLE void resumeDownload(int downloadId);
    Q_INVOKABLE void clearCompleted();

signals:
    void downloadsChanged();
    void activeCountChanged();
    void completedCountChanged();

    void manualDownloadRequested(int downloadId, const QString &url);

private:
    BrowserDownload *findDownload(int downloadId) const;
    BrowserDownload *findPendingByUrl(const QString &url) const;
    int generateDownloadId();
    void emitNotification(const QString &title, const QString &message);

    QList<BrowserDownload*> m_downloads;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextDownloadId = 1;
};

} // namespace bos::shell
