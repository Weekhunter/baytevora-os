#include "bos/BrandingManager.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>

namespace bos::shell {

namespace {

#ifndef BAYTEVORA_BRANDING_DIR
#define BAYTEVORA_BRANDING_DIR "../../../tasks/Branding"
#endif

QString stripNumberPrefix(const QString &folder)
{
    static const QRegularExpression prefixRe(QStringLiteral("^\\d+_"));
    return folder.remove(prefixRe);
}

} // namespace

BrandingManager::BrandingManager(QObject *parent)
    : QObject(parent)
{
    // The branding directory can be overridden at runtime via an environment
    // variable; otherwise the compile-time default (resolved against the
    // application directory) is used.
    const QString envDir = qEnvironmentVariable("BAYTEVORA_BRANDING_DIR");
    if (!envDir.isEmpty()) {
        m_brandingDir = envDir;
    } else {
        const QString appDir = QCoreApplication::applicationDirPath();
        m_brandingDir = QDir(appDir).filePath(QStringLiteral(BAYTEVORA_BRANDING_DIR));
    }
    m_brandingDir = QDir::cleanPath(m_brandingDir);

    // Product folder registry. Folder names match the generated repository
    // exactly; display names are derived from the folder name.
    const QStringList folders = {
        QStringLiteral("01_Baytevora_Labs"),
        QStringLiteral("02_BOS"),
        QStringLiteral("03_Browser"),
        QStringLiteral("04_PDF_Studio"),
        QStringLiteral("05_Media_Studio"),
        QStringLiteral("06_Store"),
        QStringLiteral("07_Settings"),
        QStringLiteral("08_File_Manager"),
        QStringLiteral("09_Notes"),
        QStringLiteral("10_Calculator"),
        QStringLiteral("11_Image_Viewer"),
        QStringLiteral("12_Archive_Manager"),
        QStringLiteral("13_Text_Editor"),
        QStringLiteral("14_Media_Player"),
        QStringLiteral("15_System_Monitor"),
        QStringLiteral("16_Task_Manager"),
        QStringLiteral("17_Network_Manager"),
        QStringLiteral("18_Storage_Manager"),
        QStringLiteral("19_Print_Manager"),
        QStringLiteral("20_Welcome_Center")
    };

    for (const QString &folder : folders) {
        const QString base = stripNumberPrefix(folder);
        QString display = base;
        display.replace(QLatin1Char('_'), QLatin1Char(' '));
        m_folderToName[folder] = display;
        m_folderToName[base] = display;
    }

    // Application-name to product-folder mapping. This lets QML resolve the
    // correct official brand asset from a human-readable application name.
    m_applicationToFolder[QStringLiteral("Baytevora OS")] = QStringLiteral("02_BOS");
    m_applicationToFolder[QStringLiteral("BOS")] = QStringLiteral("02_BOS");
    m_applicationToFolder[QStringLiteral("File Manager")] = QStringLiteral("08_File_Manager");
    m_applicationToFolder[QStringLiteral("Browser")] = QStringLiteral("03_Browser");
    m_applicationToFolder[QStringLiteral("Baytevora PDF Studio")] = QStringLiteral("04_PDF_Studio");
    m_applicationToFolder[QStringLiteral("PDF Studio")] = QStringLiteral("04_PDF_Studio");
    m_applicationToFolder[QStringLiteral("Media Studio")] = QStringLiteral("05_Media_Studio");
    m_applicationToFolder[QStringLiteral("Store")] = QStringLiteral("06_Store");
    m_applicationToFolder[QStringLiteral("Baytevora Store")] = QStringLiteral("06_Store");
    m_applicationToFolder[QStringLiteral("Settings")] = QStringLiteral("07_Settings");
    m_applicationToFolder[QStringLiteral("Notes")] = QStringLiteral("09_Notes");
    m_applicationToFolder[QStringLiteral("Calculator")] = QStringLiteral("10_Calculator");
    m_applicationToFolder[QStringLiteral("Image Viewer")] = QStringLiteral("11_Image_Viewer");
    m_applicationToFolder[QStringLiteral("Archive Manager")] = QStringLiteral("12_Archive_Manager");
    m_applicationToFolder[QStringLiteral("Text Editor")] = QStringLiteral("13_Text_Editor");
    m_applicationToFolder[QStringLiteral("Media Player")] = QStringLiteral("14_Media_Player");
    m_applicationToFolder[QStringLiteral("System Monitor")] = QStringLiteral("15_System_Monitor");
    m_applicationToFolder[QStringLiteral("Task Manager")] = QStringLiteral("16_Task_Manager");
    m_applicationToFolder[QStringLiteral("Network Manager")] = QStringLiteral("17_Network_Manager");
    m_applicationToFolder[QStringLiteral("Storage Manager")] = QStringLiteral("18_Storage_Manager");
    m_applicationToFolder[QStringLiteral("Print Manager")] = QStringLiteral("19_Print_Manager");
    m_applicationToFolder[QStringLiteral("Welcome Center")] = QStringLiteral("20_Welcome_Center");
    m_applicationToFolder[QStringLiteral("Package Manager")] = QStringLiteral("06_Store");
    m_applicationToFolder[QStringLiteral("Terminal")] = QStringLiteral("02_BOS");
}

QString BrandingManager::companyName() const
{
    return QStringLiteral("Baytevora Labs");
}

QString BrandingManager::osName() const
{
    return QStringLiteral("Baytevora OS");
}

QString BrandingManager::osVersion() const
{
    return QStringLiteral("Version 0.1 Alpha");
}

QString BrandingManager::fullVersionLabel() const
{
    return osName() + QStringLiteral("\n") + osVersion();
}

QString BrandingManager::poweredBy() const
{
    return QStringLiteral("Powered by Baytevora");
}

QStringList BrandingManager::productIds() const
{
    QStringList ids = m_folderToName.keys();
    ids.removeDuplicates();
    ids.sort();
    return ids;
}

QString BrandingManager::productName(const QString &productId) const
{
    if (m_folderToName.contains(productId)) {
        return m_folderToName.value(productId);
    }

    const QString folder = folderForApplication(productId);
    if (!folder.isEmpty() && m_folderToName.contains(folder)) {
        return m_folderToName.value(folder);
    }

    QString fallback = productId;
    fallback.replace(QLatin1Char('_'), QLatin1Char(' '));
    return fallback;
}

QUrl BrandingManager::applicationLogoUrl(const QString &applicationName,
                                          const QString &variant) const
{
    const QString folder = folderForApplication(applicationName);
    if (folder.isEmpty()) {
        return QUrl();
    }

    const QString file = folder + QLatin1Char('/') + logoFileName(variant);
    return QUrl::fromLocalFile(brandingFilePath(file));
}

QUrl BrandingManager::applicationSymbolUrl(const QString &applicationName) const
{
    const QString folder = folderForApplication(applicationName);
    if (folder.isEmpty()) {
        return QUrl();
    }

    const QString file = folder + QStringLiteral("/symbol.svg");
    return QUrl::fromLocalFile(brandingFilePath(file));
}

QUrl BrandingManager::applicationFaviconUrl(const QString &applicationName) const
{
    const QString folder = folderForApplication(applicationName);
    if (folder.isEmpty()) {
        return QUrl();
    }

    const QString file = folder + QStringLiteral("/favicon.svg");
    return QUrl::fromLocalFile(brandingFilePath(file));
}

QUrl BrandingManager::iconUrl(const QString &iconName) const
{
    if (iconName.isEmpty()) {
        return QUrl();
    }

    const QString file = QStringLiteral("Icons/svg/") + iconName + QStringLiteral(".svg");
    return QUrl::fromLocalFile(brandingFilePath(file));
}

QUrl BrandingManager::wallpaperUrl(const QString &name) const
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QString wallpapersDir = QDir(appDir).filePath(QStringLiteral("assets/wallpapers"));

    if (!name.isEmpty()) {
        const QString filePath = QDir(wallpapersDir).filePath(name + QStringLiteral(".jpg"));
        return QUrl::fromLocalFile(filePath);
    }

    const QString defaultPath = QDir(wallpapersDir).filePath(QStringLiteral("default.jpg"));
    return QUrl::fromLocalFile(defaultPath);
}

QStringList BrandingManager::availableWallpapers() const
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QString wallpapersDir = QDir(appDir).filePath(QStringLiteral("assets/wallpapers"));
    const QDir dir(wallpapersDir);

    QStringList names;
    for (const QFileInfo &info : dir.entryInfoList(QDir::Files)) {
        names.append(info.baseName());
    }
    return names;
}

QString BrandingManager::folderForApplication(const QString &applicationName) const
{
    if (applicationName.isEmpty()) {
        return QString();
    }

    if (m_applicationToFolder.contains(applicationName)) {
        return m_applicationToFolder.value(applicationName);
    }

    // Direct folder name lookup (e.g. "04_PDF_Studio").
    if (QDir(brandingFilePath(applicationName)).exists()) {
        return applicationName;
    }

    // Strip a numeric prefix and try again.
    const QString base = stripNumberPrefix(applicationName);
    if (m_applicationToFolder.contains(base)) {
        return m_applicationToFolder.value(base);
    }

    return QString();
}

QString BrandingManager::brandingFilePath(const QString &relativePath) const
{
    return QDir(m_brandingDir).filePath(relativePath);
}

QString BrandingManager::logoFileName(const QString &variant) const
{
    const QString v = variant.toLower();
    if (v == QStringLiteral("dark")) {
        return QStringLiteral("logo-dark.svg");
    }
    if (v == QStringLiteral("light")) {
        return QStringLiteral("logo-light.svg");
    }
    if (v == QStringLiteral("monochrome")) {
        return QStringLiteral("logo-monochrome.svg");
    }
    return QStringLiteral("logo.svg");
}

} // namespace bos::shell
