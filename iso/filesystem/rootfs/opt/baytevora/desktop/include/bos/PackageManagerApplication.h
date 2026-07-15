#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native application handler for the Baytevora Package Manager.
 */
class PackageManagerApplication : public QObject {
    Q_OBJECT

public:
    explicit PackageManagerApplication(QObject *parent = nullptr);
    ~PackageManagerApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
