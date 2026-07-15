#include "bos/ThemeManager.h"

#include <QGuiApplication>
#include <QScreen>
#include <QtMath>

namespace bos::shell {

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
{
    updateMetrics();
}

ThemeManager::~ThemeManager() = default;

void ThemeManager::recalculateMetrics()
{
    updateMetrics();
}

void ThemeManager::updateMetrics()
{
    double dpr = 1.0;
    int logicalDpi = 96;
    int screenHeight = 1080;
    int screenWidth = 1920;

    if (QScreen *screen = QGuiApplication::primaryScreen()) {
        dpr = screen->devicePixelRatio();
        logicalDpi = screen->logicalDotsPerInch();
        const QRect geometry = screen->availableGeometry();
        screenWidth = geometry.width();
        screenHeight = geometry.height();
    }

    const double dpiScale = logicalDpi / 96.0;
    const double resolutionScale = qMin(screenWidth / 1920.0, screenHeight / 1080.0);

    const double newScaleFactor = qBound(0.8, qMax(dpr, qMax(dpiScale, resolutionScale)), 3.0);
    const bool newHighDpi = dpr > 1.0;
    const bool newCompactMode = (screenWidth < 1280) || (screenHeight < 720);
    const bool newTouchMode = newHighDpi || (newScaleFactor >= 1.5);

    if (m_scaleFactor == newScaleFactor && m_iconScale == newScaleFactor
        && m_textScale == newScaleFactor && m_highDpi == newHighDpi
        && m_compactMode == newCompactMode && m_touchMode == newTouchMode) {
        return;
    }

    m_scaleFactor = newScaleFactor;
    m_iconScale = newScaleFactor;
    m_textScale = newScaleFactor;
    m_highDpi = newHighDpi;
    m_compactMode = newCompactMode;
    m_touchMode = newTouchMode;

    emit metricsChanged();
}

bool ThemeManager::compactMode() const
{
    return m_compactMode;
}

bool ThemeManager::touchMode() const
{
    return m_touchMode;
}

bool ThemeManager::highDpi() const
{
    return m_highDpi;
}

double ThemeManager::scaleFactor() const
{
    return m_scaleFactor;
}

double ThemeManager::iconScale() const
{
    return m_iconScale;
}

double ThemeManager::textScale() const
{
    return m_textScale;
}

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
