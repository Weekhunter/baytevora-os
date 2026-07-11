#include "bos/TypographyManager.h"

namespace bos::shell {

TypographyManager::TypographyManager(QObject *parent)
    : QObject(parent)
{
}

TypographyManager::~TypographyManager() = default;

QString TypographyManager::fontFamily() const
{
    return QStringLiteral("Inter, sans-serif");
}

int TypographyManager::displaySize() const
{
    return 32;
}

int TypographyManager::heading() const
{
    return 24;
}

int TypographyManager::title() const
{
    return 18;
}

int TypographyManager::subtitle() const
{
    return 16;
}

int TypographyManager::body() const
{
    return 14;
}

int TypographyManager::caption() const
{
    return 12;
}

int TypographyManager::small() const
{
    return 10;
}

} // namespace bos::shell
