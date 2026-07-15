#include "bos/PackageDependency.h"

namespace bos::shell {

QVariantMap PackageDependency::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("packageId")] = packageId;
    map[QStringLiteral("dependencyId")] = dependencyId;
    map[QStringLiteral("minimumVersion")] = minimumVersion;
    map[QStringLiteral("optional")] = optional;
    return map;
}

} // namespace bos::shell
