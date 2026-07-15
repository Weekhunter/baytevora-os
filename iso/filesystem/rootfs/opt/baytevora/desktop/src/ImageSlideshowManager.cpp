#include "bos/ImageSlideshowManager.h"

#include <QDir>
#include <QFileInfo>

#include "bos/ImageDocument.h"
#include "bos/ImageViewerManager.h"

namespace bos::shell {

ImageSlideshowManager::ImageSlideshowManager(QObject *parent)
    : QObject(parent)
{
    m_timer.setSingleShot(false);
    m_timer.setInterval(m_interval);
    connect(&m_timer, &QTimer::timeout, this, [this]() { advance(1); });
}

ImageSlideshowManager::~ImageSlideshowManager() = default;

bool ImageSlideshowManager::running() const
{
    return m_running;
}

int ImageSlideshowManager::interval() const
{
    return m_interval;
}

void ImageSlideshowManager::setInterval(int interval)
{
    if (interval < 1000) {
        interval = 1000;
    }
    if (m_interval == interval) {
        return;
    }
    m_interval = interval;
    m_timer.setInterval(interval);
    emit intervalChanged();
}

int ImageSlideshowManager::currentIndex() const
{
    return m_currentIndex;
}

int ImageSlideshowManager::imageCount() const
{
    return m_imagePaths.size();
}

void ImageSlideshowManager::setViewerManager(QObject *manager)
{
    m_viewerManager = qobject_cast<ImageViewerManager *>(manager);
    refreshFolder();
}

void ImageSlideshowManager::start()
{
    if (!m_viewerManager) {
        return;
    }
    refreshFolder();
    if (m_imagePaths.isEmpty()) {
        return;
    }

    if (m_currentIndex < 0 && !m_imagePaths.isEmpty()) {
        m_currentIndex = 0;
        m_viewerManager->openImage(m_imagePaths.first());
    }

    m_running = true;
    m_timer.start();
    emit runningChanged();
}

void ImageSlideshowManager::pause()
{
    if (!m_running) {
        return;
    }
    m_running = false;
    m_timer.stop();
    emit runningChanged();
}

void ImageSlideshowManager::stop()
{
    if (!m_running) {
        return;
    }
    m_running = false;
    m_timer.stop();
    emit runningChanged();
}

void ImageSlideshowManager::next()
{
    if (!m_viewerManager) {
        return;
    }
    refreshFolder();
    advance(1);
}

void ImageSlideshowManager::previous()
{
    if (!m_viewerManager) {
        return;
    }
    refreshFolder();
    advance(-1);
}

void ImageSlideshowManager::setFolderImages(const QStringList &paths)
{
    m_imagePaths = paths;
    updateCurrentIndexFromViewer();
}

void ImageSlideshowManager::setCurrentFolderPath(const QString &folderPath)
{
    m_folderPath = folderPath;
    refreshFolder();
}

void ImageSlideshowManager::advance(int direction)
{
    if (m_imagePaths.isEmpty() || !m_viewerManager) {
        return;
    }

    m_currentIndex += direction;
    if (m_currentIndex >= m_imagePaths.size()) {
        m_currentIndex = 0;
    } else if (m_currentIndex < 0) {
        m_currentIndex = m_imagePaths.size() - 1;
    }

    m_viewerManager->openImage(m_imagePaths.at(m_currentIndex));
    emit imageChanged();
}

void ImageSlideshowManager::refreshFolder()
{
    if (m_folderPath.isEmpty() || !m_viewerManager || !m_viewerManager->document()) {
        return;
    }

    const QDir dir(m_folderPath);
    const QStringList filters = {
        QStringLiteral("*.png"),
        QStringLiteral("*.jpg"),
        QStringLiteral("*.jpeg"),
        QStringLiteral("*.bmp"),
        QStringLiteral("*.gif"),
        QStringLiteral("*.webp")
    };
    const QFileInfoList entries = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    m_imagePaths.clear();
    m_imagePaths.reserve(entries.size());
    for (const QFileInfo &info : entries) {
        m_imagePaths.append(info.absoluteFilePath());
    }

    updateCurrentIndexFromViewer();
}

void ImageSlideshowManager::updateCurrentIndexFromViewer()
{
    if (!m_viewerManager || !m_viewerManager->document()) {
        m_currentIndex = -1;
        return;
    }

    const QString currentPath = m_viewerManager->document()->imagePath();
    m_currentIndex = m_imagePaths.indexOf(currentPath);
    if (m_currentIndex < 0 && !m_imagePaths.isEmpty()) {
        m_currentIndex = 0;
    }
}

} // namespace bos::shell
