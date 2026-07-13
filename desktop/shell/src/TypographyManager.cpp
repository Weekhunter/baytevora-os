#include "bos/TypographyManager.h"

#include <QtMath>

namespace bos::shell {

TypographyManager::TypographyManager(QObject *parent)
    : QObject(parent)
{
}

TypographyManager::~TypographyManager() = default;

void TypographyManager::setScaleFactor(double scaleFactor)
{
    if (qFuzzyCompare(m_scaleFactor, scaleFactor)) {
        return;
    }
    m_scaleFactor = scaleFactor;
    emit displayChanged();
    emit headingChanged();
    emit titleChanged();
    emit subtitleChanged();
    emit bodyChanged();
    emit captionChanged();
    emit smallChanged();
}

QString TypographyManager::fontFamily() const
{
    return QStringLiteral("Inter, sans-serif");
}

int TypographyManager::displaySize() const
{
    return scaled(32);
}

int TypographyManager::heading() const
{
    return scaled(24);
}

int TypographyManager::title() const
{
    return scaled(18);
}

int TypographyManager::subtitle() const
{
    return scaled(16);
}

int TypographyManager::body() const
{
    return scaled(14);
}

int TypographyManager::caption() const
{
    return scaled(12);
}

int TypographyManager::small() const
{
    return scaled(10);
}

int TypographyManager::scaled(int baseSize) const
{
    return qRound(baseSize * m_scaleFactor);
}

} // namespace bos::shell
