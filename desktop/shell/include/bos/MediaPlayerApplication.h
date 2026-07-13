#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Media Player application for BOS.
 *
 * MediaPlayerApplication requests a managed window from WindowManager and loads
 * the MediaPlayerWindow QML scene. Multiple Media Player windows can be opened,
 * each with its own MediaPlayerManager.
 */
class MediaPlayerApplication : public QObject {
    Q_OBJECT

public:
    explicit MediaPlayerApplication(QObject *parent = nullptr);
    ~MediaPlayerApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Media Player window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

    /**
     * @brief Opens a new Media Player window and loads the given media file.
     *
     * This method is provided for future File Manager integration.
     */
    Q_INVOKABLE int openMedia(const QString &path);

private:
    int openInternal(const QString &initialPath);

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
