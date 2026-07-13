#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Print Manager application for BOS.
 *
 * PrintApplication requests a managed window from WindowManager and loads the
 * PrintManagerWindow QML scene. Multiple Print Manager windows can be opened,
 * each with its own PrintManager.
 */
class PrintApplication : public QObject {
    Q_OBJECT

public:
    explicit PrintApplication(QObject *parent = nullptr);
    ~PrintApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Print Manager window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
