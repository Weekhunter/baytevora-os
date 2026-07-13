#include "bos/MediaPlayerManager.h"

#include <QAudioOutput>
#include <QDebug>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QUrl>

#include "bos/MediaDocument.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

MediaPlayerManager::MediaPlayerManager(QObject *parent)
    : QObject(parent)
    , m_document(new MediaDocument(this))
    , m_player(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
{
    m_player->setAudioOutput(m_audioOutput);

    connect(m_player, &QMediaPlayer::durationChanged,
            this, &MediaPlayerManager::onDurationChanged);
    connect(m_player, &QMediaPlayer::positionChanged,
            this, &MediaPlayerManager::onPositionChanged);
    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this, &MediaPlayerManager::onPlaybackStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged,
            this, &MediaPlayerManager::onMediaStatusChanged);
    connect(m_player, &QMediaPlayer::errorOccurred,
            this, &MediaPlayerManager::onErrorOccurred);

    syncVolumeToDocument();
    syncMuteToDocument();
}

MediaPlayerManager::~MediaPlayerManager() = default;

MediaDocument *MediaPlayerManager::document() const
{
    return m_document;
}

QObject *MediaPlayerManager::player() const
{
    return m_player;
}

void MediaPlayerManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void MediaPlayerManager::openMedia(const QString &path)
{
    if (!m_document || !m_player) {
        return;
    }

    QString localPath = path;
    if (localPath.startsWith(QStringLiteral("file:///"))) {
        localPath = localPath.mid(8);
    } else if (localPath.startsWith(QStringLiteral("file://"))) {
        localPath = localPath.mid(7);
    }

    const QFileInfo info(localPath);
    if (!info.exists() || !info.isFile()) {
        m_document->setLoaded(false);
        notifyError(QStringLiteral("Failed to Open Media."));
        return;
    }

    m_document->setFilePath(localPath);
    m_document->setFileName(info.fileName());
    m_document->setMediaType(detectMediaType(localPath));
    m_document->setLoaded(true);
    m_document->setCurrentPosition(0);

    m_player->setSource(QUrl::fromLocalFile(localPath));
    m_player->play();

    notifyInfo(QStringLiteral("Media Opened."));
    emit documentChanged();
    emit playerChanged();
}

void MediaPlayerManager::closeMedia()
{
    if (!m_document || !m_player) {
        return;
    }

    m_player->stop();
    m_player->setSource(QUrl());

    m_document->setFilePath(QString());
    m_document->setFileName(QString());
    m_document->setDuration(0);
    m_document->setCurrentPosition(0);
    m_document->setMediaType(QString());
    m_document->setLoaded(false);
    m_document->setPlaying(false);

    notifyInfo(QStringLiteral("Media Closed."));
    emit documentChanged();
}

void MediaPlayerManager::play()
{
    if (m_player && m_document && m_document->loaded()) {
        m_player->play();
    }
}

void MediaPlayerManager::pause()
{
    if (m_player) {
        m_player->pause();
    }
}

void MediaPlayerManager::stop()
{
    if (m_player) {
        m_player->stop();
    }
}

void MediaPlayerManager::togglePlayPause()
{
    if (!m_player || !m_document) {
        return;
    }
    if (m_document->playing()) {
        m_player->pause();
    } else if (m_document->loaded()) {
        m_player->play();
    }
}

void MediaPlayerManager::seek(qint64 position)
{
    if (m_player && m_document && m_document->loaded()) {
        m_player->setPosition(qBound(0LL, position, m_document->duration()));
    }
}

void MediaPlayerManager::setVolume(double value)
{
    if (!m_audioOutput || !m_document) {
        return;
    }
    const double clamped = qBound(0.0, value, 1.0);
    m_audioOutput->setVolume(clamped);
    m_document->setVolume(clamped);
}

void MediaPlayerManager::mute()
{
    if (m_audioOutput) {
        m_audioOutput->setMuted(true);
        if (m_document) {
            m_document->setMuted(true);
        }
    }
}

void MediaPlayerManager::unmute()
{
    if (m_audioOutput) {
        m_audioOutput->setMuted(false);
        if (m_document) {
            m_document->setMuted(false);
        }
    }
}

void MediaPlayerManager::toggleMute()
{
    if (!m_audioOutput || !m_document) {
        return;
    }
    const bool muted = !m_audioOutput->isMuted();
    m_audioOutput->setMuted(muted);
    m_document->setMuted(muted);
}

void MediaPlayerManager::onDurationChanged(qint64 duration)
{
    if (m_document) {
        m_document->setDuration(duration);
    }
}

void MediaPlayerManager::onPositionChanged(qint64 position)
{
    if (m_document) {
        m_document->setCurrentPosition(position);
    }
}

void MediaPlayerManager::onPlaybackStateChanged(QMediaPlayer::PlaybackState state)
{
    if (m_document) {
        m_document->setPlaying(state == QMediaPlayer::PlayingState);
    }
}

void MediaPlayerManager::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (!m_document) {
        return;
    }

    switch (status) {
    case QMediaPlayer::LoadedMedia:
        m_document->setLoaded(true);
        break;
    case QMediaPlayer::EndOfMedia:
        m_document->setPlaying(false);
        notifyInfo(QStringLiteral("Playback Finished."));
        emit playbackFinished();
        break;
    case QMediaPlayer::NoMedia:
        m_document->setLoaded(false);
        m_document->setPlaying(false);
        break;
    default:
        break;
    }
}

void MediaPlayerManager::onErrorOccurred(QMediaPlayer::Error /*error*/, const QString &errorString)
{
    if (m_document) {
        m_document->setLoaded(false);
        m_document->setPlaying(false);
    }
    notifyError(errorString.isEmpty() ? QStringLiteral("Failed to Open Media.") : errorString);
}

void MediaPlayerManager::notifyInfo(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Media Player"),
                                                  body,
                                                  QStringLiteral("Media Player"),
                                                  QStringLiteral("info"));
    }
}

void MediaPlayerManager::notifyError(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Media Player"),
                                                  body,
                                                  QStringLiteral("Media Player"),
                                                  QStringLiteral("error"));
    }
}

void MediaPlayerManager::syncVolumeToDocument()
{
    if (m_audioOutput && m_document) {
        m_document->setVolume(m_audioOutput->volume());
    }
}

void MediaPlayerManager::syncMuteToDocument()
{
    if (m_audioOutput && m_document) {
        m_document->setMuted(m_audioOutput->isMuted());
    }
}

QString MediaPlayerManager::detectMediaType(const QString &path)
{
    const QFileInfo info(path);
    const QString suffix = info.suffix().toLower();

    if (suffix == QStringLiteral("mp4") || suffix == QStringLiteral("webm")) {
        return QStringLiteral("Video");
    }
    if (suffix == QStringLiteral("mp3") || suffix == QStringLiteral("wav") || suffix == QStringLiteral("ogg")) {
        return QStringLiteral("Audio");
    }
    return QStringLiteral("Unknown");
}

} // namespace bos::shell
