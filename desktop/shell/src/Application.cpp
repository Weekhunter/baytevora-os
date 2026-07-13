#include "bos/Application.h"

#include <QQmlContext>
#include <QCoreApplication>
#include <QUrl>
#include <QtQml>

#include "bos/ApplicationManager.h"
#include "bos/BrowserApplication.h"
#include "bos/BrowserManager.h"
#include "bos/BrowserDownloadManager.h"
#include "bos/BrowserBookmarkManager.h"
#include "bos/BrowserHistoryManager.h"
#include "bos/BrowserPermissionManager.h"
#include "bos/BrowserPrivacySettings.h"
#include "bos/ArchiveApplication.h"
#include "bos/ArchiveManager.h"
#include "bos/CalculatorApplication.h"
#include "bos/CalculatorManager.h"
#include "bos/MediaPlayerApplication.h"
#include "bos/MediaPlayerManager.h"
#include "bos/PdfStudioApplication.h"
#include "bos/PdfStudioManager.h"
#include "bos/PdfEditorTools.h"
#include "bos/PdfAnnotationManager.h"
#include "bos/NetworkApplication.h"
#include "bos/NetworkManager.h"
#include "bos/PrintApplication.h"
#include "bos/PrintManager.h"
#include "bos/StorageApplication.h"
#include "bos/StorageManager.h"
#include "bos/SystemMonitorApplication.h"
#include "bos/SystemMonitorManager.h"
#include "bos/TaskManagerApplication.h"
#include "bos/TaskManager.h"
#include "bos/TextEditorApplication.h"
#include "bos/TextEditorManager.h"
#include "bos/BrowserModule.h"
#include "bos/AccessibilityManager.h"
#include "bos/AdaptiveLayoutManager.h"
#include "bos/ClipboardModule.h"
#include "bos/ImageDocument.h"
#include "bos/ImageMetadata.h"
#include "bos/ImageSlideshowManager.h"
#include "bos/ImageViewerApplication.h"
#include "bos/ImageViewerManager.h"
#include "bos/Note.h"
#include "bos/NotesApplication.h"
#include "bos/NotesManager.h"
#include "bos/DesignTokens.h"
#include "bos/DragModule.h"
#include "bos/DragOperationState.h"
#include "bos/DragType.h"
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
#include "bos/FileFavoriteManager.h"
#include "bos/RecentFileManager.h"
#include "bos/FileSearchManager.h"
#include "bos/NoteFolder.h"
#include "bos/NotesStorageManager.h"
#include "bos/NoteSearchManager.h"
#include "bos/IconManager.h"
#include "bos/LauncherModule.h"
#include "bos/LoginModule.h"
#include "bos/LoginState.h"
#include "bos/LockModule.h"
#include "bos/LockState.h"
#include "bos/ModuleManager.h"
#include "bos/PackageManager.h"
#include "bos/PackageModule.h"
#include "bos/PackageState.h"
#include "bos/PackageType.h"
#include "bos/PackageTransaction.h"
#include "bos/StoreApplication.h"
#include "bos/PackageManagerApplication.h"
#include "bos/StoreCategoryEnum.h"
#include "bos/StoreManager.h"
#include "bos/StoreModule.h"
#include "bos/UpdateModule.h"
#include "bos/UpdateState.h"
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

void Application::registerQmlTypes()
{
    // Sprint 12: register FileSystemModel as a QML type so each File Manager
    // window can instantiate its own model instance from QML.
    qmlRegisterType<FileSystemModel>("BOS.Shell", 1, 0, "FileSystemModel");

    // Sprint 45: register FileFavoriteManager, RecentFileManager, and
    // FileSearchManager as uncreatable types because they are owned by the
    // FileSystemModel for each File Manager window.
    qmlRegisterUncreatableType<FileFavoriteManager>("BOS.Shell", 1, 0,
                                                   "FileFavoriteManager",
                                                   "FileFavoriteManager is exposed through FileSystemModel");
    qmlRegisterUncreatableType<RecentFileManager>("BOS.Shell", 1, 0,
                                                 "RecentFileManager",
                                                 "RecentFileManager is exposed through FileSystemModel");
    qmlRegisterUncreatableType<FileSearchManager>("BOS.Shell", 1, 0,
                                                 "FileSearchManager",
                                                 "FileSearchManager is exposed through FileSystemModel");

    // Sprint 13: register SettingsManager as a QML type so each Settings window
    // can instantiate its own independent manager.
    qmlRegisterType<SettingsManager>("BOS.Shell", 1, 0, "SettingsManager");

    // Sprint 14: register TerminalManager as a QML type so each Terminal
    // window can instantiate its own command processor and session.
    qmlRegisterType<TerminalManager>("BOS.Shell", 1, 0, "TerminalManager");

    // Sprint 27: register BrowserManager as a QML type so each Browser window
    // can create its own isolated BrowserManager instance.
    qmlRegisterType<BrowserManager>("BOS.Shell", 1, 0, "BrowserManager");

    // Sprint 42: register BrowserDownloadManager as an uncreatable QML type
    // so the download manager exposed by BrowserManager can be used from QML.
    qmlRegisterUncreatableType<BrowserDownloadManager>("BOS.Shell", 1, 0,
                                                       "BrowserDownloadManager",
                                                       "BrowserDownloadManager is exposed through BrowserManager");

    // Sprint 43: register BrowserBookmarkManager and BrowserHistoryManager as
    // uncreatable QML types so the managers exposed by BrowserManager can be
    // used from the bookmarks and history windows.
    qmlRegisterUncreatableType<BrowserBookmarkManager>("BOS.Shell", 1, 0,
                                                       "BrowserBookmarkManager",
                                                       "BrowserBookmarkManager is exposed through BrowserManager");
    qmlRegisterUncreatableType<BrowserHistoryManager>("BOS.Shell", 1, 0,
                                                       "BrowserHistoryManager",
                                                       "BrowserHistoryManager is exposed through BrowserManager");

    // Sprint 44: register BrowserPermissionManager and BrowserPrivacySettings as
    // uncreatable QML types so they can be used from the privacy window.
    qmlRegisterUncreatableType<BrowserPermissionManager>("BOS.Shell", 1, 0,
                                                         "BrowserPermissionManager",
                                                         "BrowserPermissionManager is exposed through BrowserManager");
    qmlRegisterUncreatableType<BrowserPrivacySettings>("BOS.Shell", 1, 0,
                                                       "BrowserPrivacySettings",
                                                       "BrowserPrivacySettings is exposed through BrowserManager");

    // Sprint 28: register NotesManager as a QML type so each Notes window can
    // manage its own collection of in-memory notes.
    qmlRegisterType<NotesManager>("BOS.Shell", 1, 0, "NotesManager");

    // Sprint 46: register NoteFolder, NotesStorageManager, and
    // NoteSearchManager as uncreatable types because they are owned by
    // NotesManager for each Notes window.
    qmlRegisterUncreatableType<NoteFolder>("BOS.Shell", 1, 0,
                                           "NoteFolder",
                                           "NoteFolder is exposed through NotesManager");
    qmlRegisterUncreatableType<NotesStorageManager>("BOS.Shell", 1, 0,
                                                    "NotesStorageManager",
                                                    "NotesStorageManager is exposed through NotesManager");
    qmlRegisterUncreatableType<NoteSearchManager>("BOS.Shell", 1, 0,
                                                 "NoteSearchManager",
                                                 "NoteSearchManager is exposed through NotesManager");

    // Sprint 29: register ImageViewerManager as a QML type so each Image Viewer
    // window can manage its own ImageDocument.
    qmlRegisterType<ImageViewerManager>("BOS.Shell", 1, 0, "ImageViewerManager");

    // Sprint 47: register ImageMetadata and ImageSlideshowManager as uncreatable
    // types because they are owned by ImageViewerManager for each Image Viewer
    // window.
    qmlRegisterUncreatableType<ImageMetadata>("BOS.Shell", 1, 0,
                                              "ImageMetadata",
                                              "ImageMetadata is exposed through ImageViewerManager");
    qmlRegisterUncreatableType<ImageSlideshowManager>("BOS.Shell", 1, 0,
                                                     "ImageSlideshowManager",
                                                     "ImageSlideshowManager is exposed through ImageViewerManager");

    // Sprint 31: register CalculatorManager as a QML type so each Calculator
    // window owns an independent CalculatorManager instance.
    qmlRegisterType<CalculatorManager>("BOS.Shell", 1, 0, "CalculatorManager");

    // Sprint D: register PdfStudioManager as a QML type so each Baytevora PDF
    // Studio window owns an independent PdfStudioManager instance.
    qmlRegisterType<PdfStudioManager>("BOS.Shell", 1, 0, "PdfStudioManager");
    qmlRegisterUncreatableType<PdfEditorTools>("BOS.Shell", 1, 0,
                                                "PdfEditorTools",
                                                "PdfEditorTools exposes the tool enum only");
    qmlRegisterUncreatableType<PdfAnnotationManager>("BOS.Shell", 1, 0,
                                                      "PdfAnnotationManager",
                                                      "PdfAnnotationManager is exposed through PdfStudioManager");

    // Sprint 33: register ArchiveManager as a QML type so each Archive Manager
    // window owns an independent ArchiveManager instance.
    qmlRegisterType<ArchiveManager>("BOS.Shell", 1, 0, "ArchiveManager");

    // Sprint 34: register MediaPlayerManager as a QML type so each Media Player
    // window owns an independent MediaPlayerManager instance.
    qmlRegisterType<MediaPlayerManager>("BOS.Shell", 1, 0, "MediaPlayerManager");

    // Sprint 35: register TextEditorManager as a QML type so each Text Editor
    // window owns an independent TextEditorManager instance.
    qmlRegisterType<TextEditorManager>("BOS.Shell", 1, 0, "TextEditorManager");

    // Sprint 36: register SystemMonitorManager as a QML type so each System
    // Monitor window owns an independent SystemMonitorManager instance.
    qmlRegisterType<SystemMonitorManager>("BOS.Shell", 1, 0, "SystemMonitorManager");

    // Sprint 37: register TaskManager as a QML type so each Task Manager
    // window owns an independent TaskManager instance.
    qmlRegisterType<TaskManager>("BOS.Shell", 1, 0, "TaskManager");

    // Sprint 38: register NetworkManager as a QML type so each Network
    // Manager window owns an independent NetworkManager instance.
    qmlRegisterType<NetworkManager>("BOS.Shell", 1, 0, "NetworkManager");

    // Sprint 39: register StorageManager as a QML type so each Storage
    // Manager window owns an independent StorageManager instance.
    qmlRegisterType<StorageManager>("BOS.Shell", 1, 0, "StorageManager");

    // Sprint 40: register PrintManager as a QML type so each Print
    // Manager window owns an independent PrintManager instance, and expose
    // a shared print manager for cross-application printing hooks.
    qmlRegisterType<PrintManager>("BOS.Shell", 1, 0, "PrintManager");

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

    // Sprint 21: register the DragType enum so QML can create and inspect drags
    // using DragType.Text, DragType.FilePath, DragType.DesktopItem, and
    // DragType.Application.
    qmlRegisterUncreatableType<bos::shell::DragType>(
        "BOS.Shell", 1, 0, "DragType",
        QStringLiteral("DragType is an enum and cannot be instantiated"));

    // Sprint 21: register the DragOperationState enum so QML can inspect drag
    // lifecycle states using DragOperationState.Idle, DragOperationState.Started,
    // DragOperationState.Dragging, DragOperationState.Dropped, and
    // DragOperationState.Cancelled.
    qmlRegisterUncreatableType<bos::shell::DragOperationState>(
        "BOS.Shell", 1, 0, "DragOperationState",
        QStringLiteral("DragOperationState is an enum and cannot be instantiated"));

    // Sprint 22: register the LoginState enum so the login screen can inspect
    // the login lifecycle using LoginState.Booting, LoginState.WaitingForSelection,
    // LoginState.LoggingIn, and LoginState.LoggedIn.
    qmlRegisterUncreatableType<bos::shell::LoginState>(
        "BOS.Shell", 1, 0, "LoginState",
        QStringLiteral("LoginState is an enum and cannot be instantiated"));

    // Sprint 23: register the LockState enum so the lock screen can inspect
    // the lock lifecycle using LockState.Unlocked, LockState.Locking,
    // LockState.Locked, and LockState.Unlocking.
    qmlRegisterUncreatableType<bos::shell::LockState>(
        "BOS.Shell", 1, 0, "LockState",
        QStringLiteral("LockState is an enum and cannot be instantiated"));

    // Sprint 24: register the UpdateState enum so update UI can inspect the
    // lifecycle using UpdateState.Idle, UpdateState.Checking,
    // UpdateState.UpdatesAvailable, UpdateState.Downloading,
    // UpdateState.ReadyToInstall, UpdateState.UpToDate, and UpdateState.Error.
    qmlRegisterUncreatableType<bos::shell::UpdateState>(
        "BOS.Shell", 1, 0, "UpdateState",
        QStringLiteral("UpdateState is an enum and cannot be instantiated"));

    // Sprint 25: register the PackageState and PackageType enums so the package
    // UI can inspect package state and type values.
    qmlRegisterUncreatableType<bos::shell::PackageState>(
        "BOS.Shell", 1, 0, "PackageState",
        QStringLiteral("PackageState is an enum and cannot be instantiated"));
    qmlRegisterUncreatableType<bos::shell::PackageType>(
        "BOS.Shell", 1, 0, "PackageType",
        QStringLiteral("PackageType is an enum and cannot be instantiated"));

    // Sprint 49: register package transaction and operation enums for QML.
    qmlRegisterUncreatableType<bos::shell::PackageOperation>(
        "BOS.Shell", 1, 0, "PackageOperation",
        QStringLiteral("PackageOperation is an enum and cannot be instantiated"));
    qmlRegisterUncreatableType<bos::shell::PackageTransactionState>(
        "BOS.Shell", 1, 0, "PackageTransactionState",
        QStringLiteral("PackageTransactionState is an enum and cannot be instantiated"));

    // Sprint 26: register the StoreCategory enum so the store UI can filter by
    // Featured, Productivity, Development, Utilities, System, and Entertainment.
    qmlRegisterUncreatableType<bos::shell::StoreCategoryEnum>(
        "BOS.Shell", 1, 0, "StoreCategory",
        QStringLiteral("StoreCategory is an enum and cannot be instantiated"));
}

void Application::exposeDesignManagers()
{
    // Sprint 15: expose BDL design managers as QML context properties so all
    // QML components can reference the same token sources.
    // Sprint 30: extend ThemeManager with adaptive metrics and add
    // AdaptiveLayoutManager and AccessibilityManager.
    auto themeManager = std::make_unique<ThemeManager>();
    auto designTokens = std::make_unique<DesignTokens>();
    auto typographyManager = std::make_unique<TypographyManager>();
    auto spacingManager = std::make_unique<SpacingManager>();
    auto iconManager = std::make_unique<IconManager>();
    auto adaptiveLayoutManager = std::make_unique<AdaptiveLayoutManager>();
    auto accessibilityManager = std::make_unique<AccessibilityManager>();

    // Initialize adaptive scales before exposing managers to QML.
    typographyManager->setScaleFactor(themeManager->textScale());
    iconManager->setScaleFactor(themeManager->iconScale());
    adaptiveLayoutManager->setScaleFactor(themeManager->scaleFactor());

    // Propagate scale changes when the screen geometry or device pixel ratio
    // changes so that typography, icon, and layout metrics stay consistent.
    QObject::connect(themeManager.get(), &ThemeManager::metricsChanged,
                     [theme = themeManager.get(),
                      typography = typographyManager.get(),
                      icons = iconManager.get(),
                      layout = adaptiveLayoutManager.get()]() {
        typography->setScaleFactor(theme->textScale());
        icons->setScaleFactor(theme->iconScale());
        layout->setScaleFactor(theme->scaleFactor());
    });

    m_engine->rootContext()->setContextProperty(QStringLiteral("ThemeManager"), themeManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("DesignTokens"), designTokens.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("TypographyManager"), typographyManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("SpacingManager"), spacingManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("IconManager"), iconManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("AdaptiveLayoutManager"), adaptiveLayoutManager.get());
    m_engine->rootContext()->setContextProperty(QStringLiteral("AccessibilityManager"), accessibilityManager.get());

    themeManager->setParent(m_engine.get());
    designTokens->setParent(m_engine.get());
    typographyManager->setParent(m_engine.get());
    spacingManager->setParent(m_engine.get());
    iconManager->setParent(m_engine.get());
    adaptiveLayoutManager->setParent(m_engine.get());
    accessibilityManager->setParent(m_engine.get());

    themeManager.release();
    designTokens.release();
    typographyManager.release();
    spacingManager.release();
    iconManager.release();
    adaptiveLayoutManager.release();
    accessibilityManager.release();
}

void Application::loadLoginInterface()
{
    // Expose the wallpaper source path so the login screen can share the same
    // desktop background.
    const QString wallpaperPath = QCoreApplication::applicationDirPath()
        + QStringLiteral("/assets/wallpapers/default.jpg");
    m_engine->rootContext()->setContextProperty(
        QStringLiteral("wallpaperSource"),
        QUrl::fromLocalFile(wallpaperPath));

    // Load the login screen from the embedded BOS.Shell module.
    m_engine->loadFromModule(QStringLiteral("BOS.Shell"), QStringLiteral("LoginScreen"));

    const auto objects = m_engine->rootObjects();
    if (!objects.isEmpty()) {
        m_loginWindow = objects.last();
    }
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
    // Sprint 22 startup sequence:
    //   Initialize SessionManager (registers modules including LoginModule).
    //   Expose LoginManager and design managers.
    //   Load LoginScreen.
    //   On successful login -> start desktop session and load Desktop.
    m_sessionManager->initialize();

    registerQmlTypes();
    exposeDesignManagers();

    // Sprint 22: expose the LoginManager to the login screen.
    LoginManager *loginManager = nullptr;
    if (auto *loginModule = dynamic_cast<LoginModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Login")))) {
        loginManager = loginModule->loginManager();
        if (loginManager) {
            m_engine->rootContext()->setContextProperty(QStringLiteral("loginManager"), loginManager);
        }
    }

    // Sprint 22: wire notifications into LoginManager as early as possible so
    // successful login/logout events can create information notifications.
    auto *notificationModule = dynamic_cast<NotificationModule*>(
        m_sessionManager->moduleManager()->findModule(QStringLiteral("Notification")));
    NotificationManager *notificationManager = notificationModule
        ? notificationModule->notificationManager()
        : nullptr;
    if (loginManager && notificationManager) {
        loginManager->setNotificationManager(notificationManager);
    }

    // Sprint 26.5: establish signal connections before any state transition.
    // This ensures login success/failure cannot race with the handlers.
    if (loginManager) {
        QObject::connect(loginManager, &LoginManager::loggedIn, &m_app, [this, loginManager]() {
            if (m_loginWindow) {
                m_loginWindow->setProperty("visible", false);
            }
            startDesktopSession();
        }, Qt::QueuedConnection);

        QObject::connect(loginManager, &LoginManager::loggedOut, &m_app, [this]() {
            if (m_loginWindow) {
                m_loginWindow->setProperty("visible", true);
            }
            m_sessionManager->stop();
        }, Qt::QueuedConnection);
    }

    // Transition the login manager from Booting to WaitingForSelection so the
    // login screen is presented immediately.
    if (loginManager) {
        loginManager->cancel();
    }

    loadLoginInterface();

    if (m_engine->rootObjects().isEmpty()) {
        return -1;
    }

    // Run the Qt event loop until the user closes the window.
    return QCoreApplication::exec();
}

void Application::startDesktopSession()
{
    // Sprint 5 startup sequence continues here:
    //   ModuleManager.start() -> expose WindowManager -> load QML
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

    // Sprint 21: wire the NotificationManager into the DragManager and expose the
    // manager as a QML context property.
    if (auto *dragModule = dynamic_cast<DragModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Drag")))) {
        if (auto *dragManager = dragModule->dragManager()) {
            dragManager->setNotificationManager(notificationManager);
            m_engine->rootContext()->setContextProperty(QStringLiteral("dragManager"), dragManager);
        }
    }

    // Sprint 22: wire the NotificationManager into the LoginManager so login and
    // logout events can create information notifications.
    if (auto *loginModule = dynamic_cast<LoginModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Login")))) {
        if (auto *loginManager = loginModule->loginManager()) {
            loginManager->setNotificationManager(notificationManager);
        }
    }

    // Sprint 23: wire the NotificationManager into the LockManager and expose the
    // manager as a QML context property.
    if (auto *lockModule = dynamic_cast<LockModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Lock")))) {
        if (auto *lockManager = lockModule->lockManager()) {
            lockManager->setNotificationManager(notificationManager);
            m_engine->rootContext()->setContextProperty(QStringLiteral("lockManager"), lockManager);
        }
    }

    // Sprint 24: wire the NotificationManager into the UpdateManager and expose
    // the manager as a QML context property.
    if (auto *updateModule = dynamic_cast<UpdateModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Update")))) {
        if (auto *updateManager = updateModule->updateManager()) {
            updateManager->setNotificationManager(notificationManager);
            m_engine->rootContext()->setContextProperty(QStringLiteral("updateManager"), updateManager);
        }
    }

    // Sprint 25: wire the NotificationManager into the PackageManager and expose
    // the manager as a QML context property.
    PackageManager *packageManagerPtr = nullptr;
    if (auto *packageModule = dynamic_cast<PackageModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Package")))) {
        if (auto *packageManager = packageModule->packageManager()) {
            packageManager->setNotificationManager(notificationManager);
            m_engine->rootContext()->setContextProperty(QStringLiteral("packageManager"), packageManager);
            packageManagerPtr = packageManager;
        }
    }

    // Sprint 26: wire the PackageManager and NotificationManager into the
    // StoreManager and expose the manager as a QML context property.
    if (auto *storeModule = dynamic_cast<StoreModule*>(
            m_sessionManager->moduleManager()->findModule(QStringLiteral("Store")))) {
        if (auto *storeManager = storeModule->storeManager()) {
            storeManager->setPackageManager(packageManagerPtr);
            storeManager->setNotificationManager(notificationManager);
            m_engine->rootContext()->setContextProperty(QStringLiteral("storeManager"), storeManager);
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

    // Sprint 26: instantiate the Baytevora Store application handler, wire it to
    // the window and notification services, and register it with the coordinator.
    auto store = std::make_unique<StoreApplication>();
    StoreApplication *storePtr = store.get();
    if (windowManager) {
        storePtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        storePtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setStoreApplication(storePtr);
    }
    store->setParent(m_engine.get());
    store.release();

    // Sprint 49: instantiate the Baytevora Package Manager application handler,
    // wire it to the window and notification services, and register it with the
    // coordinator.
    auto packageManagerApp = std::make_unique<PackageManagerApplication>();
    PackageManagerApplication *packageManagerAppPtr = packageManagerApp.get();
    if (windowManager) {
        packageManagerAppPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        packageManagerAppPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setPackageManagerApplication(packageManagerAppPtr);
    }
    packageManagerApp->setParent(m_engine.get());
    packageManagerApp.release();

    // Sprint 27: instantiate the Baytevora Browser application handler, wire it to
    // the window and notification services, and register it with the coordinator.
    auto browser = std::make_unique<BrowserApplication>();
    BrowserApplication *browserPtr = browser.get();
    if (windowManager) {
        browserPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        browserPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setBrowserApplication(browserPtr);
    }
    browser->setParent(m_engine.get());
    browser.release();

    // Sprint 28: instantiate the Baytevora Notes application handler, wire it to
    // the window and notification services, and register it with the coordinator.
    auto notes = std::make_unique<NotesApplication>();
    NotesApplication *notesPtr = notes.get();
    if (windowManager) {
        notesPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        notesPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setNotesApplication(notesPtr);
    }

    // Sprint 46: expose NotesApplication to QML so Notes windows can consume
    // pending .bnote file open requests from the File Manager.
    qmlRegisterSingletonInstance<NotesApplication>("BOS.Shell", 1, 0,
                                                     "NotesApplication",
                                                     notesPtr);

    notes->setParent(m_engine.get());
    notes.release();

    // Sprint 29: instantiate the Baytevora Image Viewer application handler, wire
    // it to the window and notification services, and register it with the coordinator.
    auto imageViewer = std::make_unique<ImageViewerApplication>();
    ImageViewerApplication *imageViewerPtr = imageViewer.get();
    if (windowManager) {
        imageViewerPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        imageViewerPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setImageViewerApplication(imageViewerPtr);
    }

    // Sprint 47: expose ImageViewerApplication to QML so Image Viewer windows can
    // consume pending file open requests from the File Manager.
    qmlRegisterSingletonInstance<ImageViewerApplication>("BOS.Shell", 1, 0,
                                                           "ImageViewerApplication",
                                                           imageViewerPtr);

    imageViewer->setParent(m_engine.get());
    imageViewer.release();

    // Sprint 31: instantiate the Baytevora Calculator application handler, wire it
    // to the window and notification services, and register it with the coordinator.
    auto calculator = std::make_unique<CalculatorApplication>();
    CalculatorApplication *calculatorPtr = calculator.get();
    if (windowManager) {
        calculatorPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        calculatorPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setCalculatorApplication(calculatorPtr);
    }
    calculator->setParent(m_engine.get());
    calculator.release();

    // Sprint D: instantiate the Baytevora PDF Studio application handler, wire it
    // to the window, notification, and print services, and register it with the
    // coordinator.
    auto pdfStudio = std::make_unique<PdfStudioApplication>();
    PdfStudioApplication *pdfStudioPtr = pdfStudio.get();
    if (windowManager) {
        pdfStudioPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        pdfStudioPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setPdfStudioApplication(pdfStudioPtr);
    }
    qmlRegisterSingletonInstance<PdfStudioApplication>("BOS.Shell", 1, 0,
                                                         "PdfStudioApplication",
                                                         pdfStudioPtr);
    pdfStudio->setParent(m_engine.get());
    pdfStudio.release();

    // Sprint 33: instantiate the Baytevora Archive Manager application handler,
    // wire it to the window and notification services, and register it with the
    // application coordinator.
    auto archive = std::make_unique<ArchiveApplication>();
    ArchiveApplication *archivePtr = archive.get();
    if (windowManager) {
        archivePtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        archivePtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setArchiveApplication(archivePtr);
    }
    archive->setParent(m_engine.get());
    archive.release();

    // Sprint 34: instantiate the Baytevora Media Player application handler,
    // wire it to the window and notification services, and register it with the
    // application coordinator.
    auto mediaPlayer = std::make_unique<MediaPlayerApplication>();
    MediaPlayerApplication *mediaPlayerPtr = mediaPlayer.get();
    if (windowManager) {
        mediaPlayerPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        mediaPlayerPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setMediaPlayerApplication(mediaPlayerPtr);
    }
    mediaPlayer->setParent(m_engine.get());
    mediaPlayer.release();

    // Sprint 35: instantiate the Baytevora Text Editor application handler,
    // wire it to the window and notification services, and register it with the
    // application coordinator.
    auto textEditor = std::make_unique<TextEditorApplication>();
    TextEditorApplication *textEditorPtr = textEditor.get();
    if (windowManager) {
        textEditorPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        textEditorPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setTextEditorApplication(textEditorPtr);
    }
    textEditor->setParent(m_engine.get());
    textEditor.release();

    // Sprint 36: instantiate the Baytevora System Monitor application handler,
    // wire it to the window and notification services, and register it with the
    // application coordinator.
    auto systemMonitor = std::make_unique<SystemMonitorApplication>();
    SystemMonitorApplication *systemMonitorPtr = systemMonitor.get();
    if (windowManager) {
        systemMonitorPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        systemMonitorPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setSystemMonitorApplication(systemMonitorPtr);
    }
    systemMonitor->setParent(m_engine.get());
    systemMonitor.release();

    // Sprint 37: instantiate the Baytevora Task Manager application handler,
    // wire it to the window and notification services, and register it with the
    // application coordinator.
    auto taskManagerApp = std::make_unique<TaskManagerApplication>();
    TaskManagerApplication *taskManagerAppPtr = taskManagerApp.get();
    if (windowManager) {
        taskManagerAppPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        taskManagerAppPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setTaskManagerApplication(taskManagerAppPtr);
    }
    taskManagerApp->setParent(m_engine.get());
    taskManagerApp.release();

    // Sprint 38: instantiate the Baytevora Network Manager application
    // handler, wire it to the window and notification services, and register
    // it with the application coordinator.
    auto networkApp = std::make_unique<NetworkApplication>();
    NetworkApplication *networkAppPtr = networkApp.get();
    if (windowManager) {
        networkAppPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        networkAppPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setNetworkApplication(networkAppPtr);
    }
    networkApp->setParent(m_engine.get());
    networkApp.release();

    // Sprint 39: instantiate the Baytevora Storage Manager application
    // handler, wire it to the window and notification services, and register
    // it with the application coordinator.
    auto storageApp = std::make_unique<StorageApplication>();
    StorageApplication *storageAppPtr = storageApp.get();
    if (windowManager) {
        storageAppPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        storageAppPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setStorageApplication(storageAppPtr);
    }
    storageApp->setParent(m_engine.get());
    storageApp.release();

    // Sprint 40: instantiate the Baytevora Printing Framework application
    // handler, wire it to the window and notification services, and register
    // it with the application coordinator.
    auto printApp = std::make_unique<PrintApplication>();
    PrintApplication *printAppPtr = printApp.get();
    if (windowManager) {
        printAppPtr->setWindowManager(windowManager);
    }
    if (notificationManager) {
        printAppPtr->setNotificationManager(notificationManager);
    }
    if (applicationManager) {
        applicationManager->setPrintApplication(printAppPtr);
    }
    printApp->setParent(m_engine.get());
    printApp.release();

    // Sprint 40: create a shared PrintManager instance for cross-application
    // printing hooks (PDF Viewer, Text Editor, Image Viewer, etc.). The
    // Print Manager window still owns an independent PrintManager.
    auto sharedPrintManager = std::make_unique<PrintManager>();
    if (notificationManager) {
        sharedPrintManager->setNotificationManager(notificationManager);
    }
    m_engine->rootContext()->setContextProperty(QStringLiteral("printManager"),
                                                sharedPrintManager.get());
    sharedPrintManager->setParent(m_engine.get());
    sharedPrintManager.release();

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
}

} // namespace bos::shell
