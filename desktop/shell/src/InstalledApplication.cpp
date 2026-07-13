#include "bos/InstalledApplication.h"

namespace bos::shell {

QVariantMap InstalledApplication::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("applicationId")] = applicationId;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("installDate")] = installDate.toString(QStringLiteral("yyyy-MM-dd"));
    map[QStringLiteral("lastUpdated")] = lastUpdated.toString(QStringLiteral("yyyy-MM-dd"));
    return map;
}

} // namespace bos::shell
