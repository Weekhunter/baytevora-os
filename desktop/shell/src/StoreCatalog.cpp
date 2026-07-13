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

QList<StoreItem> StoreCatalog::categoryItems(StoreCategoryEnum::Value category) const
{
    QList<StoreItem> result;
    for (const StoreItem &item : m_items) {
        if (item.category == category) {
            result.append(item);
        }
    }
    return result;
}

StoreItem StoreCatalog::item(const QString &applicationId) const
{
    return m_items.value(applicationId, StoreItem());
}

bool StoreCatalog::contains(const QString &applicationId) const
{
    return m_items.contains(applicationId);
}

QList<StoreCategory> StoreCatalog::categories() const
{
    QList<StoreCategory> list;
    const QList<StoreCategoryEnum::Value> values = {
        StoreCategoryEnum::Featured,
        StoreCategoryEnum::Productivity,
        StoreCategoryEnum::Development,
        StoreCategoryEnum::Utilities,
        StoreCategoryEnum::System,
        StoreCategoryEnum::Entertainment
    };

    for (StoreCategoryEnum::Value value : values) {
        StoreCategory category;
        category.categoryId = categoryId(value);
        category.name = StoreCategoryEnum::name(value);
        category.icon = QStringLiteral("qrc:/icons/placeholder.svg");
        category.applicationCount = 0;
        for (const StoreItem &item : m_items) {
            if (item.category == value) {
                ++category.applicationCount;
            }
        }
        list.append(category);
    }
    return list;
}

void StoreCatalog::updateInstalledState(const QString &applicationId, bool installed)
{
    auto it = m_items.find(applicationId);
    if (it != m_items.end()) {
        it->installed = installed;
    }
}

void StoreCatalog::updateInstalledVersion(const QString &applicationId, const QString &installedVersion)
{
    auto it = m_items.find(applicationId);
    if (it != m_items.end()) {
        it->installedVersion = installedVersion;
    }
}

int StoreCatalog::categoryId(StoreCategoryEnum::Value category)
{
    return static_cast<int>(category);
}

void StoreCatalog::seedCatalog()
{
    auto add = [this](const StoreItem &item) {
        m_items.insert(item.applicationId, item);
    };

    StoreItem fileManager;
    fileManager.applicationId = QStringLiteral("bos.files");
    fileManager.name = QStringLiteral("File Manager");
    fileManager.version = QStringLiteral("0.1.0");
    fileManager.latestVersion = QStringLiteral("0.1.0");
    fileManager.developer = QStringLiteral("Baytevora");
    fileManager.category = StoreCategoryEnum::System;
    fileManager.shortDescription = QStringLiteral("Browse, preview, and organize your files.");
    fileManager.longDescription = QStringLiteral("File Manager provides a modern two-pane interface for navigating the Baytevora filesystem, previewing documents, and managing folders.");
    fileManager.installed = true;
    fileManager.installedVersion = QStringLiteral("0.1.0");
    fileManager.featured = true;
    fileManager.rating = 4.2;
    fileManager.downloads = 1240;
    fileManager.size = QStringLiteral("4 MB");
    fileManager.iconPath = QStringLiteral("qrc:/icons/file.svg");
    fileManager.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    fileManager.changelog = QStringLiteral("Initial release with folder navigation and previews.");
    add(fileManager);

    StoreItem settings;
    settings.applicationId = QStringLiteral("bos.settings");
    settings.name = QStringLiteral("Settings");
    settings.version = QStringLiteral("0.1.0");
    settings.latestVersion = QStringLiteral("0.1.0");
    settings.developer = QStringLiteral("Baytevora");
    settings.category = StoreCategoryEnum::System;
    settings.shortDescription = QStringLiteral("Configure your Baytevora OS session.");
    settings.longDescription = QStringLiteral("Settings lets you personalize the desktop, manage accounts, and adjust system preferences.");
    settings.installed = true;
    settings.installedVersion = QStringLiteral("0.1.0");
    settings.featured = true;
    settings.rating = 4.5;
    settings.downloads = 980;
    settings.size = QStringLiteral("2 MB");
    settings.iconPath = QStringLiteral("qrc:/icons/settings.svg");
    settings.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    settings.changelog = QStringLiteral("System preferences and personalization controls.");
    add(settings);

    StoreItem terminal;
    terminal.applicationId = QStringLiteral("bos.terminal");
    terminal.name = QStringLiteral("Terminal");
    terminal.version = QStringLiteral("0.1.0");
    terminal.latestVersion = QStringLiteral("0.2.0");
    terminal.developer = QStringLiteral("Baytevora");
    terminal.category = StoreCategoryEnum::Development;
    terminal.shortDescription = QStringLiteral("Command-line interface for Baytevora OS.");
    terminal.longDescription = QStringLiteral("Terminal offers a full-featured shell with tabs, profiles, and theming for developers and power users.");
    terminal.installed = true;
    terminal.installedVersion = QStringLiteral("0.1.0");
    terminal.featured = true;
    terminal.rating = 4.7;
    terminal.downloads = 850;
    terminal.size = QStringLiteral("3 MB");
    terminal.iconPath = QStringLiteral("qrc:/icons/terminal.svg");
    terminal.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    terminal.changelog = QStringLiteral("0.2.0 improves tab management and color profiles.");
    add(terminal);

    StoreItem browser;
    browser.applicationId = QStringLiteral("bos.browser");
    browser.name = QStringLiteral("Browser");
    browser.version = QStringLiteral("0.2.0-alpha");
    browser.latestVersion = QStringLiteral("0.2.0-alpha");
    browser.developer = QStringLiteral("Baytevora");
    browser.category = StoreCategoryEnum::Productivity;
    browser.shortDescription = QStringLiteral("Fast, privacy-focused web browser.");
    browser.longDescription = QStringLiteral("Browser is a lightweight privacy-first web client designed for speed and minimal resource usage.");
    browser.installed = false;
    browser.featured = true;
    browser.rating = 4.0;
    browser.downloads = 430;
    browser.size = QStringLiteral("32 MB");
    browser.iconPath = QStringLiteral("qrc:/icons/browser.svg");
    browser.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    browser.changelog = QStringLiteral("Alpha release with essential navigation and bookmarks.");
    add(browser);

    StoreItem calculator;
    calculator.applicationId = QStringLiteral("bos.calculator");
    calculator.name = QStringLiteral("Calculator");
    calculator.version = QStringLiteral("0.1.0");
    calculator.latestVersion = QStringLiteral("0.1.0");
    calculator.developer = QStringLiteral("Baytevora");
    calculator.category = StoreCategoryEnum::Utilities;
    calculator.shortDescription = QStringLiteral("Simple calculator for daily arithmetic.");
    calculator.longDescription = QStringLiteral("Calculator supports basic arithmetic, memory registers, and keyboard input.");
    calculator.installed = false;
    calculator.featured = false;
    calculator.rating = 4.3;
    calculator.downloads = 620;
    calculator.size = QStringLiteral("1 MB");
    calculator.iconPath = QStringLiteral("qrc:/icons/calculator.svg");
    calculator.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    calculator.changelog = QStringLiteral("First release with arithmetic and history.");
    add(calculator);

    StoreItem notes;
    notes.applicationId = QStringLiteral("bos.notes");
    notes.name = QStringLiteral("Notes");
    notes.version = QStringLiteral("0.1.0");
    notes.latestVersion = QStringLiteral("0.2.0");
    notes.developer = QStringLiteral("Baytevora");
    notes.category = StoreCategoryEnum::Productivity;
    notes.shortDescription = QStringLiteral("Create and manage quick notes.");
    notes.longDescription = QStringLiteral("Notes lets you jot down ideas, organize them into folders, and search across all entries.");
    notes.installed = true;
    notes.installedVersion = QStringLiteral("0.1.0");
    notes.featured = false;
    notes.rating = 4.1;
    notes.downloads = 310;
    notes.size = QStringLiteral("2 MB");
    notes.iconPath = QStringLiteral("qrc:/icons/notes.svg");
    notes.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    notes.changelog = QStringLiteral("0.2.0 adds folder organization and local search.");
    add(notes);

    StoreItem systemMonitor;
    systemMonitor.applicationId = QStringLiteral("bos.system-monitor");
    systemMonitor.name = QStringLiteral("System Monitor");
    systemMonitor.version = QStringLiteral("0.1.0");
    systemMonitor.latestVersion = QStringLiteral("0.1.0");
    systemMonitor.developer = QStringLiteral("Baytevora");
    systemMonitor.category = StoreCategoryEnum::System;
    systemMonitor.shortDescription = QStringLiteral("View CPU, memory, and process activity.");
    systemMonitor.longDescription = QStringLiteral("System Monitor displays real-time resource usage and process information.");
    systemMonitor.installed = false;
    systemMonitor.featured = false;
    systemMonitor.rating = 4.6;
    systemMonitor.downloads = 720;
    systemMonitor.size = QStringLiteral("3 MB");
    systemMonitor.iconPath = QStringLiteral("qrc:/icons/monitor.svg");
    systemMonitor.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    systemMonitor.changelog = QStringLiteral("Initial system resource monitoring.");
    add(systemMonitor);

    StoreItem imageViewer;
    imageViewer.applicationId = QStringLiteral("bos.image-viewer");
    imageViewer.name = QStringLiteral("Image Viewer");
    imageViewer.version = QStringLiteral("0.1.0");
    imageViewer.latestVersion = QStringLiteral("0.2.0");
    imageViewer.developer = QStringLiteral("Baytevora");
    imageViewer.category = StoreCategoryEnum::Entertainment;
    imageViewer.shortDescription = QStringLiteral("View and transform images.");
    imageViewer.longDescription = QStringLiteral("Image Viewer supports rotation, flip, zoom modes, slideshow, metadata, and folder navigation.");
    imageViewer.installed = true;
    imageViewer.installedVersion = QStringLiteral("0.1.0");
    imageViewer.featured = false;
    imageViewer.rating = 3.9;
    imageViewer.downloads = 180;
    imageViewer.size = QStringLiteral("2 MB");
    imageViewer.iconPath = QStringLiteral("qrc:/icons/image.svg");
    imageViewer.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    imageViewer.changelog = QStringLiteral("0.2.0 adds rotation, slideshow, and metadata panel.");
    add(imageViewer);

    StoreItem textEditor;
    textEditor.applicationId = QStringLiteral("bos.text-editor");
    textEditor.name = QStringLiteral("Text Editor");
    textEditor.version = QStringLiteral("0.1.0");
    textEditor.latestVersion = QStringLiteral("0.1.0");
    textEditor.developer = QStringLiteral("Baytevora");
    textEditor.category = StoreCategoryEnum::Development;
    textEditor.shortDescription = QStringLiteral("Lightweight text and code editor.");
    textEditor.longDescription = QStringLiteral("Text Editor delivers a clean editing surface with syntax highlighting and line numbers.");
    textEditor.installed = false;
    textEditor.featured = false;
    textEditor.rating = 4.4;
    textEditor.downloads = 560;
    textEditor.size = QStringLiteral("2 MB");
    textEditor.iconPath = QStringLiteral("qrc:/icons/text.svg");
    textEditor.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    textEditor.changelog = QStringLiteral("First release with editing and highlighting.");
    add(textEditor);

    StoreItem musicPlayer;
    musicPlayer.applicationId = QStringLiteral("bos.music");
    musicPlayer.name = QStringLiteral("Music Player");
    musicPlayer.version = QStringLiteral("0.1.0");
    musicPlayer.latestVersion = QStringLiteral("0.1.0");
    musicPlayer.developer = QStringLiteral("Baytevora");
    musicPlayer.category = StoreCategoryEnum::Entertainment;
    musicPlayer.shortDescription = QStringLiteral("Play your local music library.");
    musicPlayer.longDescription = QStringLiteral("Music Player organizes albums and playlists and plays local audio files.");
    musicPlayer.installed = false;
    musicPlayer.featured = false;
    musicPlayer.rating = 4.0;
    musicPlayer.downloads = 290;
    musicPlayer.size = QStringLiteral("5 MB");
    musicPlayer.iconPath = QStringLiteral("qrc:/icons/music.svg");
    musicPlayer.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    musicPlayer.changelog = QStringLiteral("Initial local music playback.");
    add(musicPlayer);

    StoreItem videoPlayer;
    videoPlayer.applicationId = QStringLiteral("bos.video");
    videoPlayer.name = QStringLiteral("Video Player");
    videoPlayer.version = QStringLiteral("0.1.0");
    videoPlayer.latestVersion = QStringLiteral("0.1.0");
    videoPlayer.developer = QStringLiteral("Baytevora");
    videoPlayer.category = StoreCategoryEnum::Entertainment;
    videoPlayer.shortDescription = QStringLiteral("Watch videos with essential controls.");
    videoPlayer.longDescription = QStringLiteral("Video Player supports common formats with playback controls and subtitles.");
    videoPlayer.installed = false;
    videoPlayer.featured = false;
    videoPlayer.rating = 3.8;
    videoPlayer.downloads = 210;
    videoPlayer.size = QStringLiteral("8 MB");
    videoPlayer.iconPath = QStringLiteral("qrc:/icons/video.svg");
    videoPlayer.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    videoPlayer.changelog = QStringLiteral("First release with playback controls.");
    add(videoPlayer);

    StoreItem archiveManager;
    archiveManager.applicationId = QStringLiteral("bos.archive");
    archiveManager.name = QStringLiteral("Archive Manager");
    archiveManager.version = QStringLiteral("0.1.0");
    archiveManager.latestVersion = QStringLiteral("0.1.0");
    archiveManager.developer = QStringLiteral("Baytevora");
    archiveManager.category = StoreCategoryEnum::Utilities;
    archiveManager.shortDescription = QStringLiteral("Inspect and extract archive files.");
    archiveManager.longDescription = QStringLiteral("Archive Manager can open, inspect, and extract common archive formats.");
    archiveManager.installed = false;
    archiveManager.featured = false;
    archiveManager.rating = 4.2;
    archiveManager.downloads = 150;
    archiveManager.size = QStringLiteral("2 MB");
    archiveManager.iconPath = QStringLiteral("qrc:/icons/archive.svg");
    archiveManager.screenshots << QStringLiteral("qrc:/images/screenshot-placeholder.svg");
    archiveManager.changelog = QStringLiteral("Initial archive inspection support.");
    add(archiveManager);
}

} // namespace bos::shell
