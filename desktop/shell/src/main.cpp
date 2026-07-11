#include <QApplication>
#include "bos/Application.h"

/**
 * @brief Entry point for the Baytevora Desktop Environment Shell.
 *
 * Creates the Qt application instance, configures basic application metadata,
 * and delegates control to the modular Application class. QApplication is
 * used instead of QGuiApplication so that the Sprint 18 ShortcutManager can
 * create the hidden QWidget parent required by QShortcut.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName(QStringLiteral("BOS Shell"));
    app.setOrganizationName(QStringLiteral("Baytevora Labs"));

    bos::shell::Application shell(app);
    return shell.run();
}
