#include "bos/MediaDocument.h"

#include <QFileInfo>

namespace bos::shell {

MediaDocument::MediaDocument(QObject *parent)
    : QObject(parent)
{
}

QString MediaDocument::filePath() const
{
    return m_filePath;
}

QString MediaDocument::fileName() const
{
    return m_fileName;
}

qint64 MediaDocument::duration() const
{
    return m_duration;
}

qint64 MediaDocument::currentPosition() const
{
    return m_currentPosition;
}

QString MediaDocument::mediaType() const
{
    return m_mediaType;
}

bool MediaDocument::loaded() const
{
    return m_loaded;
}

bool MediaDocument::playing() const
{
    return m_playing;
}

double MediaDocument::volume() const
{
    return m_volume;
}

bool MediaDocument::muted() const
{
    return m_muted;
}

void MediaDocument::setFilePath(const QString &path)
{
    if (m_filePath == path) {
        return;
    }
    m_filePath = path;
    emit filePathChanged();
}

void MediaDocument::setFileName(const QString &name)
{
    if (m_fileName == name) {
        return;
    }
    m_fileName = name;
    emit fileNameChanged();
}

void MediaDocument::setDuration(qint64 duration)
{
    if (m_duration == duration) {
        return;
    }
    m_duration = duration;
    emit durationChanged();
}

void MediaDocument::setCurrentPosition(qint64 position)
{
    if (m_currentPosition == position) {
        return;
    }
    m_currentPosition = position;
    emit currentPositionChanged();
}

void MediaDocument::setMediaType(const QString &type)
{
    if (m_mediaType == type) {
        return;
    }
    m_mediaType = type;
    emit mediaTypeChanged();
}

void MediaDocument::setLoaded(bool loaded)
{
    if (m_loaded == loaded) {
        return;
    }
    m_loaded = loaded;
    emit loadedChanged();
}

void MediaDocument::setPlaying(bool playing)
{
    if (m_playing == playing) {
        return;
    }
    m_playing = playing;
    emit playingChanged();
}

void MediaDocument::setVolume(double volume)
{
    if (qFuzzyCompare(m_volume, volume)) {
        return;
    }
    m_volume = volume;
    emit volumeChanged();
}

void MediaDocument::setMuted(bool muted)
{
    if (m_muted == muted) {
        return;
    }
    m_muted = muted;
    emit mutedChanged();
}

} // namespace bos::shell
