#include "bos/IconManager.h"

#include <QtMath>

namespace bos::shell {

IconManager::IconManager(QObject *parent)
    : QObject(parent)
{
}

IconManager::~IconManager() = default;

void IconManager::setScaleFactor(double scaleFactor)
{
    if (qFuzzyCompare(m_scaleFactor, scaleFactor)) {
        return;
    }
    m_scaleFactor = scaleFactor;
    emit smallChanged();
    emit mediumChanged();
    emit normalChanged();
    emit largeChanged();
    emit extraLargeChanged();
}

int IconManager::small() const { return scaled(16); }
int IconManager::medium() const { return scaled(20); }
int IconManager::normal() const { return scaled(24); }
int IconManager::large() const { return scaled(32); }
int IconManager::extraLarge() const { return scaled(48); }

int IconManager::scaled(int baseSize) const
{
    return qRound(baseSize * m_scaleFactor);
}

} // namespace bos::shell
