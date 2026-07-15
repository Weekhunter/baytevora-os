#include "bos/AdaptiveLayoutManager.h"

#include <QtMath>

namespace bos::shell {

AdaptiveLayoutManager::AdaptiveLayoutManager(QObject *parent)
    : QObject(parent)
{
}

AdaptiveLayoutManager::~AdaptiveLayoutManager() = default;

void AdaptiveLayoutManager::setScaleFactor(double scaleFactor)
{
    if (qFuzzyCompare(m_scaleFactor, scaleFactor)) {
        return;
    }
    m_scaleFactor = scaleFactor;
    emit metricsChanged();
}

void AdaptiveLayoutManager::recalculate()
{
    emit metricsChanged();
}

int AdaptiveLayoutManager::windowPadding() const
{
    return scaled(16);
}

int AdaptiveLayoutManager::contentPadding() const
{
    return scaled(12);
}

int AdaptiveLayoutManager::sectionSpacing() const
{
    return scaled(24);
}

int AdaptiveLayoutManager::controlSpacing() const
{
    return scaled(8);
}

int AdaptiveLayoutManager::toolbarHeight() const
{
    return scaled(44);
}

int AdaptiveLayoutManager::taskbarHeight() const
{
    return scaled(40);
}

int AdaptiveLayoutManager::sidebarWidth() const
{
    return scaled(180);
}

int AdaptiveLayoutManager::titleBarHeight() const
{
    return scaled(32);
}

int AdaptiveLayoutManager::scaled(int baseSize) const
{
    return qRound(baseSize * m_scaleFactor);
}

} // namespace bos::shell
