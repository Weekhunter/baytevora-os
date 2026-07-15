#pragma once

#include <QObject>
#include <QVariantList>

#include "bos/User.h"

namespace bos::shell {

/**
 * @brief Owns the local user list and the currently selected user.
 *
 * UserManager exposes the available users and the current selection to QML. It
 * contains no authentication logic.
 */
class UserManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList users READ users NOTIFY usersChanged)
    Q_PROPERTY(QVariantMap currentUser READ currentUser NOTIFY currentUserChanged)

public:
    explicit UserManager(QObject *parent = nullptr);

    QVariantList users() const;
    QVariantMap currentUser() const;

    Q_INVOKABLE void selectUser(const QString &username);
    Q_INVOKABLE int userCount() const;
    Q_INVOKABLE void createUserFromWizard(const QString &name,
                                          const QString &login,
                                          const QString &password,
                                          bool administrator,
                                          const QString &avatar);

signals:
    void usersChanged();
    void currentUserChanged();

private:
    void createDefaultUser();

    QList<User> m_users;
    QString m_currentUsername;
};

} // namespace bos::shell
