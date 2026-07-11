#include "bos/SearchItem.h"

namespace bos::shell {

QVariantMap SearchItem::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("id")] = id;
    map[QStringLiteral("title")] = title;
    map[QStringLiteral("subtitle")] = subtitle;
    map[QStringLiteral("category")] = static_cast<int>(category);
    map[QStringLiteral("keywords")] = keywords;
    map[QStringLiteral("iconName")] = iconName;
    map[QStringLiteral("provider")] = provider;
    map[QStringLiteral("enabled")] = enabled;
    return map;
}

} // namespace bos::shell
