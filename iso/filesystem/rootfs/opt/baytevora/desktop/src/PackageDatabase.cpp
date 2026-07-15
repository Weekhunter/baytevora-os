#include "bos/PackageDatabase.h"

namespace bos::shell {

PackageDatabase::PackageDatabase()
{
    seedPackages();
}

QList<PackageInfo> PackageDatabase::allPackages() const
{
    return m_packages.values();
}

PackageInfo PackageDatabase::package(const QString &packageId) const
{
    return m_packages.value(packageId, PackageInfo());
}

bool PackageDatabase::contains(const QString &packageId) const
{
    return m_packages.contains(packageId);
}

void PackageDatabase::setState(const QString &packageId, PackageState::Value state)
{
    auto it = m_packages.find(packageId);
    if (it != m_packages.end()) {
        it->state = state;
        it->installed = (state == PackageState::Installed || state == PackageState::UpdateAvailable);
    }
}

void PackageDatabase::seedPackages()
{
    auto add = [this](const PackageInfo &info) {
        m_packages.insert(info.packageId, info);
    };

    PackageInfo fileManager;
    fileManager.packageId = QStringLiteral("bos.files");
    fileManager.name = QStringLiteral("File Manager");
    fileManager.version = QStringLiteral("0.1.0");
    fileManager.description = QStringLiteral("Browse and organize files on Baytevora OS.");
    fileManager.developer = QStringLiteral("Baytevora");
    fileManager.category = QStringLiteral("System");
    fileManager.installed = true;
    fileManager.packageType = PackageType::System;
    fileManager.state = PackageState::Installed;
    fileManager.size = QStringLiteral("4 MB");
    add(fileManager);

    PackageInfo terminal;
    terminal.packageId = QStringLiteral("bos.terminal");
    terminal.name = QStringLiteral("Terminal");
    terminal.version = QStringLiteral("0.1.0");
    terminal.description = QStringLiteral("Command-line interface for Baytevora OS.");
    terminal.developer = QStringLiteral("Baytevora");
    terminal.category = QStringLiteral("Developer");
    terminal.installed = true;
    terminal.packageType = PackageType::System;
    terminal.state = PackageState::Installed;
    terminal.size = QStringLiteral("3 MB");
    add(terminal);

    PackageInfo settings;
    settings.packageId = QStringLiteral("bos.settings");
    settings.name = QStringLiteral("Settings");
    settings.version = QStringLiteral("0.1.0");
    settings.description = QStringLiteral("Configure your Baytevora OS session.");
    settings.developer = QStringLiteral("Baytevora");
    settings.category = QStringLiteral("System");
    settings.installed = true;
    settings.packageType = PackageType::System;
    settings.state = PackageState::Installed;
    settings.size = QStringLiteral("2 MB");
    add(settings);

    PackageInfo browser;
    browser.packageId = QStringLiteral("bos.browser");
    browser.name = QStringLiteral("Browser");
    browser.version = QStringLiteral("0.2.0-alpha");
    browser.description = QStringLiteral("Web browser for Baytevora OS.");
    browser.developer = QStringLiteral("Baytevora");
    browser.category = QStringLiteral("Internet");
    browser.installed = false;
    browser.packageType = PackageType::Application;
    browser.state = PackageState::Available;
    browser.size = QStringLiteral("32 MB");
    add(browser);

    PackageInfo calculator;
    calculator.packageId = QStringLiteral("bos.calculator");
    calculator.name = QStringLiteral("Calculator");
    calculator.version = QStringLiteral("0.1.0");
    calculator.description = QStringLiteral("Simple calculator for daily arithmetic.");
    calculator.developer = QStringLiteral("Baytevora");
    calculator.category = QStringLiteral("Utilities");
    calculator.installed = false;
    calculator.packageType = PackageType::Application;
    calculator.state = PackageState::Available;
    calculator.size = QStringLiteral("1 MB");
    add(calculator);

    PackageInfo notes;
    notes.packageId = QStringLiteral("bos.notes");
    notes.name = QStringLiteral("Notes");
    notes.version = QStringLiteral("0.1.0");
    notes.description = QStringLiteral("Create and manage quick notes.");
    notes.developer = QStringLiteral("Baytevora");
    notes.category = QStringLiteral("Productivity");
    notes.installed = false;
    notes.packageType = PackageType::Application;
    notes.state = PackageState::Available;
    notes.size = QStringLiteral("2 MB");
    add(notes);
}

} // namespace bos::shell
