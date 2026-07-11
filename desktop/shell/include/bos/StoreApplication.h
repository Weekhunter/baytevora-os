#pragma once

#include <QObject>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Store application for BOS.
 *
 * StoreApplication requests a managed window from WindowManager and loads the
 * StoreWindow QML scene.
 */
class StoreApplication : public QObject {
    Q_OBJECT

public:
    explicit StoreApplication(QObject *parent = nullptr);
    ~StoreApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();

private:
    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
