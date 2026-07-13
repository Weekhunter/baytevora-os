#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Calculator application for BOS.
 *
 * CalculatorApplication requests a managed window from WindowManager and loads
 * the CalculatorWindow QML scene. Multiple Calculator windows can be opened.
 */
class CalculatorApplication : public QObject {
    Q_OBJECT

public:
    explicit CalculatorApplication(QObject *parent = nullptr);
    ~CalculatorApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
