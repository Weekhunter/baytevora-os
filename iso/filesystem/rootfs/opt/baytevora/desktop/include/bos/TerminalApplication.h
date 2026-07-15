#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Terminal application for Baytevora OS.
 *
 * TerminalApplication requests a managed window from WindowManager and emits a
 * startup notification. The per-window session and command buffer are provided
 * by TerminalManager and displayed by QML.
 */
class TerminalApplication : public QObject {
    Q_OBJECT

public:
    explicit TerminalApplication(QObject *parent = nullptr);
    ~TerminalApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
