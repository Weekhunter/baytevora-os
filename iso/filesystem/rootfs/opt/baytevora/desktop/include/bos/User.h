#pragma once

#include <QDateTime>
#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Lightweight immutable data model for a Baytevora user.
 *
 * User carries a username, display name, optional avatar path, administrator
 * flag, and last-login timestamp. It is exposed to QML as a QVariantMap.
 */
struct User {
    QString username;
    QString displayName;
    QString password;
    QString avatarPath;
    bool administrator = false;
    QDateTime lastLogin;

    QVariantMap toMap() const;
};

} // namespace bos::shell
