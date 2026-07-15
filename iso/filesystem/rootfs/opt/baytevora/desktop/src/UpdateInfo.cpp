#include "bos/UpdateInfo.h"

namespace bos::shell {

QVariantMap UpdateInfo::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("version")] = version;
    map[QStringLiteral("title")] = title;
    map[QStringLiteral("description")] = description;
    map[QStringLiteral("size")] = size;
    map[QStringLiteral("releaseDate")] = releaseDate.toString(Qt::ISODate);
    map[QStringLiteral("type")] = type;
    return map;
}

} // namespace bos::shell
