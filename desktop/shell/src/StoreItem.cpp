#include "bos/StoreItem.h"

namespace bos::shell {

QVariantMap StoreItem::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("applicationId")] = applicationId;
    map[QStringLiteral("name")] = name;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("developer")] = developer;
    map[QStringLiteral("category")] = static_cast<int>(category);
    map[QStringLiteral("shortDescription")] = shortDescription;
    map[QStringLiteral("longDescription")] = longDescription.isEmpty() ? shortDescription : longDescription;
    map[QStringLiteral("installed")] = installed;
    map[QStringLiteral("installedVersion")] = installedVersion;
    map[QStringLiteral("latestVersion")] = latestVersion.isEmpty() ? version : latestVersion;
    map[QStringLiteral("screenshots")] = screenshots;
    map[QStringLiteral("changelog")] = changelog;
    map[QStringLiteral("rating")] = rating;
    map[QStringLiteral("size")] = size;
    map[QStringLiteral("iconPath")] = iconPath;
    map[QStringLiteral("featured")] = featured;
    map[QStringLiteral("downloads")] = downloads;
    return map;
}

} // namespace bos::shell
