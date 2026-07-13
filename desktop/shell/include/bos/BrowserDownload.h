#pragma once

#include <QDateTime>
#include <QObject>
#include <QPointer>
#include <QString>

QT_BEGIN_NAMESPACE
class QWebEngineDownloadRequest;
QT_END_NAMESPACE

namespace bos::shell {

/**
 * @brief Represents the state of a single browser download.
 *
 * BrowserDownload mirrors a Qt WebEngine download request and exposes a
 * stable, QML-friendly set of properties for the download list UI.
 */
class BrowserDownload : public QObject {
    Q_OBJECT

    Q_PROPERTY(int downloadId READ downloadId NOTIFY downloadIdChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(QString sourceUrl READ sourceUrl NOTIFY sourceUrlChanged FINAL)
    Q_PROPERTY(QString destinationPath READ destinationPath NOTIFY destinationPathChanged FINAL)
    Q_PROPERTY(qint64 totalBytes READ totalBytes NOTIFY totalBytesChanged FINAL)
    Q_PROPERTY(qint64 receivedBytes READ receivedBytes NOTIFY receivedBytesChanged FINAL)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged FINAL)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY mimeTypeChanged FINAL)
    Q_PROPERTY(QDateTime startTime READ startTime NOTIFY startTimeChanged FINAL)
    Q_PROPERTY(QDateTime finishTime READ finishTime NOTIFY finishTimeChanged FINAL)

public:
    explicit BrowserDownload(int downloadId, QObject *parent = nullptr);
    ~BrowserDownload() override;

    int downloadId() const;
    QString fileName() const;
    QString sourceUrl() const;
    QString destinationPath() const;
    qint64 totalBytes() const;
    qint64 receivedBytes() const;
    int progress() const;
    QString state() const;
    QString mimeType() const;
    QDateTime startTime() const;
    QDateTime finishTime() const;

    void setFileName(const QString &fileName);
    void setSourceUrl(const QString &sourceUrl);
    void setDestinationPath(const QString &destinationPath);
    void setTotalBytes(qint64 totalBytes);
    void setReceivedBytes(qint64 receivedBytes);
    void setState(const QString &state);
    void setMimeType(const QString &mimeType);
    void setStartTime(const QDateTime &startTime);
    void setFinishTime(const QDateTime &finishTime);

    void setRequest(QWebEngineDownloadRequest *request);

    Q_INVOKABLE void cancel();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();

    bool isTerminalState() const;

signals:
    void downloadIdChanged();
    void fileNameChanged();
    void sourceUrlChanged();
    void destinationPathChanged();
    void totalBytesChanged();
    void receivedBytesChanged();
    void progressChanged();
    void stateChanged();
    void mimeTypeChanged();
    void startTimeChanged();
    void finishTimeChanged();

private:
    void onStateChanged();
    void onReceivedBytesChanged();
    void onTotalBytesChanged();
    void updateProgress();

    int m_downloadId = -1;
    QString m_fileName;
    QString m_sourceUrl;
    QString m_destinationPath;
    qint64 m_totalBytes = 0;
    qint64 m_receivedBytes = 0;
    int m_progress = 0;
    QString m_state = QStringLiteral("pending");
    QString m_mimeType;
    QDateTime m_startTime;
    QDateTime m_finishTime;

    QPointer<QWebEngineDownloadRequest> m_request;
};

} // namespace bos::shell
