#include <QApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

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

    // Sprint 27: initialize the Qt WebEngine runtime before any QML engine is
    // created so the Browser view can load content immediately.
    QtWebEngineQuick::initialize();

    app.setApplicationName(QStringLiteral("Baytevora OS"));
    app.setApplicationDisplayName(QStringLiteral("Baytevora OS"));
    app.setApplicationVersion(QStringLiteral("0.1 Alpha"));
    app.setOrganizationName(QStringLiteral("Baytevora Labs"));

    bos::shell::Application shell(app);
    return shell.run();
}
