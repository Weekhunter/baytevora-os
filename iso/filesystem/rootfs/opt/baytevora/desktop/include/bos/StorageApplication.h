#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Storage Manager application for BOS.
 *
 * StorageApplication requests a managed window from WindowManager and loads
 * the StorageManagerWindow QML scene. Multiple Storage Manager windows can be
 * opened, each with its own StorageManager.
 */
class StorageApplication : public QObject {
    Q_OBJECT

public:
    explicit StorageApplication(QObject *parent = nullptr);
    ~StorageApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Storage Manager window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
