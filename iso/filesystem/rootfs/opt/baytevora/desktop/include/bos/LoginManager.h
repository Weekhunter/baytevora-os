#pragma once

#include <QObject>
#include <QVariantMap>

#include "bos/LoginState.h"

namespace bos::shell {

class NotificationManager;
class UserManager;

/**
 * @brief Coordinates the Baytevora Login Manager (BLM) flow.
 *
 * LoginManager owns the UserManager and tracks the login lifecycle. This sprint
 * uses placeholder authentication only: calling login() always succeeds. Real
 * password validation, PAM, and biometric authentication are reserved for
 * future sprints.
 */
class LoginManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int state READ state NOTIFY stateChanged)
    Q_PROPERTY(QVariantMap selectedUser READ selectedUser NOTIFY selectedUserChanged)
    Q_PROPERTY(QVariantList users READ users NOTIFY usersChanged)

public:
    explicit LoginManager(QObject *parent = nullptr);
    ~LoginManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    int state() const;
    QVariantMap selectedUser() const;
    QVariantList users() const;
    UserManager *userManager() const;
    Q_INVOKABLE QString stateName() const;

    Q_INVOKABLE void login();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void cancel();
    Q_INVOKABLE void selectUser(const QString &username);

signals:
    void stateChanged();
    void selectedUserChanged();
    void usersChanged();
    void loggedIn();
    void loggedOut();

private:
    void setState(LoginState::Value state);
    void notify(const QString &title, const QString &message);

    LoginState::Value m_state = LoginState::Booting;
    UserManager *m_userManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
