#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora System Monitor application for BOS.
 *
 * SystemMonitorApplication requests a managed window from WindowManager and
 * loads the SystemMonitorWindow QML scene. Multiple System Monitor windows can
 * be opened, each with its own SystemMonitorManager.
 */
class SystemMonitorApplication : public QObject {
    Q_OBJECT

public:
    explicit SystemMonitorApplication(QObject *parent = nullptr);
    ~SystemMonitorApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new System Monitor window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
