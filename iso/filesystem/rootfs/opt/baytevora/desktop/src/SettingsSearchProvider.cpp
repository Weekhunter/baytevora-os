#include "bos/SettingsSearchProvider.h"

namespace bos::shell {

QString SettingsSearchProvider::providerName() const
{
    return QStringLiteral("Settings");
}

QList<SearchItem> SettingsSearchProvider::registerItems()
{
    QList<SearchItem> items;

    auto add = [&items](const QString &id, const QString &title, const QString &subtitle,
                        const QStringList &keywords, const QString &iconName) {
        SearchItem item;
        item.id = id;
        item.title = title;
        item.subtitle = subtitle;
        item.category = SearchCategory::Setting;
        item.keywords = keywords;
        item.iconName = iconName;
        item.provider = QStringLiteral("Settings");
        item.enabled = true;
        items.append(item);
    };

    add(QStringLiteral("settings-appearance"), QStringLiteral("Appearance"),
        QStringLiteral("Change theme and colors"),
        QStringList{QStringLiteral("theme"), QStringLiteral("colors"), QStringLiteral("style")},
        QStringLiteral("appearance"));

    add(QStringLiteral("settings-wallpaper"), QStringLiteral("Wallpaper"),
        QStringLiteral("Change desktop background"),
        QStringList{QStringLiteral("wallpaper"), QStringLiteral("background"), QStringLiteral("desktop")},
        QStringLiteral("wallpaper"));

    add(QStringLiteral("settings-system"), QStringLiteral("System"),
        QStringLiteral("System information"),
        QStringList{QStringLiteral("system"), QStringLiteral("info"), QStringLiteral("about")},
        QStringLiteral("system"));

    add(QStringLiteral("settings-about"), QStringLiteral("About"),
        QStringLiteral("About Baytevora OS"),
        QStringList{QStringLiteral("about"), QStringLiteral("version"), QStringLiteral("os")},
        QStringLiteral("about"));

    add(QStringLiteral("settings-shortcuts"), QStringLiteral("Shortcuts"),
        QStringLiteral("Keyboard shortcuts"),
        QStringList{QStringLiteral("shortcuts"), QStringLiteral("keyboard"), QStringLiteral("keys")},
        QStringLiteral("shortcuts"));

    add(QStringLiteral("settings-search"), QStringLiteral("Search"),
        QStringLiteral("Search subsystem status"),
        QStringList{QStringLiteral("search"), QStringLiteral("bss"), QStringLiteral("find")},
        QStringLiteral("search"));

    return items;
}

} // namespace bos::shell
