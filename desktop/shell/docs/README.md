# BDE Shell

## Overview

The Baytevora Desktop Environment (BDE) Shell implemented through Sprint 20.

The shell includes a modular session/module system, window manager with focus and state control, taskbar, launcher, application framework, notification service, desktop icons, a global clipboard service, a global keyboard shortcut manager, the Baytevora Search Service (BSS), and the Baytevora Power Management Service (BPS). Each sprint is built on top of the previous one without rewriting earlier work.

## Technology Stack

- C++17
- Qt 6
- Qt Quick (QML)
- CMake

## Build Requirements

- CMake 3.16 or newer
- Qt 6.2 or newer with the `Quick` and `Widgets` modules installed
- A C++17-compatible compiler (GCC, Clang, MSVC)

## Qt Dependencies

- Qt6::Core
- Qt6::Quick
- Qt6::Widgets
- Qt6::Qml (transitive dependency of Quick)

## Build Instructions

### Command Line

```bash
cd baytevora-os-main/desktop/shell
mkdir build && cd build
cmake ..
cmake --build .
```

### Qt Creator

1. Open `desktop/shell/CMakeLists.txt` in Qt Creator.
2. Configure the project with a suitable Qt 6 kit.
3. Build and run the `BOS_Shell` target.

### CLion

1. Open the `desktop/shell` directory in CLion.
2. CLion will detect `CMakeLists.txt` automatically.
3. Select a Qt 6 toolchain and run the `BOS_Shell` target.

## Run

```bash
./build/BOS_Shell
```

The application will open a borderless fullscreen window with a dark blue background. Close the window to exit.

## File Explanations

| File | Purpose |
|------|---------|
| `CMakeLists.txt` | CMake build configuration following Qt's recommended structure |
| `src/main.cpp` | Application entry point; creates QGuiApplication and starts the shell |
| `include/bos/Application.h` | Header for the modular Application class |
| `src/Application.cpp` | Implementation of the Application class; owns the SessionManager, manages the QML engine, and exposes the wallpaper path to QML |
| `include/bos/SessionManager.h` | Header for the SessionManager class |
| `src/SessionManager.cpp` | Implementation of the SessionManager; owns the ModuleManager and controls startup order |
| `src/ModuleManager.cpp` | Implementation of the ModuleManager; registers and runs module lifecycle methods |
| `src/DesktopSurfaceModule.cpp` | Placeholder implementation of the DesktopSurface module |
| `src/WallpaperModule.cpp` | Placeholder implementation of the Wallpaper module |
| `src/WindowManager.cpp` | Implementation of the WindowManager framework |
| `src/Window.cpp` | Implementation of the lightweight Window data model |
| `include/bos/DesktopModule.h` | Abstract base class for desktop modules |
| `include/bos/ModuleManager.h` | Header for the ModuleManager |
| `include/bos/DesktopSurfaceModule.h` | Header for the DesktopSurface placeholder module |
| `include/bos/WallpaperModule.h` | Header for the Wallpaper placeholder module |
| `include/bos/WindowManager.h` | Header for the WindowManager |
| `include/bos/Window.h` | Header for the Window data model |
| `include/bos/TaskbarModule.h` | Header for the Taskbar placeholder module |
| `include/bos/LauncherModule.h` | Header for the Launcher module |
| `include/bos/ApplicationInfo.h` | Lightweight application metadata model |
| `include/bos/ApplicationRegistry.h` | Header for the application registry |
| `include/bos/ApplicationLauncher.h` | Header for the launch request validator |
| `include/bos/ApplicationManager.h` | Header for the application launch coordinator |
| `include/bos/Notification.h` | Notification data model with severity levels |
| `include/bos/NotificationManager.h` | Header for the active notification manager |
| `include/bos/NotificationModule.h` | Header for the notification desktop module |
| `include/bos/FileSystemModel.h` | Directory listing model for the File Manager |
| `include/bos/FileManagerApplication.h` | File Manager application handler |
| `include/bos/SettingsPage.h` | Lightweight settings page data model |
| `include/bos/SettingsManager.h` | Settings backing model with pages and system info |
| `include/bos/SettingsApplication.h` | Settings application handler |
| `include/bos/TerminalSession.h` | Per-window terminal identity and working directory |
| `include/bos/TerminalManager.h` | Per-window terminal command processor and output buffer |
| `include/bos/TerminalApplication.h` | Terminal application handler |
| `include/bos/ThemeManager.h` | BDL color palette provider |
| `include/bos/DesignTokens.h` | BDL corner radius and shared tokens |
| `include/bos/TypographyManager.h` | BDL type scale and font family |
| `include/bos/SpacingManager.h` | BDL spacing scale |
| `include/bos/IconManager.h` | BDL icon size constants |
| `include/bos/DesktopItem.h` | Data model for a single desktop icon |
| `include/bos/DesktopModel.h` | QAbstractListModel backing the desktop icon list |
| `include/bos/DesktopManager.h` | Owns the desktop icon model and exposes it to QML |
| `include/bos/DesktopIconsModule.h` | Desktop module that owns the DesktopManager |
| `include/bos/ClipboardItem.h` | Data model for a single clipboard entry |
| `include/bos/ClipboardManager.h` | Central clipboard manager wrapping QClipboard |
| `include/bos/ClipboardModule.h` | Desktop module that owns the ClipboardManager |
| `include/bos/ShortcutContext.h` | Enum for shortcut contexts (Global/Application/Window) |
| `include/bos/Shortcut.h` | Data model for a single registered shortcut |
| `include/bos/ShortcutManager.h` | Central keyboard shortcut manager using QShortcut |
| `include/bos/ShortcutModule.h` | Desktop module that owns the ShortcutManager |
| `include/bos/SearchCategory.h` | Enum for search categories (Application/Setting/Desktop/Command) |
| `include/bos/SearchItem.h` | Data model for one searchable item |
| `include/bos/SearchProvider.h` | Abstract interface for search providers |
| `include/bos/SearchManager.h` | Central search manager indexing and querying items |
| `include/bos/SearchModule.h` | Desktop module that owns the SearchManager and built-in providers |
| `include/bos/ApplicationSearchProvider.h` | Built-in application search provider |
| `include/bos/DesktopSearchProvider.h` | Built-in desktop location search provider |
| `include/bos/SettingsSearchProvider.h` | Built-in Settings page search provider |
| `include/bos/PowerActionType.h` | Enum for power action types |
| `include/bos/PowerAction.h` | Data model for one power action |
| `include/bos/PowerManager.h` | Central power action manager |
| `include/bos/PowerModule.h` | Desktop module that owns the PowerManager |
| `qml/Desktop.qml` | Root window: borderless fullscreen container for the desktop surface |
| `qml/DesktopSurface.qml` | Desktop surface container that fills the window and renders windows |
| `qml/Wallpaper.qml` | Reusable wallpaper component with image scaling and fallback color |
| `qml/WindowFrame.qml` | Reusable minimal window frame component |
| `qml/WindowButton.qml` | Small static title-bar button used by WindowFrame |
| `qml/Taskbar.qml` | Bottom-of-screen taskbar container |
| `qml/TaskbarButton.qml` | Flat reusable button used in the taskbar |
| `qml/RunningApps.qml` | Taskbar component showing one button per non-closed window |
| `qml/Clock.qml` | Minimal HH:MM digital clock for the taskbar |
| `qml/Launcher.qml` | Launcher overlay and panel |
| `qml/LauncherButton.qml` | Reusable launcher grid entry button |
| `qml/LauncherGrid.qml` | Grid of placeholder application entries |
| `qml/LauncherHeader.qml` | Static launcher header with title and welcome line |
| `qml/NotificationCenter.qml` | Top-right notification container |
| `qml/NotificationPopup.qml` | Individual notification card |
| `qml/FileManagerWindow.qml` | Main File Manager window content |
| `qml/Sidebar.qml` | Common locations sidebar |
| `qml/FileList.qml` | Directory listing view |
| `qml/Toolbar.qml` | File Manager toolbar |
| `qml/StatusBar.qml` | File Manager status bar |
| `qml/ToolButton.qml` | Reusable toolbar button |
| `qml/HeaderLabel.qml` | List header label helper |
| `qml/CellLabel.qml` | List cell label helper |
| `qml/SettingsWindow.qml` | Main Settings window content |
| `qml/NavigationSidebar.qml` | Settings page navigation sidebar |
| `qml/SettingsContent.qml` | Settings page header and content container |
| `qml/SettingsPage.qml` | Body of each settings page |
| `qml/SettingsButton.qml` | Reusable light-themed settings button |
| `qml/InfoRow.qml` | Read-only label/value row helper |
| `qml/TerminalWindow.qml` | Main Terminal window content |
| `qml/TerminalToolbar.qml` | Terminal toolbar with current directory and status |
| `qml/TerminalView.qml` | Terminal output and command input |
| `qml/TerminalStatusBar.qml` | Terminal status bar |
| `qml/DesktopIcons.qml` | Desktop icon container bound to DesktopManager model |
| `qml/DesktopIcon.qml` | Single desktop icon with selection and activation |
| `qml/DesktopSelection.qml` | Placeholder component for future selection UI |
| `assets/wallpapers/default.jpg` | Default wallpaper image |
| `../../design/BDL.md` | Baytevora Design Language overview |
| `../../design/Colors.md` | BDL color palette |
| `../../design/Typography.md` | BDL typography scale |
| `../../design/Spacing.md` | BDL spacing tokens |
| `../../design/Motion.md` | BDL motion standards |
| `../../design/Icons.md` | BDL icon size constants |
| `../../design/Accessibility.md` | BDL accessibility requirements |
| `../../design/Components.md` | BDL component standards |
| `docs/README.md` | This documentation |

## Design Notes

- The project uses `qt_add_qml_module()` to embed QML files as a resource module.
- The application loads `Desktop.qml` from the `BOS.Shell` module using `loadFromModule()`.
- The `Application` class exposes `wallpaperSource` as a QML context property pointing to `<appDir>/assets/wallpapers/default.jpg`.
- `CMakeLists.txt` copies the `assets/` directory into the build output folder at build time so the executable can locate the wallpaper at runtime.
- If `assets/wallpapers/default.jpg` is missing or cannot be loaded, the `Wallpaper` component logs a warning and displays the fallback dark blue background.
- The wallpaper uses `Image.PreserveAspectCrop` so it fills the screen while preserving aspect ratio.
- The `Application` class is kept small and focused so future sprints can add panels, window management, settings, and other desktop components without restructuring the codebase.

## Sprint 2 Changes

- Added `DesktopSurface.qml` as the container for all desktop content.
- Added reusable `Wallpaper.qml` component with automatic fallback handling.
- Updated `Desktop.qml` to load the `DesktopSurface`.
- Updated `Application.cpp` to expose the wallpaper source path to QML.
- Updated `CMakeLists.txt` to include the new QML files and copy the `assets/` directory at build time.
- Added `assets/wallpapers/default.jpg` as the default wallpaper.

## Sprint 3 Changes

- Added `SessionManager` class (`include/bos/SessionManager.h`, `src/SessionManager.cpp`) to coordinate the desktop session lifecycle.
- Updated `Application` to own the `SessionManager` instance.
- Added `[BDE]` startup log messages and a `shutdown()` placeholder.

## Sprint 4 Changes

- Added `DesktopModule` abstract base class defining the module interface (`name`, `initialize`, `start`, `shutdown`).
- Added `ModuleManager` class that owns registered modules and runs their lifecycle methods in order.
- Added placeholder modules `DesktopSurfaceModule` and `WallpaperModule` that inherit from `DesktopModule` and log lifecycle events.
- Updated `SessionManager` to own a `ModuleManager` and drive the module system.
- Updated `Application::run()` to the new startup sequence:
  1. `SessionManager::initialize()`
  2. `ModuleManager::registerModule()` (inside SessionManager)
  3. `ModuleManager::initializeAll()` (inside SessionManager)
  4. `ModuleManager::startAll()` (inside SessionManager)
  5. Load `Desktop.qml`
- Updated shutdown path: `SessionManager::shutdown()` calls `ModuleManager::shutdownAll()`.

### Startup Flow

```
main()
  └── QGuiApplication
        └── bos::shell::Application
              └── SessionManager::initialize()
                    ├── ModuleManager::registerModule(DesktopSurfaceModule)
                    ├── ModuleManager::registerModule(WallpaperModule)
                    ├── ModuleManager::initializeAll()
                    └── (SessionManager::start() -> ModuleManager::startAll())
              └── load Desktop.qml
```

### Module Ownership

```
Application
  └── SessionManager
        └── ModuleManager
              ├── DesktopSurfaceModule
              ├── WallpaperModule
              └── WindowManager
```

## Sprint 5 Changes

- Added lightweight `Window` data model (`include/bos/Window.h`, `src/Window.cpp`) with id, title, geometry, and visibility.
- Added `WindowManager` class (`include/bos/WindowManager.h`, `src/WindowManager.cpp`) that inherits from `DesktopModule` and `QObject` to expose window state to QML.
- `WindowManager` responsibilities: register/remove windows, assign unique IDs, list active windows, find by ID.
- Registered `WindowManager` with the `ModuleManager` so it participates in the module lifecycle.
- `WindowManager::start()` creates one demonstration window automatically.
- Added `ModuleManager::findModule()` and `SessionManager::moduleManager()` so `Application` can locate the `WindowManager` and expose it to QML.
- Updated `Application::run()` to set the `windowManager` context property before loading `Desktop.qml`.
- Added `qml/WindowFrame.qml`, a reusable minimal window frame with title bar, background, and simple border.
- Updated `qml/DesktopSurface.qml` to render every registered window via a `Repeater` over `windowManager.windows`.
- No forbidden features from Sprint 5 were implemented.

## Sprint 6 Changes

- Extended `Window` data model with `isActive` to track focus state.
- Extended `WindowManager` with focus API.
- At startup, the demonstration window automatically becomes the active window.
- `WindowManager` logs focus changes.
- Updated `qml/WindowFrame.qml` with click detection and active styling.
- Business logic remains in C++; QML only handles input and presentation.
- No forbidden features from Sprint 6 were implemented.

## Sprint 7 Changes

- Added `WindowState` enum and extended `Window` with state storage and normal-geometry snapshot helpers.
- Extended `WindowManager` with state transition methods.
- Added title-bar control buttons in `qml/WindowFrame.qml`.
- Updated `qml/DesktopSurface.qml` to hide minimized windows.
- Updated `CMakeLists.txt` and documentation.
- No forbidden features from Sprint 7 were implemented.

## Sprint 8 Changes

- Added `TaskbarModule` (`include/bos/TaskbarModule.h`, `src/TaskbarModule.cpp`), a placeholder desktop module that logs taskbar lifecycle events.
- Registered `TaskbarModule` with the `ModuleManager` in `SessionManager`.
- Added `WindowManager::taskbarButtonClicked(id)` to handle taskbar button clicks entirely in C++:
  - Minimized window → restore.
  - Already active window → no-op.
  - Inactive window → focus.
- Created taskbar QML components:
  - `qml/Taskbar.qml` — 40 px bottom bar, dark charcoal background, 1 px lighter gray top border.
  - `qml/TaskbarButton.qml` — flat, reusable button; no animations, hover effects, or shadows.
  - `qml/RunningApps.qml` — binds to `windowManager.windows` and `activeWindowId` to display one button per non-closed window.
  - `qml/Clock.qml` — digital clock in `HH:MM` format, updates every minute via `Qt.formatTime` and a `Timer`.
- Updated `qml/Desktop.qml` to include the `Taskbar` above the desktop surface.
- BOS button logs `[BDE] BOS button clicked` on click.
- Updated `CMakeLists.txt` to include the new C++ source/header and QML files.
- Updated documentation with taskbar architecture and interaction diagrams.
- No forbidden features are implemented: no start menu, search, system tray, notifications, quick settings, volume, network, battery, context menus, dragging taskbar, auto hide, or animations.

## Sprint 9 Changes

- Added `LauncherModule` (`include/bos/LauncherModule.h`, `src/LauncherModule.cpp`), a desktop module that owns the launcher visibility state.
- Registered `LauncherModule` with the `ModuleManager` in `SessionManager`.
- Exposed `LauncherModule` to QML as the `launcher` context property in `Application.cpp`.
- Added `openLauncher()`, `closeLauncher()`, `toggleLauncher()`, and `requestLaunch(appName)` methods in `LauncherModule`. Visibility is exposed through the `visible` QML property with `visibleChanged` notifications.
- Created launcher QML components:
  - `qml/Launcher.qml` — full-screen overlay that appears when `launcher.visible` is true; anchored to the bottom-left above the taskbar; closes on outside click or Escape.
  - `qml/LauncherHeader.qml` — static header showing "Baytevora OS" and "Welcome".
  - `qml/LauncherGrid.qml` — grid of six placeholder applications (File Manager, Terminal, Settings, Browser, Calculator, Notes).
  - `qml/LauncherButton.qml` — flat, reusable grid entry with a placeholder icon and application name.
- Updated `qml/Taskbar.qml`: the BOS button now toggles `launcher.visible` and highlights while the launcher is open.
- Updated `qml/Desktop.qml` to include the `Launcher` overlay.
- Updated `CMakeLists.txt` to include the new C++ source/header and QML files.
- Updated documentation with launcher architecture, taskbar ↔ launcher interaction, visibility lifecycle, and module ownership.
- No forbidden features are implemented: no search, categories, favorites, recently used, drag and drop, context menus, keyboard navigation beyond Escape, animations, or real application launching.

## Sprint 10 Changes

- Added the Application Framework:
  - `ApplicationInfo` (`include/bos/ApplicationInfo.h`) — lightweight metadata model.
  - `ApplicationRegistry` (`include/bos/ApplicationRegistry.h`, `src/ApplicationRegistry.cpp`) — owns installed applications, supports find by ID/name and list all.
  - `ApplicationLauncher` (`include/bos/ApplicationLauncher.h`, `src/ApplicationLauncher.cpp`) — validates launch requests.
  - `ApplicationManager` (`include/bos/ApplicationManager.h`, `src/ApplicationManager.cpp`) — module that owns registry and launcher, registers placeholder apps, tracks running apps, enforces `singleInstance`, and requests demo windows from `WindowManager`.
- Registered `ApplicationManager` with `ModuleManager` in `SessionManager`.
- Added `WindowManager::createApplicationWindow(title)` so `ApplicationManager` can request windows without manipulating them directly.
- Added `WindowManager::windowClosed(id)` signal so `ApplicationManager` can remove applications from the running set when their windows close.
- Wired `ApplicationManager` to `WindowManager` and exposed `ApplicationManager` to QML as `applicationManager` in `Application.cpp`.
- Updated `LauncherGrid.qml` to display applications from `ApplicationManager.applications` and call `ApplicationManager.launchApplication(name)` when clicked.
- Updated `LauncherButton.qml` to display the `iconName` from `ApplicationInfo` with a fallback to the first two letters of the application name.
- Updated `CMakeLists.txt` with the new C++ sources and headers.
- Updated documentation with Application Framework overview, class relationships, launch sequence, registration lifecycle, and single-instance enforcement.
- No forbidden features are implemented: no real binary execution, plugin loading, package management, installation, updates, permissions, sandboxing, background services, search, or favorites.

### Launcher Application Launch Sequence

```
User clicks an application entry in LauncherGrid.qml
        |
        v
ApplicationManager.launchApplication(name)
        |
        +-- logs [BDE] Launch request: <name>
        |
        v
ApplicationLauncher::canLaunch(name)
        |
        v
ApplicationRegistry::findByName(name)
        |
        v
if singleInstance and already running:
        +-- logs [BDE] Launch denied: <name> already running
        +-- returns false
else:
        +-- logs [BDE] Launch approved
        |
        v
WindowManager::createApplicationWindow(name)
        |
        +-- creates centered 700x450 window titled <name>
        +-- logs [BDE] Demo window created: <name>
        |
        v
WindowManager emits windowsChanged / activeWindowIdChanged
        |
        v
Desktop.qml updates automatically through property bindings
```

### Application Framework Class Relationships

```
ApplicationManager
        |
        |-- owns --> ApplicationRegistry
        |              |
        |              +-- contains ApplicationInfo
        |
        |-- owns --> ApplicationLauncher
        |
        |-- uses --> WindowManager (wired in Application.cpp)
        |
        +-- exposed to QML as applicationManager
```

## Sprint 11 Changes

- Added the Notification Service:
  - `Notification` (`include/bos/Notification.h`) — data model with `id`, `title`, `message`, `sourceApplication`, `timestamp`, and `severity` (Info, Success, Warning, Error).
  - `NotificationManager` (`include/bos/NotificationManager.h`, `src/NotificationManager.cpp`) — owns active notifications, generates unique IDs, provides create/remove/clear/find operations, and emits `notificationsChanged`.
  - `NotificationModule` (`include/bos/NotificationModule.h`, `src/NotificationModule.cpp`) — desktop module that initializes and owns `NotificationManager`.
- Registered `NotificationModule` with `ModuleManager` in `SessionManager`.
- Exposed `NotificationManager` to QML as `notificationManager` in `Application.cpp`.
- Updated `ApplicationManager` with `setNotificationManager()` so it can notify on launch.
- `ApplicationManager::launchApplication()` now creates a `Success` notification titled "Application Started" with the message `<name> launched successfully.`.
- Added startup demonstration notification in `Application.cpp` after the QML interface loads: "Welcome to Baytevora OS" / "Desktop environment initialized successfully." / Source "System" / Severity "Info".
- Created QML components:
  - `qml/NotificationCenter.qml` — vertical column in the top-right corner, width ~340 px, margin ~20 px, bound to `notificationManager.notifications`.
  - `qml/NotificationPopup.qml` — card with title, message, source application, timestamp, and a close button; solid color based on severity; rounded corners; no shadows, transparency, or animations.
- Updated `qml/Desktop.qml` to include the `NotificationCenter` overlay.
- Updated `CMakeLists.txt` with the new C++ sources/headers and QML files.
- Updated documentation with notification architecture, lifecycle, ownership diagram, and `ApplicationManager` interaction.
- No forbidden features are implemented: no notification history, sounds, grouping, persistence, toast animations, timed dismissal, progress bars, action buttons, rich media, images, or icons.

### Notification Architecture

```
Application
        |
        v
SessionManager.start() -> ModuleManager.startAll()
        |
        +-- NotificationModule.start()
                |
                +-- NotificationManager initialized
        |
        v
Application.cpp wires NotificationModule -> notificationManager context property
        |
        +-- QML NotificationCenter binds to notificationManager.notifications
```

### Notification Lifecycle

```
Create notification:
        |
        v
NotificationManager::createNotification(title, message, source, severity)
        |
        +-- assigns unique ID
        +-- appends Notification to active list
        +-- logs [BDE] Notification created
        +-- emits notificationsChanged()
        |
        v
NotificationCenter.qml updates Repeater automatically
        |
        v
NotificationPopup.qml displays the notification

Dismiss notification:
        |
        v
User clicks close button on NotificationPopup.qml
        |
        v
onDismissed -> notificationManager.removeNotification(id)
        |
        +-- removes Notification from active list
        +-- logs [BDE] Notification dismissed
        +-- emits notificationsChanged()
        |
        v
NotificationCenter.qml removes the card automatically

Application launch notification:
        |
        v
ApplicationManager::launchApplication(name) succeeds
        |
        v
NotificationManager::createNotification("Application Started",
                                            "<name> launched successfully.",
                                            name,
                                            "success")
```

### Module Ownership

```
NotificationModule
        |
        +-- owns NotificationManager
                |
                +-- owns active Notification objects
                |
                +-- exposed to QML as notificationManager

ApplicationManager
        |
        +-- uses NotificationManager (set in Application.cpp)
                |
                +-- creates launch success notifications
```

### Taskbar ↔ Launcher Interaction

```
User clicks BOS button
        |
        v
TaskbarButton (input)
        |
        v
LauncherModule::toggleLauncher()
        |-- if hidden -> setVisible(true) -> log [BDE] Launcher opened
        +-- if visible -> setVisible(false) -> log [BDE] Launcher closed
        |
        v
visibleChanged()
        |
        v
Launcher.qml updates visibility through binding
```

### Taskbar ↔ WindowManager Interaction

```
User clicks a taskbar button
        |
        v
RunningApps.qml (input)
        |
        v
WindowManager::taskbarButtonClicked(id)
        |-- if minimized  -> restoreWindow(id)
        |-- if inactive   -> setActiveWindow(id)
        +-- if active     -> no-op
        |
        v
WindowManager emits windowsChanged / activeWindowIdChanged
        |
        v
RunningApps.qml updates automatically through property bindings
```

### Updated Startup Flow

```
main()
  └── QGuiApplication
        └── bos::shell::Application
              └── SessionManager::initialize()
                    ├── ModuleManager::registerModule(DesktopSurfaceModule)
                    ├── ModuleManager::registerModule(WallpaperModule)
                    ├── ModuleManager::registerModule(WindowManager)
                    ├── ModuleManager::registerModule(TaskbarModule)
                    └── ModuleManager::initializeAll()
              └── SessionManager::start()
                    └── ModuleManager::startAll()
                          ├── WindowManager creates demo window (Normal state) and sets it active
                          └── TaskbarModule starts
              └── expose windowManager to QML
              └── load Desktop.qml
```

### Module Ownership

```
Application
  └── SessionManager
        └── ModuleManager
              ├── DesktopSurfaceModule
              ├── WallpaperModule
              ├── WindowManager
              │     ├── Window (demo)
              │     └── focus / state management
              └── TaskbarModule
                    └── Taskbar.qml + RunningApps.qml + Clock.qml
```

## Sprint 12 Changes

- Added the first real BOS application: the File Manager.
- Created `FileSystemModel` (`include/bos/FileSystemModel.h`, `src/FileSystemModel.cpp`) — a `QAbstractListModel` that reads a directory with `QDir`, omits hidden files, lists folders before files, and exposes `name`, `type`, `size`, `lastModified`, and `isFolder` roles.
- Created `FileManagerApplication` (`include/bos/FileManagerApplication.h`, `src/FileManagerApplication.cpp`) — requests a managed 900×600 window from `WindowManager` and emits a startup "File Manager / Ready." info notification via `NotificationManager`.
- Registered `FileSystemModel` as a QML type in `Application.cpp` so each File Manager window can instantiate its own model from QML.
- Extended the `Window` data model with an `applicationName` property so the shell can choose the correct content view per window.
- Updated `WindowManager::registerWindow()` and `WindowManager::windowToMap()` to carry `applicationName`.
- Updated `WindowFrame.qml` to load `FileManagerWindow.qml` when `applicationName === "File Manager"`; other windows keep the placeholder content area.
- Updated `DesktopSurface.qml` to pass `applicationName` into each `WindowFrame` delegate.
- Updated `ApplicationManager` with `setFileManagerApplication()`; launching "File Manager" now delegates to `FileManagerApplication::open()` instead of creating a generic demo window.
- Wired `FileManagerApplication` with `WindowManager` and `NotificationManager` in `Application.cpp`.
- Created QML components:
  - `qml/FileManagerWindow.qml` — root File Manager content (toolbar, sidebar, file list, status bar).
  - `qml/Toolbar.qml` — back/forward (disabled), up, refresh, home, and read-only path field.
  - `qml/Sidebar.qml` — common locations (Home, Desktop, Documents, Downloads, Pictures, Music, Videos).
  - `qml/FileList.qml` — list view showing name, type, size, and last modified time.
  - `qml/StatusBar.qml` — item count and current folder name.
  - Helper components: `qml/ToolButton.qml`, `qml/HeaderLabel.qml`, `qml/CellLabel.qml`.
- File Manager already existed as a placeholder entry in `ApplicationRegistry`; the entry remains and is now the registration point used by `LauncherGrid`.
- Added Sprint 12 logging:
  - `[BDE] Directory opened`
  - `[BDE] Folder entered`
  - `[BDE] Refresh requested`
  - `[BDE] Home directory opened`
  - `[BDE] File open request: <filename>`
- Updated `CMakeLists.txt` and this documentation with the new C++ sources, headers, QML files, architecture, filesystem model, navigation flow, and ownership diagram.
- No forbidden features are implemented: no copy, move, delete, rename, drag and drop, file properties, search, tabs, bookmarks, context menus, file previews, trash, network drives, or permissions editor.

### File Manager Architecture

```
Launcher
        |
        v
ApplicationManager.launchApplication("File Manager")
        |
        v
ApplicationLauncher.canLaunch("File Manager")
        |
        v
FileManagerApplication.open()
        |
        +-- WindowManager.registerWindow("File Manager", 900, 600, x, y, "File Manager")
        +-- NotificationManager.createNotification("File Manager", "Ready.", "File Manager", "info")
        |
        v
WindowManager exposes window with applicationName "File Manager"
        |
        v
DesktopSurface Repeater creates WindowFrame
        |
        v
WindowFrame loads FileManagerWindow.qml
        |
        v
FileManagerWindow creates FileSystemModel { path: home }
        |
        v
FileSystemModel loads directory contents and exposes roles to FileList.qml
```

### Filesystem Model

```
FileSystemModel (QAbstractListModel)
        |
        +-- path property (set from QML, reloads model)
        |
        +-- roles: name, type, size, lastModified, isFolder
        |
        +-- loadDirectory()
                |
                +-- QDir::entryInfoList(NoDotAndDotDot | Dirs | Files)
                +-- omit hidden entries
                +-- append folders first
                +-- append files second
                +-- logs [BDE] Directory opened
        |
        +-- cdUp()
                |
                +-- QDir::cdUp()
                +-- logs [BDE] Folder entered
        |
        +-- refresh()
                |
                +-- logs [BDE] Refresh requested
```

### Navigation Flow

```
Sidebar location clicked
        |
        v
StandardPaths.standardLocations(<location>)[0]
        |
        v
fileSystemModel.path = <path>
        |
        v
FileSystemModel::setPath -> loadDirectory -> notificationsChanged
        |
        v
FileList.qml updates automatically through property bindings

Toolbar Up clicked
        |
        v
FileSystemModel::cdUp()
        |
        v
FileSystemModel::setPath(parent)
        |
        v
FileList.qml updates automatically

Toolbar Home clicked
        |
        v
fileSystemModel.path = StandardPaths.home
        |
        v
logs [BDE] Home directory opened
        |
        v
FileSystemModel::setPath -> loadDirectory
        |
        v
FileList.qml updates automatically

Toolbar Refresh clicked
        |
        v
FileSystemModel::refresh()
        |
        v
FileList.qml updates automatically

FileList double-click folder
        |
        v
fileSystemModel.path = currentPath + "/" + folderName
        |
        v
logs [BDE] Folder entered
        |
        v
FileSystemModel::setPath -> loadDirectory

FileList double-click file
        |
        v
logs [BDE] File open request: <filename>
        |
        +-- no launch (forbidden in Sprint 12)
```

### Ownership Diagram

```
Application
        |
        +-- SessionManager
        |       +-- ModuleManager
        |             +-- ApplicationManager
        |             |     +-- ApplicationRegistry
        |             |     |     +-- ApplicationInfo ("File Manager")
        |             |     +-- ApplicationLauncher
        |             |     +-- FileManagerApplication (set externally)

## Sprint 14 Changes

- Added the first native Terminal application.
- Created `TerminalSession` (`include/bos/TerminalSession.h`, `src/TerminalSession.cpp`) — per-window identity model holding the current user name, host name, working directory, and computed prompt string. It replaces the home directory with `~` in the prompt.
- Created `TerminalManager` (`include/bos/TerminalManager.h`, `src/TerminalManager.cpp`) — per-window command processor and output buffer. It owns a `TerminalSession`, exposes `output`, `lineCount`, `currentDirectory`, `status`, and `session` properties, and implements the built-in commands `help`, `clear`, `version`, `date`, and `pwd` internally. Unknown commands produce the friendly message "Command execution is not implemented yet." and are not executed externally.
- Created `TerminalApplication` (`include/bos/TerminalApplication.h`, `src/TerminalApplication.cpp`) — requests a managed 900×600 window from `WindowManager` and emits a startup "Terminal / Ready." info notification.
- Registered `TerminalManager` as a QML type in `Application.cpp` so each Terminal window can instantiate its own manager and session.
- Updated `ApplicationManager` with `setTerminalApplication()`; launching "Terminal" now delegates to `TerminalApplication::open()` instead of creating a generic demo window.
- Updated the placeholder "Terminal" entry in `ApplicationRegistry` to allow multiple instances (`singleInstance: false`).
- Updated `WindowFrame.qml` to load `TerminalWindow.qml` when `applicationName === "Terminal"`.
- Wired `TerminalApplication` with `WindowManager` and `NotificationManager` in `Application.cpp`.
- Created QML components:
  - `qml/TerminalWindow.qml` — root Terminal content (toolbar, view, status bar).
  - `qml/TerminalToolbar.qml` — current directory, session status, and New Session placeholder button.
  - `qml/TerminalView.qml` — read-only output TextArea and prompt-line TextField for command input.
  - `qml/TerminalStatusBar.qml` — status and output line count.
- Added Sprint 14 logging:
  - `[BDE] Terminal window opened (ID: <id>)`
  - `[BDE] Command received: <command>`
  - `[BDE] New session requested`
- Updated `CMakeLists.txt` and this documentation with new sources, headers, QML files, architecture, session/command flow, and ownership diagrams.
- No forbidden features are implemented: no bash/zsh/fish/PowerShell, external process execution, SSH, tabs, split panes, history persistence, autocomplete, clipboard, ANSI colors, PTY integration, package manager, or shell scripting.

### Terminal Architecture

```
Launcher
        |
        v
ApplicationManager.launchApplication("Terminal")
        |
        v
ApplicationLauncher.canLaunch("Terminal")
        |
        v
TerminalApplication.open()
        |
        +-- WindowManager.registerWindow("Terminal", 900, 600, x, y, "Terminal")
        +-- NotificationManager.createNotification("Terminal", "Ready.", "Terminal", "info")
        |
        v
WindowManager exposes window with applicationName "Terminal"
        |
        v
DesktopSurface Repeater creates WindowFrame
        |
        v
WindowFrame loads TerminalWindow.qml
        |
        v
TerminalWindow creates TerminalManager
        |
        v
TerminalView displays TerminalManager.output
        |
        v
User types command and presses Enter
        |
        v
TerminalManager.executeCommand(command)
        |
        +-- logs [BDE] Command received: <command>
        +-- built-in command -> internal result
        +-- unknown command -> "Command execution is not implemented yet."
        |
        v
Output buffer updates -> TerminalView refreshes automatically
```

### Terminal Session Model

```
TerminalSession (QObject)
        |
        +-- userName  -> $USER or "user"
        |
        +-- hostName  -> QSysInfo::machineHostName() or "bos"
        |
        +-- currentDirectory -> QDir::homePath()
        |
        +-- prompt() -> "user@host:dir$"
```

### Terminal Command Flow

```
User types command and presses Enter
        |
        v
TerminalView calls TerminalManager.executeCommand(text)
        |
        v
TerminalManager logs [BDE] Command received: <command>
        |
        v
processCommand()
        |
        +-- built-in (help/clear/version/date/pwd) -> appendOutput(result)
        |
        +-- unknown -> appendOutput("Command execution is not implemented yet.")
        |
        v
appendPrompt()
        |
        v
outputChanged() / lineCountChanged() -> TerminalView updates
```

### Ownership Diagram

```
Application
        |
        +-- SessionManager
        |       +-- ModuleManager
        |             +-- ApplicationManager
        |             |     +-- ApplicationRegistry
        |             |     |     +-- ApplicationInfo ("Terminal")
        |             |     +-- ApplicationLauncher
        |             |     +-- FileManagerApplication
        |             |     +-- SettingsApplication
        |             |     +-- TerminalApplication (set externally)
        |             |     +-- uses WindowManager
        |             |     +-- uses NotificationManager
        |             +-- WindowManager
        |             +-- NotificationModule
        |                   +-- NotificationManager
        +-- FileManagerApplication instance
        +-- SettingsApplication instance
        +-- TerminalApplication instance
              +-- uses WindowManager
              +-- uses NotificationManager

QML
        |
        +-- WindowFrame
              |
              +-- TerminalWindow
                    |
                    +-- TerminalManager
                    |     +-- TerminalSession
                    +-- TerminalToolbar
                    +-- TerminalView
                    +-- TerminalStatusBar
```

        |             |     +-- uses WindowManager
        |             |     +-- uses NotificationManager
        |             +-- WindowManager
        |             |     +-- Window (applicationName)
        |             +-- NotificationModule
        |                   +-- NotificationManager
        +-- FileManagerApplication instance (parented to QML engine)
              +-- uses WindowManager
              +-- uses NotificationManager

QML
        |
        +-- WindowFrame
              |
              +-- FileManagerWindow (when applicationName == "File Manager")
                    |
                    +-- FileSystemModel
                    +-- Toolbar
                    +-- Sidebar
                    +-- FileList
                    +-- StatusBar
              |
              +-- SettingsWindow (when applicationName == "Settings")
                    |
                    +-- SettingsManager
                    +-- NavigationSidebar
                    +-- SettingsContent
                    +-- SettingsPage
```

## Sprint 13 Changes

- Added the first native Settings application.
- Created `SettingsPage` data model (`include/bos/SettingsPage.h`) for page id/title metadata.
- Created `SettingsManager` (`include/bos/SettingsManager.h`, `src/SettingsManager.cpp`) — owns the four settings pages (Appearance, Wallpaper, System, About), exposes the currently selected page, and provides read-only system information (BOS version, Qt version, architecture, session uptime). Placeholder configuration methods (`setTheme`, `setAccentColor`, `setFontSize`, `chooseWallpaper`, `restoreDefaultWallpaper`) log requests but do not change the desktop.
- Created `SettingsApplication` (`include/bos/SettingsApplication.h`, `src/SettingsApplication.cpp`) — requests a managed 900×650 window from `WindowManager` and emits a startup "Settings / Ready." info notification.
- Registered `SettingsManager` as a QML type in `Application.cpp` so each Settings window can instantiate its own independent manager.
- Updated `ApplicationManager` with `setSettingsApplication()`; launching "Settings" now delegates to `SettingsApplication::open()` instead of creating a generic demo window.
- Updated the placeholder "Settings" entry in `ApplicationRegistry` to allow multiple instances (`singleInstance: false`).
- Updated `WindowFrame.qml` to load `SettingsWindow.qml` when `applicationName === "Settings"`.
- Wired `SettingsApplication` with `WindowManager` and `NotificationManager` in `Application.cpp`.
- Created QML components:
  - `qml/SettingsWindow.qml` — root Settings content (sidebar + content area).
  - `qml/NavigationSidebar.qml` — four-page navigation list.
  - `qml/SettingsContent.qml` — page title and content container.
  - `qml/SettingsPage.qml` — bodies for Appearance, Wallpaper, System, and About.
  - Helper components: `qml/SettingsButton.qml`, `qml/InfoRow.qml`.
- Added Sprint 13 logging:
  - `[BDE] Settings window opened (ID: <id>)`
  - `[BDE] Settings page selected: <pageId>`
  - `[BDE] Theme change requested: <theme>`
  - `[BDE] Accent color change requested: <color>`
  - `[BDE] Font size change requested: <size>`
  - `[BDE] Choose wallpaper requested`
  - `[BDE] Restore default wallpaper requested`
- Updated `CMakeLists.txt` and this documentation with new sources, headers, QML files, architecture, and ownership diagrams.
- No forbidden features are implemented: no file picker, theme engine, live wallpaper switching, display settings, networking, user management, or package updates.

### Settings Architecture

```
Launcher
        |
        v
ApplicationManager.launchApplication("Settings")
        |
        v
ApplicationLauncher.canLaunch("Settings")
        |
        v
SettingsApplication.open()
        |
        +-- WindowManager.registerWindow("Settings", 900, 650, x, y, "Settings")
        +-- NotificationManager.createNotification("Settings", "Ready.", "Settings", "info")
        |
        v
WindowManager exposes window with applicationName "Settings"
        |
        v
DesktopSurface Repeater creates WindowFrame
        |
        v
WindowFrame loads SettingsWindow.qml
        |
        v
SettingsWindow creates SettingsManager
        |
        v
NavigationSidebar displays SettingsManager.pages
        |
        v
SettingsPage renders the selected page id
```

### Settings Page Model

```
SettingsManager (QObject)
        |
        +-- pages property: Appearance, Wallpaper, System, About
        |
        +-- currentPage property (read/write)
        |
        +-- bosVersion  -> "0.13.0"
        |
        +-- qtVersion   -> QT_VERSION_STR
        |
        +-- architecture -> QSysInfo::currentCpuArchitecture()
        |
        +-- uptime      -> HH:MM:SS since manager creation
        |
        +-- wallpaperPath
        |
        +-- placeholder setters (log only)
```

### Ownership Diagram

```
Application
        |
        +-- SessionManager
        |       +-- ModuleManager
        |             +-- ApplicationManager
        |             |     +-- ApplicationRegistry
        |             |     |     +-- ApplicationInfo ("Settings")
        |             |     +-- ApplicationLauncher
        |             |     +-- FileManagerApplication
        |             |     +-- SettingsApplication (set externally)
        |             |     +-- uses WindowManager
        |             |     +-- uses NotificationManager
        |             +-- WindowManager
        |             +-- NotificationModule
        |                   +-- NotificationManager
        +-- FileManagerApplication instance
        +-- SettingsApplication instance
              +-- uses WindowManager
              +-- uses NotificationManager

QML
        |
        +-- WindowFrame
              |
              +-- SettingsWindow
                    |
                    +-- SettingsManager
                    +-- NavigationSidebar
                    +-- SettingsContent
                    +-- SettingsPage
```


## Sprint 15 Changes

- Created the Baytevora Design Language (BDL) under `desktop/design/`:
  - `BDL.md` — overview, architecture, and how to use tokens from QML.
  - `Colors.md` — initial BOS palette and semantic/surface color usage.
  - `Typography.md` — font family and type scale.
  - `Spacing.md` — 4 px grid spacing tokens.
  - `Motion.md` — timing and easing standards (documented only).
  - `Icons.md` — icon size constants.
  - `Accessibility.md` — contrast, focus, touch targets, scaling, and motion rules.
  - `Components.md` — standards for buttons, toolbars, sidebars, lists, cards, notifications, windows, dialogs, and application layout.
- Created C++ design-token managers in the shell:
  - `ThemeManager` (`include/bos/ThemeManager.h`, `src/ThemeManager.cpp`) — exposes all BDL colors: primary, accent, background, surface, surface secondary, border, text primary/secondary/disabled, success, warning, error, highlight, selection, plus surface-specific tokens (window, taskbar, launcher, notification backgrounds).
  - `DesignTokens` (`include/bos/DesignTokens.h`, `src/DesignTokens.cpp`) — exposes corner radii: small (6 px), medium (8 px), large (12 px), extra large (16 px).
  - `TypographyManager` (`include/bos/TypographyManager.h`, `src/TypographyManager.cpp`) — exposes font family and sizes: display (32 px), heading (24 px), title (18 px), subtitle (16 px), body (14 px), caption (12 px), small (10 px).
  - `SpacingManager` (`include/bos/SpacingManager.h`, `src/SpacingManager.cpp`) — exposes 4 px grid spacing tokens: 4, 8, 12, 16, 20, 24, 32, 40, 48, 64 px.
  - `IconManager` (`include/bos/IconManager.h`, `src/IconManager.cpp`) — exposes icon size constants: small (16 px), medium (20 px), normal (24 px), large (32 px), extra large (48 px).
- Registered all managers in `Application.cpp` and exposed them as QML context properties: `ThemeManager`, `DesignTokens`, `TypographyManager`, `SpacingManager`, and `IconManager`.
- Began replacing hardcoded constants in existing QML with token references (constants only, no layout redesigns):
  - `qml/Taskbar.qml` — `ThemeManager.taskbarBackground`, `ThemeManager.borderColor`, `SpacingManager.space8`, `SpacingManager.space12`.
  - `qml/NotificationPopup.qml` — severity backgrounds mapped to `ThemeManager` semantic colors, text colors from `ThemeManager`, `DesignTokens.radiusMedium`, `SpacingManager` for margins/spacing, `TypographyManager` for font sizes and family.
  - `qml/NotificationCenter.qml` — `SpacingManager.space20` for margins, `SpacingManager.space12` for spacing.
  - `qml/WindowFrame.qml` — `ThemeManager.windowBackground`, `ThemeManager.borderColor`, `ThemeManager.surfaceSecondaryColor`, `ThemeManager.surfaceColor`, `ThemeManager.backgroundColor`, `ThemeManager.textPrimary`, `SpacingManager` for title bar margins, `TypographyManager` for title font.
  - `qml/Launcher.qml` — `ThemeManager.launcherBackground`, `ThemeManager.borderColor`, `DesignTokens.radiusMedium`, `SpacingManager.space8`/`space16`.
- Updated `CMakeLists.txt` with new sources and headers.
- Updated this README with design docs, new files, and Sprint 15 architecture.
- No forbidden features are implemented: no dark mode, light mode, theme switching, animations, blur, glass, transparency, custom themes, or dynamic colors.

### BDL Architecture

```
Application
        |
        +-- ThemeManager         (colors)
        +-- DesignTokens         (radius)
        +-- TypographyManager    (font sizes, family)
        +-- SpacingManager       (spacing scale)
        +-- IconManager          (icon sizes)
        |
        +-- exposed as QML context properties
                |
                v
        QML components reference tokens:
                ThemeManager.backgroundColor
                ThemeManager.textPrimary
                DesignTokens.radiusMedium
                SpacingManager.space16
                TypographyManager.body
                IconManager.normal
```


## Sprint 16 Changes

- Implemented the first Desktop Model for BOS:
  - `DesktopItem` (`include/bos/DesktopItem.h`, `src/DesktopItem.cpp`) — data object with `id`, `name`, `icon`, `type`, `positionX`, `positionY`, `selected`, and `visible` properties.
  - `DesktopModel` (`include/bos/DesktopModel.h`, `src/DesktopModel.cpp`) — `QAbstractListModel` exposing `name`, `icon`, `type`, `positionX`, `positionY`, `selected`, and `visible` roles. Owns and destroys `DesktopItem` instances.
  - `DesktopManager` (`include/bos/DesktopManager.h`, `src/DesktopManager.cpp`) — owns the `DesktopModel`, registers items, loads the default icon set, and exposes `selectItem()` / `activateItem()` invokables. Emits logs:
    - `[BDE] Desktop initialized`
    - `[BDE] Desktop item registered: <Name>`
    - `[BDE] Desktop item selected: <id>`
    - `[BDE] Desktop item activated: <id>`
  - `DesktopIconsModule` (`include/bos/DesktopIconsModule.h`, `src/DesktopIconsModule.cpp`) — concrete `DesktopModule` that owns the `DesktopManager` and loads defaults during module initialization.
- Registered `DesktopIconsModule` in `SessionManager` and exposed `desktopManager` as a QML context property from `Application.cpp`.
- Registered `DesktopModel` as a QML type (`BOS.Shell 1.0`) so it can be referenced from QML.
- Created QML components:
  - `qml/DesktopIcons.qml` — renders all desktop icons using a `Repeater` bound to `desktopManager.model`. Icons are positioned with the `positionX`/`positionY` roles.
  - `qml/DesktopIcon.qml` — displays a placeholder icon (first letter of the name), the item name, selected highlight, and handles single click (select) and double click (activate). Uses BDL tokens for colors, radius, typography, spacing, and icon sizes.
  - `qml/DesktopSelection.qml` — placeholder component for future selection handling.
- Integrated `DesktopIcons` into `qml/DesktopSurface.qml` between the wallpaper layer and the window layer.
- Added six default desktop entries: Home, Documents, Downloads, Computer, Trash, Settings.
- Updated `CMakeLists.txt` with the new C++ sources, headers, and QML files.
- Updated this README with Sprint 16 files and architecture.
- No forbidden features are implemented: no drag-and-drop, no shortcuts, no filesystem integration, no context menus, no rename/delete/copy/paste, no multi-selection, no grid snapping, no auto-arrange, no wallpaper interaction, and no desktop widgets.

### Desktop Architecture

```
DesktopIconsModule
        |
        +-- DesktopManager
                |
                +-- DesktopModel (QAbstractListModel)
                        |
                        +-- DesktopItem[]
                                |
                                v
                        QML DesktopIcons.qml
                                |
                                +-- DesktopIcon (per item)
```


## Sprint 17 Changes

- Implemented the first global Clipboard Service for Baytevora OS:
  - `ClipboardItem` (`include/bos/ClipboardItem.h`, `src/ClipboardItem.cpp`) — plain-text clipboard entry with `id`, `text`, `type`, and `timestamp` properties.
  - `ClipboardManager` (`include/bos/ClipboardManager.h`, `src/ClipboardManager.cpp`) — central manager that wraps `QClipboard`, exposes `hasContent`, `text`, `type`, and `timestamp` to QML, and provides `copyText()`, `pasteText()`, and `clearClipboard()` invokables. Logs:
    - `[BDE] Clipboard initialized`
    - `[BDE] Clipboard updated`
    - `[BDE] Clipboard cleared`
  - `ClipboardModule` (`include/bos/ClipboardModule.h`, `src/ClipboardModule.cpp`) — concrete `DesktopModule` that owns the `ClipboardManager`, initializes it during module startup, and shuts it down cleanly.
- Registered `ClipboardModule` in `SessionManager` and exposed `clipboardManager` as a QML context property from `Application.cpp`.
- Wired the `NotificationManager` into `ClipboardModule` so a manual `clearClipboard()` call creates an information notification: "Clipboard cleared".
- Terminal integration: added **Copy** and **Paste** buttons to `qml/TerminalView.qml`. Copy copies the current command-line text into the clipboard; Paste inserts the clipboard text into the command input. Only plain text is supported.
- File Manager integration: added single-click selection highlight in `qml/FileList.qml` and a **Copy Filename** button in `qml/Toolbar.qml`. Clicking it copies the selected filename (metadata only) to the clipboard. No file copy operation is performed.
- Settings integration: added a **Clipboard** settings page under System (`qml/SettingsPage.qml`). It displays read-only values:
  - Clipboard Available (Yes/No)
  - Current Content Length
  - A "Clear Clipboard" button that triggers the manual-clear notification.
- Updated `CMakeLists.txt` with the new C++ sources and headers.
- Updated this README with Sprint 17 files, architecture, and integration details.
- No forbidden features are implemented: no clipboard history, synchronization, image/file/HTML clipboard, drag-and-drop, file copy/paste, cloud clipboard, encryption, search, favorites, pinning, or persistence after reboot.

### Clipboard Architecture

```
ClipboardModule
        |
        +-- ClipboardManager
                |
                +-- QClipboard (QGuiApplication)
                        |
                        v
            QML: TerminalView (copy/paste)
            QML: FileManagerWindow (copy filename)
            QML: SettingsPage (status + clear)
```


## Sprint 18 Changes

- Implemented the first global Keyboard Shortcut Manager for Baytevora OS:
  - `ShortcutContext` (`include/bos/ShortcutContext.h`) — enum with `Global`, `Application`, and `Window` contexts, exposed to QML.
  - `Shortcut` (`include/bos/Shortcut.h`, `src/Shortcut.cpp`) — data model for one shortcut, owning the native `QShortcut` object and supporting enable/disable.
  - `ShortcutManager` (`include/bos/ShortcutManager.h`, `src/ShortcutManager.cpp`) — central manager with `registerShortcut()`, `removeShortcut()`, `enableShortcut()`, `disableShortcut()`, `isRegistered()`, and `registeredShortcuts()`. Detects duplicates, rejects them with `[BDE] Duplicate shortcut rejected`, and emits `shortcutActivated`, `shortcutRegistered`, `shortcutRemoved`. Logs:
    - `[BDE] Shortcut manager initialized`
    - `[BDE] Shortcut registered: <name>`
    - `[BDE] Shortcut activated: <id>`
    - `[BDE] Shortcut removed`
  - `ShortcutModule` (`include/bos/ShortcutModule.h`, `src/ShortcutModule.cpp`) — `DesktopModule` subclass that creates a hidden `QWidget` parent for `QShortcut` objects and owns the `ShortcutManager`.
- Switched the application from `QGuiApplication` to `QApplication` in `src/main.cpp` and linked `Qt6::Widgets` in `CMakeLists.txt` so `QShortcut` has the required widgets runtime.
- Registered `ShortcutModule` in `SessionManager` and exposed `shortcutManager` as a QML context property from `Application.cpp`. Registered `ShortcutContext` as a QML enum so integrations can use `ShortcutContext.Global` / `.Application` / `.Window`.
- Application integrations:
  - **Terminal** (`qml/TerminalView.qml`): registers `Ctrl+C` (copy input), `Ctrl+V` (paste), `Ctrl+L` (clear output), and `Ctrl+A` (select all). Added `TerminalManager::clearOutput()` in `src/TerminalManager.cpp` to support `Ctrl+L`.
  - **File Manager** (`qml/FileManagerWindow.qml`, `qml/FileList.qml`, `qml/Toolbar.qml`): registers `Ctrl+C` to copy the first selected filename and `Ctrl+A` to select all visible entries. File list selection now uses a `selectedFileNames` array so multiple rows can be highlighted.
  - **Launcher** (`qml/Launcher.qml`): registers `Escape` to close the launcher.
  - **Notification Center** (`qml/NotificationCenter.qml`): registers `Escape` to clear all notifications.
  - **Desktop** (`qml/DesktopSurface.qml`): registers `Delete` and logs `[BDE] Desktop delete requested`.
- Settings integration: added a **Shortcuts** page under System (`qml/SettingsPage.qml`, `src/SettingsManager.cpp`) that displays:
  - Shortcut Subsystem status (Active/Inactive)
  - Total shortcut count
  - A read-only list of registered shortcuts with name and key sequence.
- Updated `CMakeLists.txt` with the new C++ sources/headers and `Qt6::Widgets`.
- Updated this README with Sprint 18 files, architecture, and integration details.
- No forbidden features are implemented: no shortcut customization, editor, Alt+Tab, Alt+F4, Print Screen, media/function-key remapping, macros, recording, profiles, game mode, or accessibility remapping.

### Shortcut Architecture

```
ShortcutModule
        |
        +-- ShortcutManager
                |
                +-- QWidget (hidden shortcut host)
                        |
                        +-- QShortcut[]
                                |
                                v
            QML: TerminalView (Ctrl+C/V/L/A)
            QML: FileManagerWindow (Ctrl+C/A)
            QML: Launcher (Escape)
            QML: NotificationCenter (Escape)
            QML: DesktopSurface (Delete)
```


## Sprint 19 Changes

- Implemented the first version of the Baytevora Search Service (BSS):
  - `SearchCategory` (`include/bos/SearchCategory.h`) — enum with `Application`, `Setting`, `Desktop`, and `Command`, exposed to QML as `SearchCategory`.
  - `SearchItem` (`include/bos/SearchItem.h`, `src/SearchItem.cpp`) — plain value object with `id`, `title`, `subtitle`, `category`, `keywords`, `iconName`, `provider`, and `enabled`. Converted to a `QVariantMap` for QML consumption.
  - `SearchProvider` (`include/bos/SearchProvider.h`) — abstract C++ interface with `providerName()`, `registerItems()`, `unregisterItems()`, and `refresh()`.
  - `SearchManager` (`include/bos/SearchManager.h`, `src/SearchManager.cpp`) — central manager that registers providers, indexes items once, performs case-insensitive searches, orders results by priority (exact title, starts with, contains, keywords, subtitle), exposes `results` to QML, detects duplicate item IDs, and logs:
    - `[BDE] Search manager initialized`
    - `[BDE] Search provider registered: <name>`
    - `[BDE] Indexed items: <count>`
    - `[BDE] Search: <query>`
    - `[BDE] Results: <count>`
    - `[BDE] Duplicate search item rejected`
  - `SearchModule` (`include/bos/SearchModule.h`, `src/SearchModule.cpp`) — `DesktopModule` subclass that owns the `SearchManager` and registers the three built-in providers.
- Built-in providers:
  - `ApplicationSearchProvider` — File Manager, Terminal, Settings, Browser, Calculator, Notes.
  - `DesktopSearchProvider` — Home, Documents, Downloads, Computer, Trash, Settings.
  - `SettingsSearchProvider` — Appearance, Wallpaper, System, About, Shortcuts, Search.
- Registered `SearchModule` in `SessionManager` and exposed `searchManager` and `settingsApplication` as QML context properties from `Application.cpp`.
- Enhanced `SettingsApplication` (`include/bos/SettingsApplication.h`, `src/SettingsApplication.cpp`) with a `pendingPage` property and `openPage(pageId)` invokable so search results can request a specific Settings page.
- Updated `SettingsWindow.qml` to read `settingsApplication.pendingPage` on completion and set the `SettingsManager.currentPage` accordingly.
- Launcher integration:
  - Added `SearchField.qml`, `SearchResults.qml`, and `SearchResultItem.qml`.
  - Updated `Launcher.qml` to show the search field below the header. When the field is empty, the normal application grid is shown; when text exists, search results are shown.
  - Selecting a result launches the application (for `Application`), opens Settings to the requested page (for `Setting`), or logs `[BDE] Desktop item selected: <title>` (for `Desktop`).
- Settings integration: added a **Search** page (`qml/SettingsPage.qml`, `src/SettingsManager.cpp`) that shows subsystem status, provider count, indexed item count, and current result count.
- Updated `CMakeLists.txt` (Sprint 19, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no file content indexing, recursive filesystem search, internet search, AI search, voice search, search history, recent searches, ranking learning, fuzzy matching, search suggestions, search filters, or plugins.

### Search Architecture

```
SearchModule
        |

## Sprint 20 Changes

- Implemented the first version of the Baytevora Power Management Service (BPS):
  - `PowerActionType` (`include/bos/PowerActionType.h`, `src/PowerActionType.cpp`) — enum with `Shutdown`, `Restart`, `LogOut`, `Lock`, `Sleep`, and `Hibernate`, exposed to QML as `PowerActionType`.
  - `PowerAction` (`include/bos/PowerAction.h`, `src/PowerAction.cpp`) — plain value object with `id`, `title`, `description`, `type`, `enabled`, and `iconName`. Converted to a `QVariantMap` for QML.
  - `PowerManager` (`include/bos/PowerManager.h`, `src/PowerManager.cpp`) — central manager that owns the default power actions, exposes `actions`, handles `executeAction(type)`, reports availability, emits `actionExecuted(type)` and `actionsChanged`, and creates information notifications via `NotificationManager` while logging `[BDE] <Action> requested`.
  - `PowerModule` (`include/bos/PowerModule.h`, `src/PowerModule.cpp`) — `DesktopModule` subclass that owns the `PowerManager`.
- Registered `PowerModule` in `SessionManager` and exposed `powerManager` as a QML context property from `Application.cpp`. The `PowerActionType` enum is also registered for QML use.
- Wired `NotificationManager` into `PowerManager` in `Application.cpp` so every action request produces an information notification.
- Default actions: Shutdown, Restart, Log Out, Lock, Sleep, Hibernate. All are placeholders; no hardware or session state is changed.
- Taskbar integration:
  - Added `PowerMenu.qml` and `PowerMenuItem.qml`.
  - Added a **P** power button to the far right of `Taskbar.qml`; clicking toggles the menu.
  - `PowerMenu` is anchored above the power button and lists all actions. Selecting an item calls `powerManager.executeAction(type)`.
  - Escape closes the menu (`Keys.onEscapePressed`).
  - Clicking outside the menu closes it via a taskbar overlay and a desktop surface overlay in `Desktop.qml`.
- Settings integration: added a **Power** page (`qml/SettingsPage.qml`, `src/SettingsManager.cpp`) showing subsystem status, registered action count, and session uptime.
- Updated `CMakeLists.txt` (Sprint 20, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no real shutdown, reboot, logout, lock, battery monitoring, brightness, power profiles, suspend, hibernate, ACPI, hardware APIs, CPU frequency, fan control, or thermal monitoring.

### Power Architecture

```
PowerModule
        |
        +-- PowerManager
                |
                +-- PowerAction[]
                        |
                        v
            Taskbar (PowerMenu)
            Settings (Power page)
```

        +-- SearchManager
                |
                +-- ApplicationSearchProvider
                +-- DesktopSearchProvider
                +-- SettingsSearchProvider
                        |
                        +-- SearchItems[]
                                |
                                v
            Launcher (SearchField + SearchResults)
            Settings (Search page)
```
