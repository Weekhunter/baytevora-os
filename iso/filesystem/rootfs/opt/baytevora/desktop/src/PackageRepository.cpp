#include "bos/PackageRepository.h"

namespace bos::shell {

QVariantMap PackageRepository::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("repositoryId")] = repositoryId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("enabled")] = enabled;
    map[QStringLiteral("priority")] = priority;
    map[QStringLiteral("localPath")] = localPath;
    return map;
}

} // namespace bos::shell
