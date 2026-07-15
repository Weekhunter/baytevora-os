#include "bos/PackageInfo.h"

namespace bos::shell {

QVariantMap PackageInfo::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("packageId")] = packageId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("description")] = description;
    map[QStringLiteral("developer")] = developer;
    map[QStringLiteral("category")] = category;
    map[QStringLiteral("installed")] = installed;
    map[QStringLiteral("packageType")] = static_cast<int>(packageType);
    map[QStringLiteral("state")] = static_cast<int>(state);
    map[QStringLiteral("size")] = size;
    return map;
}

} // namespace bos::shell
