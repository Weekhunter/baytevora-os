#include "bos/DesktopSearchProvider.h"

namespace bos::shell {

QString DesktopSearchProvider::providerName() const
{
    return QStringLiteral("Desktop");
}

QList<SearchItem> DesktopSearchProvider::registerItems()
{
    QList<SearchItem> items;

    auto add = [&items](const QString &id, const QString &title, const QString &subtitle,
                        const QStringList &keywords, const QString &iconName) {
        SearchItem item;
        item.id = id;
        item.title = title;
        item.subtitle = subtitle;
        item.category = SearchCategory::Desktop;
        item.keywords = keywords;
        item.iconName = iconName;
        item.provider = QStringLiteral("Desktop");
        item.enabled = true;
        items.append(item);
    };

    add(QStringLiteral("desktop-home"), QStringLiteral("Home"),
        QStringLiteral("User home directory"),
        QStringList{QStringLiteral("home"), QStringLiteral("user"), QStringLiteral("directory")},
        QStringLiteral("home"));

    add(QStringLiteral("desktop-documents"), QStringLiteral("Documents"),
        QStringLiteral("Documents folder"),
        QStringList{QStringLiteral("documents"), QStringLiteral("files"), QStringLiteral("folder")},
        QStringLiteral("documents"));

    add(QStringLiteral("desktop-downloads"), QStringLiteral("Downloads"),
        QStringLiteral("Downloads folder"),
        QStringList{QStringLiteral("downloads"), QStringLiteral("files"), QStringLiteral("folder")},
        QStringLiteral("downloads"));

    add(QStringLiteral("desktop-computer"), QStringLiteral("Computer"),
        QStringLiteral("System and drives"),
        QStringList{QStringLiteral("computer"), QStringLiteral("system"), QStringLiteral("drives")},
        QStringLiteral("computer"));

    add(QStringLiteral("desktop-trash"), QStringLiteral("Trash"),
        QStringLiteral("Deleted items"),
        QStringList{QStringLiteral("trash"), QStringLiteral("bin"), QStringLiteral("deleted")},
        QStringLiteral("trash"));

    add(QStringLiteral("desktop-settings"), QStringLiteral("Settings"),
        QStringLiteral("System settings shortcut"),
        QStringList{QStringLiteral("settings"), QStringLiteral("preferences")},
        QStringLiteral("settings"));

    return items;
}

} // namespace bos::shell
