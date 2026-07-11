#include "bos/StoreCatalog.h"

namespace bos::shell {

StoreCatalog::StoreCatalog()
{
    seedCatalog();
}

QList<StoreItem> StoreCatalog::allItems() const
{
    return m_items.values();
}

QList<StoreItem> StoreCatalog::featuredItems() const
{
    QList<StoreItem> result;
    for (const StoreItem &item : m_items) {
        if (item.featured) {
            result.append(item);
        }
    }
    return result;
}

QList<StoreItem> StoreCatalog::categoryItems(StoreCategory::Value category) const
{
    QList<StoreItem> result;
    for (const StoreItem &item : m_items) {
        if (item.category == category) {
            result.append(item);
        }
    }
    return result;
}

StoreItem StoreCatalog::item(const QString &packageId) const
{
    return m_items.value(packageId, StoreItem());
}

bool StoreCatalog::contains(const QString &packageId) const
{
    return m_items.contains(packageId);
}

QStringList StoreCatalog::categories() const
{
    QStringList names;
    names.append(StoreCategory::name(StoreCategory::Featured));
    names.append(StoreCategory::name(StoreCategory::Productivity));
    names.append(StoreCategory::name(StoreCategory::Development));
    names.append(StoreCategory::name(StoreCategory::Utilities));
    names.append(StoreCategory::name(StoreCategory::System));
    names.append(StoreCategory::name(StoreCategory::Entertainment));
    return names;
}

void StoreCatalog::updateInstalledState(const QString &packageId, bool installed)
{
    auto it = m_items.find(packageId);
    if (it != m_items.end()) {
        it->installed = installed;
    }
}

void StoreCatalog::seedCatalog()
{
    auto add = [this](const StoreItem &item) {
        m_items.insert(item.packageId, item);
    };

    StoreItem fileManager;
    fileManager.packageId = QStringLiteral("bos.files");
    fileManager.name = QStringLiteral("File Manager");
    fileManager.description = QStringLiteral("Browse, preview, and organize your files.");
    fileManager.developer = QStringLiteral("Baytevora");
    fileManager.version = QStringLiteral("0.1.0");
    fileManager.rating = 4.2;
    fileManager.downloads = 1240;
    fileManager.category = StoreCategory::System;
    fileManager.installed = true;
    fileManager.featured = true;
    fileManager.iconPath = QStringLiteral("qrc:/icons/file.svg");
    add(fileManager);

    StoreItem settings;
    settings.packageId = QStringLiteral("bos.settings");
    settings.name = QStringLiteral("Settings");
    settings.description = QStringLiteral("Configure your Baytevora OS session.");
    settings.developer = QStringLiteral("Baytevora");
    settings.version = QStringLiteral("0.1.0");
    settings.rating = 4.5;
    settings.downloads = 980;
    settings.category = StoreCategory::System;
    settings.installed = true;
    settings.featured = true;
    settings.iconPath = QStringLiteral("qrc:/icons/settings.svg");
    add(settings);

    StoreItem terminal;
    terminal.packageId = QStringLiteral("bos.terminal");
    terminal.name = QStringLiteral("Terminal");
    terminal.description = QStringLiteral("Command-line interface for Baytevora OS.");
    terminal.developer = QStringLiteral("Baytevora");
    terminal.version = QStringLiteral("0.1.0");
    terminal.rating = 4.7;
    terminal.downloads = 850;
    terminal.category = StoreCategory::Development;
    terminal.installed = true;
    terminal.featured = true;
    terminal.iconPath = QStringLiteral("qrc:/icons/terminal.svg");
    add(terminal);

    StoreItem browser;
    browser.packageId = QStringLiteral("bos.browser");
    browser.name = QStringLiteral("Browser");
    browser.description = QStringLiteral("Fast, privacy-focused web browser.");
    browser.developer = QStringLiteral("Baytevora");
    browser.version = QStringLiteral("0.2.0-alpha");
    browser.rating = 4.0;
    browser.downloads = 430;
    browser.category = StoreCategory::Productivity;
    browser.installed = false;
    browser.featured = true;
    browser.iconPath = QStringLiteral("qrc:/icons/browser.svg");
    add(browser);

    StoreItem calculator;
    calculator.packageId = QStringLiteral("bos.calculator");
    calculator.name = QStringLiteral("Calculator");
    calculator.description = QStringLiteral("Simple calculator for daily arithmetic.");
    calculator.developer = QStringLiteral("Baytevora");
    calculator.version = QStringLiteral("0.1.0");
    calculator.rating = 4.3;
    calculator.downloads = 620;
    calculator.category = StoreCategory::Utilities;
    calculator.installed = false;
    calculator.featured = false;
    calculator.iconPath = QStringLiteral("qrc:/icons/calculator.svg");
    add(calculator);

    StoreItem notes;
    notes.packageId = QStringLiteral("bos.notes");
    notes.name = QStringLiteral("Notes");
    notes.description = QStringLiteral("Create and manage quick notes.");
    notes.developer = QStringLiteral("Baytevora");
    notes.version = QStringLiteral("0.1.0");
    notes.rating = 4.1;
    notes.downloads = 310;
    notes.category = StoreCategory::Productivity;
    notes.installed = false;
    notes.featured = false;
    notes.iconPath = QStringLiteral("qrc:/icons/notes.svg");
    add(notes);

    StoreItem systemMonitor;
    systemMonitor.packageId = QStringLiteral("bos.system-monitor");
    systemMonitor.name = QStringLiteral("System Monitor");
    systemMonitor.description = QStringLiteral("View CPU, memory, and process activity.");
    systemMonitor.developer = QStringLiteral("Baytevora");
    systemMonitor.version = QStringLiteral("0.1.0");
    systemMonitor.rating = 4.6;
    systemMonitor.downloads = 720;
    systemMonitor.category = StoreCategory::System;
    systemMonitor.installed = false;
    systemMonitor.featured = false;
    systemMonitor.iconPath = QStringLiteral("qrc:/icons/monitor.svg");
    add(systemMonitor);

    StoreItem imageViewer;
    imageViewer.packageId = QStringLiteral("bos.image-viewer");
    imageViewer.name = QStringLiteral("Image Viewer");
    imageViewer.description = QStringLiteral("View and compare images.");
    imageViewer.developer = QStringLiteral("Baytevora");
    imageViewer.version = QStringLiteral("0.1.0");
    imageViewer.rating = 3.9;
    imageViewer.downloads = 180;
    imageViewer.category = StoreCategory::Entertainment;
    imageViewer.installed = false;
    imageViewer.featured = false;
    imageViewer.iconPath = QStringLiteral("qrc:/icons/image.svg");
    add(imageViewer);

    StoreItem textEditor;
    textEditor.packageId = QStringLiteral("bos.text-editor");
    textEditor.name = QStringLiteral("Text Editor");
    textEditor.description = QStringLiteral("Lightweight text and code editor.");
    textEditor.developer = QStringLiteral("Baytevora");
    textEditor.version = QStringLiteral("0.1.0");
    textEditor.rating = 4.4;
    textEditor.downloads = 560;
    textEditor.category = StoreCategory::Development;
    textEditor.installed = false;
    textEditor.featured = false;
    textEditor.iconPath = QStringLiteral("qrc:/icons/text.svg");
    add(textEditor);

    StoreItem musicPlayer;
    musicPlayer.packageId = QStringLiteral("bos.music");
    musicPlayer.name = QStringLiteral("Music Player");
    musicPlayer.description = QStringLiteral("Play your local music library.");
    musicPlayer.developer = QStringLiteral("Baytevora");
    musicPlayer.version = QStringLiteral("0.1.0");
    musicPlayer.rating = 4.0;
    musicPlayer.downloads = 290;
    musicPlayer.category = StoreCategory::Entertainment;
    musicPlayer.installed = false;
    musicPlayer.featured = false;
    musicPlayer.iconPath = QStringLiteral("qrc:/icons/music.svg");
    add(musicPlayer);

    StoreItem videoPlayer;
    videoPlayer.packageId = QStringLiteral("bos.video");
    videoPlayer.name = QStringLiteral("Video Player");
    videoPlayer.description = QStringLiteral("Watch videos with essential controls.");
    videoPlayer.developer = QStringLiteral("Baytevora");
    videoPlayer.version = QStringLiteral("0.1.0");
    videoPlayer.rating = 3.8;
    videoPlayer.downloads = 210;
    videoPlayer.category = StoreCategory::Entertainment;
    videoPlayer.installed = false;
    videoPlayer.featured = false;
    videoPlayer.iconPath = QStringLiteral("qrc:/icons/video.svg");
    add(videoPlayer);

    StoreItem archiveManager;
    archiveManager.packageId = QStringLiteral("bos.archive");
    archiveManager.name = QStringLiteral("Archive Manager");
    archiveManager.description = QStringLiteral("Inspect and extract archive files.");
    archiveManager.developer = QStringLiteral("Baytevora");
    archiveManager.version = QStringLiteral("0.1.0");
    archiveManager.rating = 4.2;
    archiveManager.downloads = 150;
    archiveManager.category = StoreCategory::Utilities;
    archiveManager.installed = false;
    archiveManager.featured = false;
    archiveManager.iconPath = QStringLiteral("qrc:/icons/archive.svg");
    add(archiveManager);
}

} // namespace bos::shell
