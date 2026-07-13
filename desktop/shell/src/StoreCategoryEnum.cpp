#include "bos/StoreCategoryEnum.h"

namespace bos::shell {

StoreCategoryEnum::StoreCategoryEnum(QObject *parent)
    : QObject(parent)
{
}

QString StoreCategoryEnum::name(StoreCategoryEnum::Value category)
{
    switch (category) {
    case Featured:
        return QStringLiteral("Featured");
    case Productivity:
        return QStringLiteral("Productivity");
    case Development:
        return QStringLiteral("Development");
    case Utilities:
        return QStringLiteral("Utilities");
    case System:
        return QStringLiteral("System");
    case Entertainment:
        return QStringLiteral("Entertainment");
    }
    return QStringLiteral("Unknown");
}

} // namespace bos::shell
