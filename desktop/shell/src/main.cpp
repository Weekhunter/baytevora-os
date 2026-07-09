#include <QGuiApplication>
#include "bos/Application.h"

/**
 * @brief Entry point for the Baytevora Desktop Environment Shell.
 *
 * Creates the Qt application instance, configures basic application metadata,
 * and delegates control to the modular Application class.
 */
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName(QStringLiteral("BOS Shell"));
    app.setOrganizationName(QStringLiteral("Baytevora Labs"));

    bos::shell::Application shell(app);
    return shell.run();
}
