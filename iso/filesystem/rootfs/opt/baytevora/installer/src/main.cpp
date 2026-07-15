#include "boi/InstallerApplication.h"

#include <QGuiApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("Baytevora"));
    app.setApplicationName(QStringLiteral("Baytevora OS Installer"));

    QTranslator translator;
    if (translator.load(QLocale(), QStringLiteral("boi"), QStringLiteral("."), QStringLiteral(":/i18n"))) {
        app.installTranslator(&translator);
    }

    boi::InstallerApplication installer(app);
    return installer.run();
}
