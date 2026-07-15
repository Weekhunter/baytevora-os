#include "bos/AccessibilityManager.h"

namespace bos::shell {

AccessibilityManager::AccessibilityManager(QObject *parent)
    : QObject(parent)
{
}

AccessibilityManager::~AccessibilityManager() = default;

bool AccessibilityManager::largeTextEnabled() const
{
    return false;
}

bool AccessibilityManager::highContrastEnabled() const
{
    return false;
}

bool AccessibilityManager::reducedMotionEnabled() const
{
    return false;
}

void AccessibilityManager::setLargeTextEnabled(bool enabled)
{
    Q_UNUSED(enabled)
    // Placeholder for future accessibility implementation.
    emit largeTextEnabledChanged();
}

void AccessibilityManager::setHighContrastEnabled(bool enabled)
{
    Q_UNUSED(enabled)
    // Placeholder for future accessibility implementation.
    emit highContrastEnabledChanged();
}

void AccessibilityManager::setReducedMotionEnabled(bool enabled)
{
    Q_UNUSED(enabled)
    // Placeholder for future accessibility implementation.
    emit reducedMotionEnabledChanged();
}

} // namespace bos::shell
