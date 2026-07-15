#include "bos/DragData.h"

namespace bos::shell {

QVariantMap DragData::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("type")] = static_cast<int>(type);
    map[QStringLiteral("typeName")] = typeToString();
    map[QStringLiteral("value")] = value;
    return map;
}

QString DragData::typeToString() const
{
    switch (type) {
    case DragType::Text:
        return QStringLiteral("Text");
    case DragType::FilePath:
        return QStringLiteral("FilePath");
    case DragType::DesktopItem:
        return QStringLiteral("DesktopItem");
    case DragType::Application:
        return QStringLiteral("Application");
    }
    return QStringLiteral("Unknown");
}

} // namespace bos::shell
