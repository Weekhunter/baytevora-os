#include "bos/Application.h"

#include <QQmlContext>
#include <QCoreApplication>
#include <QUrl>
#include <QtQml>

#include "bos/ApplicationManager.h"
#include "bos/ClipboardModule.h"
#include "bos/DesignTokens.h"
#include "bos/SearchCategory.h"
#include "bos/SearchModule.h"
#include "bos/SettingsApplication.h"
#include "bos/ShortcutContext.h"
#include "bos/ShortcutModule.h"
#include "bos/DesktopIconsModule.h"
#include "bos/DesktopManager.h"
#include "bos/DesktopModel.h"
#include "bos/FileManagerApplication.h"
#include "bos/FileSystemModel.h"
#include "bos/IconManager.h"
#include "bos/LauncherModule.h"
#include "bos/ModuleManager.h"
#include "bos/NotificationModule.h"
#include "bos/PowerActionType.h"
#include "bos/PowerModule.h"
#include "bos/SettingsManager.h"
#include "bos/SessionManager.h"
#include "bos/SpacingManager.h"
#include "bos/TerminalApplication.h"
#include "bos/TerminalManager.h"
#include "bos/ThemeManager.h"
#include "bos/TypographyManager.h"
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

    // Sprint 12: register FileSystemModel as a QML type so each File Manager
    // window can instantiate its own model instance from QML.
    qmlRegisterType<FileSystemModel>("BOS.Shell", 1, 0, "FileSystemModel");

    // Sprint 13: register SettingsManager as a QML type so each Settings window
    // can instantiate its own independent manager.
    qmlRegisterType<SettingsManager>("BOS.Shell", 1, 0, "SettingsManager");

    // Sprint 14: register TerminalManager as a QML type so each Terminal
    // window can instantiate its own command processor and session.
    qmlRegisterType<TerminalManager>("BOS.Shell", 1, 0, "TerminalManager");

    // Sprint 16: register DesktopModel as a QML type so the desktop surface
    // can render icons from the model exposed by DesktopManager.
    qmlRegisterType<DesktopModel>("BOS.Shell", 1, 0, "DesktopModel");

    // Sprint 18: register the ShortcutContext enum so QML integrations can use
    // ShortcutContext.Global, ShortcutContext.Application, and ShortcutContext.Window.
    qmlRegisterUncreatableMetaObject(
        bos::shell::ShortcutContext::staticMetaObject,
        "BOS.Shell", 1, 0, "ShortcutContext",
        QStringLiteral("ShortcutContext is an enum and cannot be instantiated"));

    // Sprint 19: register the SearchCategory enum so QML can compare result
    // categories using SearchCategory.Application, SearchCategory.Setting,
    // SearchCategory.Desktop, and SearchCategory.Command.
    qmlRegisterUncreatableType<bos::shell::SearchCategory>(
        "BOS.Shell", 1, 0, "SearchCategory",
        QStringLiteral("SearchCategory is an enum and cannot be instantiated"));

    // Sprint 20: register the PowerActionType enum so QML can request and
    // compare power actions using PowerActionType.Shutdown, etc.
    qmlRegisterUncreatableType<bos::shell::PowerActionType>(
        "BOS.Shell", 1, 0, "PowerActionType",
        QStringLiteral("PowerActionType is an enum and cannot be instantiated"));

    // Sprint 15: expose BDL design managers as QML context properties so all
    // QML components can reference the same token sources.
    auto themeManager = std::make_unique<ThemeManager>();
    auto designTokens = std::make_unique<DesignTokens>();
    auto typographyManager = std::make_unique<TypographyManager>();
    auto spacingManager = std::make_unique<SpacingManager>();
    auto iconManager = std::make_unique<IconManager>();

    m_engine->rootContext()->setContextProperty(QStringLiteral("ThemeManager"), themeManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("DesignTokens"), designTokens.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("TypographyManager"), typographyManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("SpacingManager"), spacingManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("IconManager"), iconManager.get());

    themeManager->setParent(m_engine.get());
    designTokens->setParent(m_engine.get());
    typographyManager->setParent(m_engine.get());
    spacingManager->setParent(m_engine.get());
    iconManager->setParent(m_engine.get());

    themeManager.release();
    designTokens.release();
    typographyManager.release();
    spacingManager.release();
    iconManager.release();

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

    // Expose the LauncherModule to QML so the taskbar and launcher UI can
    // toggle visibility and log placeholder launch requests.
    if (auto *launcher = dynamic_cast<LauncherModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Launcher")))) {
        m_engine->rootContext()->setContextProperty(QStringLiteral("launcher"), launcher);
    }

    // Sprint 16: expose the DesktopManager so the desktop surface can render
    // icons and handle selection/activation events.
    if (auto *desktopIconsModule = dynamic_cast<DesktopIconsModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("DesktopIcons")))) {
        if (auto *desktopManager = desktopIconsModule->desktopManager()) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("desktopManager"), desktopManager);
        }
    }

    // Sprint 17: expose the ClipboardManager so applications can copy and paste
    // plain text through the central clipboard service.
    if (auto *clipboardModule = dynamic_cast<ClipboardModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Clipboard")))) {
        if (auto *clipboardManager = clipboardModule->clipboardManager()) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("clipboardManager"), clipboardManager);
        }
    }

    // Sprint 18: expose the ShortcutManager so the desktop environment and
    // applications can register keyboard shortcuts through a single service.
    if (auto *shortcutModule = dynamic_cast<ShortcutModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Shortcut")))) {
        if (auto *shortcutManager = shortcutModule->shortcutManager()) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("shortcutManager"), shortcutManager);
        }
    }

    // Sprint 19: expose the SearchManager so the launcher and settings can query
    // the Baytevora Search Service.
    if (auto *searchModule = dynamic_cast<SearchModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Search")))) {
        if (auto *searchManager = searchModule->searchManager()) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("searchManager"), searchManager);
        }
    }

    // Sprint 19: expose the SettingsApplication so search results can request a
    // specific settings page.
    if (m_sessionManager->applicationManager() && m_sessionManager->applicationManager()->settingsApplication()) {
        m_engine->rootContext()->setContextProperty(
            QStringLiteral("settingsApplication"),
            m_sessionManager->applicationManager()->settingsApplication());
    }

    // Sprint 20: expose the PowerManager so the taskbar and settings can use
    // the Baytevora Power Management Service.
    if (auto *powerModule = dynamic_cast<PowerModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Power")))) {
        if (auto *powerManager = powerModule->powerManager()) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("powerManager"), powerManager);
        }
    }

    // Wire ApplicationManager to WindowManager so launch requests can create
    // demonstration windows, then expose it to QML.
    auto *windowManager = dynamic_cast<WindowManager*>(
        m_sessionManager->moduleManager()->findModule(QStringLiteral("WindowManager")));
    auto *applicationManager = dynamic_cast<ApplicationManager*>(
        m_sessionManager->moduleManager()->findModule(QStringLiteral("ApplicationManager")));
    auto *notificationModule = dynamic_cast<NotificationModule*>(
        m_sessionManager->moduleManager()->findModule(QStringLiteral("Notification")));
    NotificationManager *notificationManager = notificationModule
        ? notificationModule->notificationManager()
        : nullptr;

    if (windowManager && applicationManager) {
        applicationManager->setWindowManager(windowManager);
    }
    if (applicationManager && notificationManager) {
        applicationManager->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        m_engine->rootContext()->setContextProperty(
            QStringLiteral("applicationManager"), applicationManager);
    }

    // Sprint 20: wire the NotificationManager into the PowerManager so power
    // action requests can create information notifications.
    if (auto *powerModule = dynamic_cast<PowerModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Power")))) {
        if (auto *powerManager = powerModule->powerManager()) {
            powerManager->setNotificationManager(notificationManager);
        }
    }

    // Sprint 12: instantiate the File Manager application handler, wire it to
    // the window and notification services, and register it with the coordinator.
    auto fileManager = std::make_unique<FileManagerApplication>();
    FileManagerApplication *fileManagerPtr = fileManager.get();
    if (windowManager) {
        fileManagerPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        fileManagerPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setFileManagerApplication(fileManagerPtr);
    }
    // Extend the engine lifetime with the application so the handler survives
    // until the process exits.
    fileManager->setParent(m_engine.get());
    fileManager.release();

    // Sprint 13: instantiate the Settings application handler, wire it to the
    // window and notification services, and register it with the coordinator.
    auto settings = std::make_unique<SettingsApplication>();
    SettingsApplication *settingsPtr = settings.get();
    if (windowManager) {
        settingsPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        settingsPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setSettingsApplication(settingsPtr);
    }
    settings->setParent(m_engine.get());
    settings.release();

    // Sprint 14: instantiate the Terminal application handler, wire it to the
    // window and notification services, and register it with the coordinator.
    auto terminal = std::make_unique<TerminalApplication>();
    TerminalApplication *terminalPtr = terminal.get();
    if (windowManager) {
        terminalPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        terminalPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setTerminalApplication(terminalPtr);
    }
    terminal->setParent(m_engine.get());
    terminal.release();

    // Sprint 17: wire the NotificationManager into the ClipboardModule so a
    // manual clipboard clear can trigger an information notification.
    if (auto *clipboardModule = dynamic_cast<ClipboardModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Clipboard")))) {
        if (notificationManager) {
            clipboardModule->setNotificationManager(notificationManager);
        }
    }

    if (notificationManager) {
        m_engine->rootContext()->setContextProperty(
            QStringLiteral("notificationManager"), notificationManager);
    }

    loadInterface();

    // Sprint 11 startup demonstration: a single information notification once
    // the desktop environment has finished starting.
    if (notificationManager) {
        notificationManager->createNotification(
            QStringLiteral("Welcome to Baytevora OS"),
            QStringLiteral("Desktop environment initialized successfully."),
            QStringLiteral("System"),
            QStringLiteral("info"));
    }

    // If no root object was created, the QML file failed to load.
    if (m_engine->rootObjects().isEmpty()) {
        return -1;
    }

    // Run the Qt event loop until the user closes the window.
    return QCoreApplication::exec();
}

} // namespace bos::shell
