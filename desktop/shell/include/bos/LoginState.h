#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Lifecycle states of the LoginManager.
 *
 * LoginState is exposed to QML as LoginState so the login screen can react to
 * Booting, WaitingForSelection, LoggingIn, and LoggedIn.
 */
class LoginState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Booting,
        WaitingForSelection,
        LoggingIn,
        LoggedIn
    };
    Q_ENUM(Value)

    explicit LoginState(QObject *parent = nullptr);
};

} // namespace bos::shell
