#include "bos/User.h"

namespace bos::shell {

QVariantMap User::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("username")] = username;
    map[QStringLiteral("displayName")] = displayName;
    map[QStringLiteral("avatarPath")] = avatarPath;
    map[QStringLiteral("administrator")] = administrator;
    map[QStringLiteral("lastLogin")] = lastLogin.toString(Qt::ISODate);
    return map;
}

} // namespace bos::shell
