#include "bos/SettingsManager.h"

#include <QCoreApplication>
#include <QDebug>
#include <QSysInfo>
#include <QtGlobal>

namespace bos::shell {

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
{
    m_pages.append(SettingsPage(QStringLiteral("appearance"), QStringLiteral("Appearance")));
    m_pages.append(SettingsPage(QStringLiteral("wallpaper"), QStringLiteral("Wallpaper")));
    m_pages.append(SettingsPage(QStringLiteral("system"), QStringLiteral("System")));
    m_pages.append(SettingsPage(QStringLiteral("clipboard"), QStringLiteral("Clipboard")));
    m_pages.append(SettingsPage(QStringLiteral("shortcuts"), QStringLiteral("Shortcuts")));
    m_pages.append(SettingsPage(QStringLiteral("search"), QStringLiteral("Search")));
    m_pages.append(SettingsPage(QStringLiteral("power"), QStringLiteral("Power")));
    m_pages.append(SettingsPage(QStringLiteral("dragdrop"), QStringLiteral("Drag & Drop")));
    m_pages.append(SettingsPage(QStringLiteral("updates"), QStringLiteral("Updates")));
    m_pages.append(SettingsPage(QStringLiteral("packages"), QStringLiteral("Packages")));
    m_pages.append(SettingsPage(QStringLiteral("store"), QStringLiteral("Store")));
    m_pages.append(SettingsPage(QStringLiteral("about"), QStringLiteral("About")));

    m_currentPage = m_pages.first().id();

    m_wallpaperPath = QCoreApplication::applicationDirPath()
        + QStringLiteral("/assets/wallpapers/default.jpg");

    m_sessionTimer.start();
    m_uptimeTimer.setInterval(1000);
    connect(&m_uptimeTimer, &QTimer::timeout, this, &SettingsManager::updateUptime);
    m_uptimeTimer.start();
}

SettingsManager::~SettingsManager() = default;

QVariantList SettingsManager::pages() const
{
    QVariantList list;
    list.reserve(m_pages.size());
    for (const auto &page : m_pages) {
        list.append(page.toMap());
    }
    return list;
}

QString SettingsManager::currentPage() const
{
    return m_currentPage;
}

void SettingsManager::setCurrentPage(const QString &pageId)
{
    if (m_currentPage == pageId) {
        return;
    }

    bool valid = false;
    for (const auto &page : m_pages) {
        if (page.id() == pageId) {
            valid = true;
            break;
        }
    }

    if (!valid) {
        qWarning() << QStringLiteral("[BDE] Unknown settings page:") << pageId;
        return;
    }

    m_currentPage = pageId;
    emit currentPageChanged();
}

QString SettingsManager::bosVersion() const
{
    return QStringLiteral("0.1 Alpha");
}

QString SettingsManager::qtVersion() const
{
    return QStringLiteral(QT_VERSION_STR);
}

QString SettingsManager::architecture() const
{
    return QSysInfo::currentCpuArchitecture();
}

QString SettingsManager::uptime() const
{
    const qint64 totalSeconds = m_sessionTimer.elapsed() / 1000;
    const qint64 hours = totalSeconds / 3600;
    const qint64 minutes = (totalSeconds % 3600) / 60;
    const qint64 seconds = totalSeconds % 60;

    return QStringLiteral("%1:%2:%3")
        .arg(hours, 2, 10, QLatin1Char('0'))
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

QString SettingsManager::wallpaperPath() const
{
    return m_wallpaperPath;
}

void SettingsManager::setWallpaperPath(const QString &path)
{
    if (m_wallpaperPath == path) {
        return;
    }

    m_wallpaperPath = path;
    emit wallpaperPathChanged();
}

void SettingsManager::setTheme(const QString &theme)
{
    qDebug() << QStringLiteral("[BDE] Theme change requested:") << theme;
}

void SettingsManager::setAccentColor(const QString &color)
{
    qDebug() << QStringLiteral("[BDE] Accent color change requested:") << color;
}

void SettingsManager::setFontSize(int size)
{
    qDebug() << QStringLiteral("[BDE] Font size change requested:") << size;
}

void SettingsManager::chooseWallpaper()
{
    qDebug() << QStringLiteral("[BDE] Choose wallpaper requested");
}

void SettingsManager::restoreDefaultWallpaper()
{
    qDebug() << QStringLiteral("[BDE] Restore default wallpaper requested");
    setWallpaperPath(QCoreApplication::applicationDirPath()
                     + QStringLiteral("/assets/wallpapers/default.jpg"));
}

void SettingsManager::updateUptime()
{
    emit uptimeChanged();
}

} // namespace bos::shell
