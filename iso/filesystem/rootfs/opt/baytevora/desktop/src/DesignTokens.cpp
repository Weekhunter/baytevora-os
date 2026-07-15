#include "bos/DesignTokens.h"

namespace bos::shell {

DesignTokens::DesignTokens(QObject *parent)
    : QObject(parent)
{
}

DesignTokens::~DesignTokens() = default;

int DesignTokens::radiusSmall() const
{
    return 6;
}

int DesignTokens::radiusMedium() const
{
    return 8;
}

int DesignTokens::radiusLarge() const
{
    return 12;
}

int DesignTokens::radiusXLarge() const
{
    return 16;
}

} // namespace bos::shell
