#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <QTimer>

namespace bos::shell {

class ImageViewerManager;

/**
 * @brief Manages slideshow playback for an Image Viewer window.
 *
 * ImageSlideshowManager advances through the images in the current folder on
 * a configurable interval. It uses ImageViewerManager to open each image.
 */
class ImageSlideshowManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged FINAL)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged FINAL)
    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY imageChanged FINAL)
    Q_PROPERTY(int imageCount READ imageCount NOTIFY imageChanged FINAL)

public:
    explicit ImageSlideshowManager(QObject *parent = nullptr);
    ~ImageSlideshowManager() override;

    bool running() const;
    int interval() const;
    void setInterval(int interval);
    int currentIndex() const;
    int imageCount() const;

    Q_INVOKABLE void setViewerManager(QObject *manager);

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void setFolderImages(const QStringList &paths);
    Q_INVOKABLE void setCurrentFolderPath(const QString &folderPath);

signals:
    void runningChanged();
    void intervalChanged();
    void imageChanged();

private:
    void advance(int direction);
    void refreshFolder();

    ImageViewerManager *m_viewerManager = nullptr;
    QStringList m_imagePaths;
    QString m_folderPath;
    int m_currentIndex = -1;
    QTimer m_timer;
    bool m_running = false;
    int m_interval = 5000;
};

} // namespace bos::shell
