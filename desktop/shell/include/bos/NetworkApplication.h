#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Network Manager application for BOS.
 *
 * NetworkApplication requests a managed window from WindowManager and loads
 * the NetworkManagerWindow QML scene. Multiple Network Manager windows can
 * be opened, each with its own NetworkManager.
 */
class NetworkApplication : public QObject {
    Q_OBJECT

public:
    explicit NetworkApplication(QObject *parent = nullptr);
    ~NetworkApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Network Manager window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
