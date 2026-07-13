#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Task Manager application for BOS.
 *
 * TaskManagerApplication requests a managed window from WindowManager and loads
 * the TaskManagerWindow QML scene. Multiple Task Manager windows can be opened,
 * each with its own TaskManager.
 */
class TaskManagerApplication : public QObject {
    Q_OBJECT

public:
    explicit TaskManagerApplication(QObject *parent = nullptr);
    ~TaskManagerApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Task Manager window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
