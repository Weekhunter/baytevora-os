#pragma once

#include <QObject>
#include <QStringList>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Image Viewer application for BOS.
 */
class ImageViewerApplication : public QObject {
    Q_OBJECT

public:
    explicit ImageViewerApplication(QObject *parent = nullptr);
    ~ImageViewerApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();
    Q_INVOKABLE int openFile(const QString &filePath);

    Q_INVOKABLE bool hasPendingOpenFile() const;
    Q_INVOKABLE QString takePendingOpenFile();

private:
    int doOpen();

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QStringList m_pendingOpenFiles;
};

} // namespace bos::shell
