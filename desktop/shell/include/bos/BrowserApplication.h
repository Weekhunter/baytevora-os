#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Browser application for BOS.
 *
 * BrowserApplication requests a managed window from WindowManager and loads
 * the BrowserWindow QML scene. Multiple browser windows can be opened.
 */
class BrowserApplication : public QObject {
    Q_OBJECT

public:
    explicit BrowserApplication(QObject *parent = nullptr);
    ~BrowserApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
