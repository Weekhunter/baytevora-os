#include "bos/PowerAction.h"

namespace bos::shell {

QVariantMap PowerAction::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("id")] = id;
    map[QStringLiteral("title")] = title;
    map[QStringLiteral("description")] = description;
    map[QStringLiteral("type")] = static_cast<int>(type);
    map[QStringLiteral("enabled")] = enabled;
    map[QStringLiteral("iconName")] = iconName;
    return map;
}

} // namespace bos::shell
