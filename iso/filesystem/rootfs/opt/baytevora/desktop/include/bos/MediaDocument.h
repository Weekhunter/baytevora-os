#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents the media document currently loaded in the Media Player.
 */
class MediaDocument : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged FINAL)
    Q_PROPERTY(qint64 currentPosition READ currentPosition NOTIFY currentPositionChanged FINAL)
    Q_PROPERTY(QString mediaType READ mediaType NOTIFY mediaTypeChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged FINAL)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged FINAL)

public:
    explicit MediaDocument(QObject *parent = nullptr);

    QString filePath() const;
    QString fileName() const;
    qint64 duration() const;
    qint64 currentPosition() const;
    QString mediaType() const;
    bool loaded() const;
    bool playing() const;
    double volume() const;
    bool muted() const;

    void setFilePath(const QString &path);
    void setFileName(const QString &name);
    void setDuration(qint64 duration);
    void setCurrentPosition(qint64 position);
    void setMediaType(const QString &type);
    void setLoaded(bool loaded);
    void setPlaying(bool playing);
    void setVolume(double volume);
    void setMuted(bool muted);

signals:
    void filePathChanged();
    void fileNameChanged();
    void durationChanged();
    void currentPositionChanged();
    void mediaTypeChanged();
    void loadedChanged();
    void playingChanged();
    void volumeChanged();
    void mutedChanged();

private:
    QString m_filePath;
    QString m_fileName;
    qint64 m_duration = 0;
    qint64 m_currentPosition = 0;
    QString m_mediaType;
    bool m_loaded = false;
    bool m_playing = false;
    double m_volume = 1.0;
    bool m_muted = false;
};

} // namespace bos::shell
