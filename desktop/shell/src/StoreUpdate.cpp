#include "bos/StoreUpdate.h"

namespace bos::shell {

QVariantMap StoreUpdate::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("applicationId")] = applicationId;
    map[QStringLiteral("installedVersion")] = installedVersion;
    map[QStringLiteral("availableVersion")] = availableVersion;
    map[QStringLiteral("updateAvailable")] = updateAvailable;
    return map;
}

} // namespace bos::shell
