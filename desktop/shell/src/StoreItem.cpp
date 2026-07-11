#include "bos/StoreItem.h"

namespace bos::shell {

QVariantMap StoreItem::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("packageId")] = packageId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("description")] = description;
    map[QStringLiteral("developer")] = developer;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("rating")] = rating;
    map[QStringLiteral("downloads")] = downloads;
    map[QStringLiteral("category")] = static_cast<int>(category);
    map[QStringLiteral("installed")] = installed;
    map[QStringLiteral("featured")] = featured;
    map[QStringLiteral("iconPath")] = iconPath;
    return map;
}

} // namespace bos::shell
