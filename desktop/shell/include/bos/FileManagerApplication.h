#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief The first real BOS application: the File Manager.
 *
 * FileManagerApplication integrates with the existing application framework. It
 * requests a managed window from WindowManager, reports startup through the
 * notification service, and exposes the file-system logic to its QML view via
 * FileSystemModel. No file manipulation logic lives in QML.
 */
class FileManagerApplication : public QObject {
    Q_OBJECT

public:
    explicit FileManagerApplication(QObject *parent = nullptr);
    ~FileManagerApplication() override;

    /**
     * @brief Sets the WindowManager used to create File Manager windows.
     */
    void setWindowManager(WindowManager *windowManager);

    /**
     * @brief Sets the NotificationManager used for startup notifications.
     */
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new File Manager window.
     * @return The new window ID, or -1 if creation failed.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
