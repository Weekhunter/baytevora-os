#include "bos/Package.h"

namespace bos::shell {

QVariantMap Package::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("packageId")] = packageId;
    map[QStringLiteral("applicationId")] = applicationId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("architecture")] = architecture;
    map[QStringLiteral("size")] = size;
    map[QStringLiteral("installed")] = installed;
    map[QStringLiteral("state")] = state;
    map[QStringLiteral("packageType")] = packageType;
    map[QStringLiteral("description")] = description;
    map[QStringLiteral("category")] = category;
    map[QStringLiteral("developer")] = developer;
    return map;
}

} // namespace bos::shell
