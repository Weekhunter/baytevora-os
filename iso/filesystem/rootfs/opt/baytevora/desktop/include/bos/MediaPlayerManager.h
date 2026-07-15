#pragma once

#include <QObject>

QT_BEGIN_NAMESPACE
class QAudioOutput;
class QMediaPlayer;
QT_END_NAMESPACE

namespace bos::shell {

class MediaDocument;
class NotificationManager;

/**
 * @brief Manages media playback state for one Media Player window.
 *
 * MediaPlayerManager owns the current MediaDocument and a Qt Multimedia
 * QMediaPlayer. It exposes the player and document to QML and provides
 * invokable playback controls.
 */
class MediaPlayerManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(MediaDocument *document READ document NOTIFY documentChanged FINAL)
    Q_PROPERTY(QObject *player READ player NOTIFY playerChanged FINAL)

public:
    explicit MediaPlayerManager(QObject *parent = nullptr);
    ~MediaPlayerManager() override;

    MediaDocument *document() const;
    QObject *player() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void openMedia(const QString &path);
    Q_INVOKABLE void closeMedia();
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void togglePlayPause();
    Q_INVOKABLE void seek(qint64 position);
    Q_INVOKABLE void setVolume(double value);
    Q_INVOKABLE void mute();
    Q_INVOKABLE void unmute();
    Q_INVOKABLE void toggleMute();

private slots:
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onErrorOccurred(QMediaPlayer::Error error, const QString &errorString);

signals:
    void documentChanged();
    void playerChanged();
    void playbackFinished();

private:
    void notifyInfo(const QString &body);
    void notifyError(const QString &body);
    void syncVolumeToDocument();
    void syncMuteToDocument();
    static QString detectMediaType(const QString &path);

    MediaDocument *m_document = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
};

} // namespace bos::shell
