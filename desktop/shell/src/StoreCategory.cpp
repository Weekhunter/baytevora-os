#include "bos/StoreCategory.h"

namespace bos::shell {

QVariantMap StoreCategory::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("categoryId")] = categoryId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("icon")] = icon;
    map[QStringLiteral("applicationCount")] = applicationCount;
    return map;
}

} // namespace bos::shell
