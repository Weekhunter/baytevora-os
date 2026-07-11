#include "bos/UserManager.h"

namespace bos::shell {

UserManager::UserManager(QObject *parent)
    : QObject(parent)
{
    createDefaultUser();
}

QVariantList UserManager::users() const
{
    QVariantList list;
    for (const User &user : m_users) {
        list.append(user.toMap());
    }
    return list;
}

QVariantMap UserManager::currentUser() const
{
    for (const User &user : m_users) {
        if (user.username == m_currentUsername) {
            return user.toMap();
        }
    }
    return QVariantMap();
}

void UserManager::selectUser(const QString &username)
{
    bool found = false;
    for (const User &user : m_users) {
        if (user.username == username) {
            found = true;
            break;
        }
    }

    if (!found) {
        return;
    }

    if (m_currentUsername != username) {
        m_currentUsername = username;
        emit currentUserChanged();
    }
}

int UserManager::userCount() const
{
    return m_users.size();
}

void UserManager::createDefaultUser()
{
    User user;
    user.username = QStringLiteral("bos");
    user.displayName = QStringLiteral("Baytevora User");
    user.avatarPath = QStringLiteral("");
    user.administrator = true;
    user.lastLogin = QDateTime::currentDateTimeUtc();

    m_users.append(user);
    m_currentUsername = user.username;
}

} // namespace bos::shell
