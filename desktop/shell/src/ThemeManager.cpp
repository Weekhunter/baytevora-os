#include "bos/ThemeManager.h"

namespace bos::shell {

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
{
}

ThemeManager::~ThemeManager() = default;

QString ThemeManager::primaryColor() const
{
    return QStringLiteral("#2563EB");
}

QString ThemeManager::accentColor() const
{
    return QStringLiteral("#06B6D4");
}

QString ThemeManager::backgroundColor() const
{
    return QStringLiteral("#0F172A");
}

QString ThemeManager::surfaceColor() const
{
    return QStringLiteral("#1E293B");
}

QString ThemeManager::surfaceSecondaryColor() const
{
    return QStringLiteral("#334155");
}

QString ThemeManager::borderColor() const
{
    return QStringLiteral("#475569");
}

QString ThemeManager::textPrimary() const
{
    return QStringLiteral("#F8FAFC");
}

QString ThemeManager::textSecondary() const
{
    return QStringLiteral("#CBD5E1");
}

QString ThemeManager::textDisabled() const
{
    return QStringLiteral("#64748B");
}

QString ThemeManager::successColor() const
{
    return QStringLiteral("#10B981");
}

QString ThemeManager::warningColor() const
{
    return QStringLiteral("#F59E0B");
}

QString ThemeManager::errorColor() const
{
    return QStringLiteral("#EF4444");
}

QString ThemeManager::highlightColor() const
{
    return QStringLiteral("#38BDF8");
}

QString ThemeManager::selectionColor() const
{
    return QStringLiteral("#2563EB");
}

QString ThemeManager::windowBackground() const
{
    return QStringLiteral("#1E293B");
}

QString ThemeManager::taskbarBackground() const
{
    return QStringLiteral("#1E293B");
}

QString ThemeManager::launcherBackground() const
{
    return QStringLiteral("#1E293B");
}

QString ThemeManager::notificationBackground() const
{
    return QStringLiteral("#1E293B");
}

} // namespace bos::shell
