#include "bos/Application.h"

#include <QQmlContext>
#include <QCoreApplication>
#include <QUrl>

#include "bos/ModuleManager.h"
#include "bos/SessionManager.h"
#include "bos/WindowManager.h"

namespace bos::shell {

Application::Application(QGuiApplication &app)
    : m_app(app)
    , m_engine(std::make_unique<QQmlApplicationEngine>())
    , m_sessionManager(std::make_unique<SessionManager>())
{
    initialize();
}

Application::~Application() = default;

void Application::initialize()
{
    connectSignals();
}

void Application::connectSignals()
{
    // If the root QML object fails to create, exit the application with an
    // error code. The queued connection ensures the event loop is running
    // before the lambda is invoked.
    QObject::connect(
        m_engine.get(),
        &QQmlApplicationEngine::objectCreated,
        &m_app,
        [this](QObject *object, const QUrl &url) {
            if (!object && url == QUrl(QStringLiteral("qrc:/qt/qml/BOS/Shell/Desktop.qml"))) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
}

void Application::loadInterface()
{
    // Expose the wallpaper source path to QML. The path is resolved relative
    // to the application executable so that the build directory can contain a
    // copy of the assets folder (see CMakeLists.txt). If the file is missing,
    // the Wallpaper component will log a warning and show the fallback color.
    const QString wallpaperPath = QCoreApplication::applicationDirPath()
        + QStringLiteral("/assets/wallpapers/default.jpg");
    m_engine->rootContext()->setContextProperty(
        QStringLiteral("wallpaperSource"),
        QUrl::fromLocalFile(wallpaperPath));

    // Load the root QML type from the embedded BOS.Shell module.
    m_engine->loadFromModule(QStringLiteral("BOS.Shell"), QStringLiteral("Desktop"));
}

int Application::run()
{
    // Sprint 5 startup sequence:
    //   SessionManager.initialize() -> ModuleManager.register() ->
    //   ModuleManager.initialize() -> ModuleManager.start() ->
    //   expose WindowManager -> load QML
    m_sessionManager->initialize();
    m_sessionManager->start();

    // Expose the WindowManager to QML so the desktop surface can render frames
    // for every registered window.
    if (auto *windowManager = dynamic_cast<WindowManager*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("WindowManager")))) {
        m_engine->rootContext()->setContextProperty(QStringLiteral("windowManager"), windowManager);
    }

    loadInterface();

    // If no root object was created, the QML file failed to load.
    if (m_engine->rootObjects().isEmpty()) {
        return -1;
    }

    // Run the Qt event loop until the user closes the window.
    return QCoreApplication::exec();
}

} // namespace bos::shell
