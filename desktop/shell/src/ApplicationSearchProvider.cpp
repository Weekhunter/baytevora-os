#include "bos/ApplicationSearchProvider.h"

namespace bos::shell {

QString ApplicationSearchProvider::providerName() const
{
    return QStringLiteral("Applications");
}

QList<SearchItem> ApplicationSearchProvider::registerItems()
{
    QList<SearchItem> items;

    auto add = [&items](const QString &id, const QString &title, const QString &subtitle,
                        const QStringList &keywords, const QString &iconName) {
        SearchItem item;
        item.id = id;
        item.title = title;
        item.subtitle = subtitle;
        item.category = SearchCategory::Application;
        item.keywords = keywords;
        item.iconName = iconName;
        item.provider = QStringLiteral("Applications");
        item.enabled = true;
        items.append(item);
    };

    add(QStringLiteral("app-file-manager"), QStringLiteral("File Manager"),
        QStringLiteral("Browse files and folders"),
        QStringList{QStringLiteral("files"), QStringLiteral("folders"), QStringLiteral("browse")},
        QStringLiteral("folder"));

    add(QStringLiteral("app-terminal"), QStringLiteral("Terminal"),
        QStringLiteral("Command line interface"),
        QStringList{QStringLiteral("shell"), QStringLiteral("command"), QStringLiteral("console")},
        QStringLiteral("terminal"));

    add(QStringLiteral("app-settings"), QStringLiteral("Settings"),
        QStringLiteral("System configuration"),
        QStringList{QStringLiteral("preferences"), QStringLiteral("configuration"), QStringLiteral("options")},
        QStringLiteral("settings"));

    add(QStringLiteral("app-browser"), QStringLiteral("Browser"),
        QStringLiteral("Web browser"),
        QStringList{QStringLiteral("web"), QStringLiteral("internet"), QStringLiteral("www")},
        QStringLiteral("browser"));

    add(QStringLiteral("app-calculator"), QStringLiteral("Calculator"),
        QStringLiteral("Basic calculator"),
        QStringList{QStringLiteral("math"), QStringLiteral("calculate"), QStringLiteral("numbers")},
        QStringLiteral("calculator"));

    add(QStringLiteral("app-notes"), QStringLiteral("Notes"),
        QStringLiteral("Simple notes"),
        QStringList{QStringLiteral("note"), QStringLiteral("memo"), QStringLiteral("text")},
        QStringLiteral("notes"));

    return items;
}

} // namespace bos::shell
