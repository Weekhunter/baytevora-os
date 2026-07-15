#include "bos/LoginManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"
#include "bos/UserManager.h"

namespace bos::shell {

LoginManager::LoginManager(QObject *parent)
    : QObject(parent)
    , m_userManager(new UserManager(this))
{
    qDebug() << QStringLiteral("[BDE] LoginManager initialized");
    m_state = LoginState::Booting;
}

LoginManager::~LoginManager() = default;

void LoginManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int LoginManager::state() const
{
    return static_cast<int>(m_state);
}

QVariantMap LoginManager::selectedUser() const
{
    return m_userManager->currentUser();
}

QVariantList LoginManager::users() const
{
    return m_userManager->users();
}

UserManager *LoginManager::userManager() const
{
    return m_userManager;
}

QString LoginManager::stateName() const
{
    switch (m_state) {
    case LoginState::Booting:
        return QStringLiteral("Booting");
    case LoginState::WaitingForSelection:
        return QStringLiteral("Waiting for selection");
    case LoginState::LoggingIn:
        return QStringLiteral("Logging in");
    case LoginState::LoggedIn:
        return QStringLiteral("Logged in");
    }
    return QStringLiteral("Unknown");
}

void LoginManager::login()
{
    if (m_state == LoginState::LoggedIn) {
        return;
    }

    setState(LoginState::LoggingIn);
    qDebug() << QStringLiteral("[BDE] Login requested for user") << m_userManager->currentUser().value(QStringLiteral("username")).toString();

    // Sprint 22: authentication is a placeholder. Any login request succeeds.
    setState(LoginState::LoggedIn);
    notify(QStringLiteral("Welcome"), QStringLiteral("Welcome back."));
    emit loggedIn();
}

void LoginManager::logout()
{
    qDebug() << QStringLiteral("[BDE] Logout requested");
    notify(QStringLiteral("Session"), QStringLiteral("Session ended."));

    setState(LoginState::WaitingForSelection);
    emit loggedOut();
}

void LoginManager::cancel()
{
    if (m_state == LoginState::LoggingIn || m_state == LoginState::Booting) {
        setState(LoginState::WaitingForSelection);
    }
}

void LoginManager::selectUser(const QString &username)
{
    if (m_userManager) {
        m_userManager->selectUser(username);
        emit selectedUserChanged();
    }
}

void LoginManager::setState(LoginState::Value state)
{
    if (m_state != state) {
        m_state = state;
        emit stateChanged();
    }
}

void LoginManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                   QStringLiteral("Login"),
                                                   QStringLiteral("info"));
    }
}

} // namespace bos::shell
