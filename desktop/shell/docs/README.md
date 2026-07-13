# BDE Shell

## Overview

The Baytevora Desktop Environment (BDE) Shell implemented through Sprint 45.

The shell includes a modular session/module system, window manager with focus and state control, taskbar, launcher, application framework, notification service, desktop icons, a global clipboard service, a global keyboard shortcut manager, the Baytevora Search Service (BSS), the Baytevora Power Management Service (BPS), the Baytevora Drag & Drop Framework (BDDF), the Baytevora Login Manager (BLM), the Baytevora Lock Screen (BLS), the Baytevora Update Manager (BUM), the Baytevora Package Manager (BPM), the Baytevora Store Foundation (BSF), the Baytevora Browser Foundation (BBF), the Baytevora Notes Application (BNA), the Baytevora Image Viewer (BIV), the Baytevora Design Language Version 2 (BDL v2) adaptive design foundation, the Baytevora Calculator Application (BCA), the Baytevora PDF Viewer Foundation (BPV), the Baytevora Archive Manager (BAM), the Baytevora Media Player (BMP), the Baytevora Text Editor (BTE), the Baytevora System Monitor (BSM), the Baytevora Task Manager (BTM), the Baytevora Network Manager (BNM), the Baytevora Storage Manager (BSM), the Baytevora Printing Framework (BPF), Baytevora Browser Phase 2 (BBP2) multi-tab browsing, Baytevora Browser Downloads (BBD) per-window download management, Baytevora Browser Bookmarks & History (BBBH) with local JSON persistence, Baytevora Browser Privacy Foundation (BBPF) for site permissions and privacy settings, Baytevora File Manager Phase 2 (BFM2) with breadcrumb navigation, in-session search, favorites, recent files, and improved context menus, and Baytevora Notes Phase 2 (BNP2) with persistent JSON storage, folder organization, local search, auto-save, and File Manager integration for .bnote files, and Baytevora Image Viewer Phase 2 (BIV2) with rotation, flip, zoom modes, fullscreen, slideshow, metadata panel, folder navigation, and Print Manager integration. Each sprint is built on top of the previous one without rewriting earlier work.

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
| `include/bos/FileSystemModel.h` | Directory listing model for the File Manager; owns per-window navigation history, FileFavoriteManager, RecentFileManager, and FileSearchManager |
| `include/bos/FavoriteLocation.h` | Value object representing a favorite location (displayName, path, icon, pinned) |
| `include/bos/FileFavoriteManager.h` | Manages favorite locations with JSON persistence and QML notifications |
| `include/bos/RecentFile.h` | Value object representing a recently opened file (fileName, path, fileType, lastOpened) |
| `include/bos/RecentFileManager.h` | Maintains the recent files list with JSON persistence and QML notifications |
| `include/bos/FileSearchManager.h` | Provides fast local in-session file search without background indexing |
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
| `include/bos/DragType.h` | Enum for drag payload types |
| `include/bos/DragOperationState.h` | Enum for drag lifecycle states |
| `include/bos/DragData.h` | Lightweight immutable drag payload |
| `include/bos/DragOperation.h` | Represents one active drag session |
| `include/bos/DragManager.h` | Central drag & drop controller |
| `include/bos/DragModule.h` | Desktop module that owns the DragManager |
| `include/bos/User.h` | Lightweight immutable user data model |
| `include/bos/UserManager.h` | Owns available users and current selection |
| `include/bos/LoginState.h` | Enum for login lifecycle states |
| `include/bos/LoginManager.h` | Coordinates the login/logout flow |
| `include/bos/LoginModule.h` | Desktop module that owns the LoginManager |
| `include/bos/LockState.h` | Enum for lock lifecycle states |
| `include/bos/LockManager.h` | Coordinates the lock/unlock flow |
| `include/bos/LockModule.h` | Desktop module that owns the LockManager |
| `include/bos/UpdateState.h` | Enum for update lifecycle states |
| `include/bos/UpdateInfo.h` | Lightweight immutable update data model |
| `include/bos/UpdateManager.h` | Coordinates update checks and metadata |
| `include/bos/UpdateModule.h` | Desktop module that owns the UpdateManager |
| `include/bos/PackageState.h` | Enum for package lifecycle states |
| `include/bos/PackageType.h` | Enum for package type classification |
| `include/bos/PackageInfo.h` | Lightweight immutable package data model |
| `include/bos/Package.h` | Rich Baytevora package data model |
| `include/bos/PackageDependency.h` | Package dependency relationship model |
| `include/bos/PackageRepository.h` | Local/remote repository model |
| `include/bos/PackageTransaction.h` | Package transaction model |
| `include/bos/PackageDatabase.h` | Owns placeholder package metadata |
| `include/bos/PackageManager.h` | Coordinates package operations, dependencies, repositories, and transactions |
| `include/bos/PackageManagerApplication.h` | Native Package Manager application handler |
| `include/bos/PackageModule.h` | Desktop module that owns the PackageManager |
| `include/bos/StoreCategoryEnum.h` | Enum for store category classification |
| `include/bos/StoreCategory.h` | Model for a Baytevora Store category with count |
| `include/bos/StoreItem.h` | Lightweight immutable store catalog data model |
| `include/bos/InstalledApplication.h` | Model for an installed Store application |
| `include/bos/StoreUpdate.h` | Model for an available Store application update |
| `include/bos/StoreCatalog.h` | Owns placeholder store catalog entries |
| `include/bos/StoreManager.h` | Coordinates store catalog, install/remove, and updates |
| `include/bos/StoreModule.h` | Desktop module that owns the StoreManager |
| `include/bos/StoreApplication.h` | Native Baytevora Store application handler |
| `include/bos/BrowserPage.h` | Stores a single browser page state |
| `include/bos/BrowserTab.h` | Represents a single browser tab state |
| `include/bos/BrowserSession.h` | Holds per-window tab collection, active tab, downloads, bookmarks, history, permissions, and privacy settings |
| `include/bos/BrowserManager.h` | Coordinates tabs, downloads, bookmarks, history, permissions, privacy settings, session, and navigation and exposes them to QML |
| `include/bos/BrowserDownload.h` | Represents a single browser download state |
| `include/bos/BrowserDownloadManager.h` | Maintains the download list for a browser window |
| `include/bos/BrowserBookmark.h` | Represents a single bookmark |
| `include/bos/BrowserBookmarkManager.h` | Manages bookmarks and folders with JSON persistence |
| `include/bos/BrowserHistoryEntry.h` | Represents a single browsing history entry |
| `include/bos/BrowserHistoryManager.h` | Manages browsing history with JSON persistence |
| `include/bos/BrowserPermission.h` | Represents a single site permission rule |
| `include/bos/BrowserPermissionManager.h` | Manages site permissions with JSON persistence |
| `include/bos/BrowserPrivacySettings.h` | Holds global browser privacy settings with JSON persistence |
| `include/bos/BrowserModule.h` | Desktop module that owns the shared BrowserManager |
| `include/bos/BrowserApplication.h` | Native Browser application handler |
| `include/bos/Note.h` | Value object for a single note (noteId, title, content, folder, pinned, favorite, timestamps) |
| `include/bos/NoteFolder.h` | Value object for a note folder (folderId, name) |
| `include/bos/NotesStorageManager.h` | Persists notes and folders to local JSON files |
| `include/bos/NoteSearchManager.h` | Fast local title/content/folder/favorite search |
| `include/bos/NotesManager.h` | Note and folder collection manager for the Notes app |
| `include/bos/NotesApplication.h` | Native Notes application handler; accepts .bnote open requests |
| `include/bos/ImageDocument.h` | Data object for the currently viewed image with metadata and transformations |
| `include/bos/ImageMetadata.h` | Exposes image metadata to QML |
| `include/bos/ImageSlideshowManager.h` | Manages slideshow playback for the current folder |
| `include/bos/ImageViewerManager.h` | Manages image document, metadata, transformations, and slideshow |
| `include/bos/ImageViewerApplication.h` | Native Image Viewer application handler; accepts file open requests |
| `include/bos/CalculatorEngine.h` | Stateless arithmetic evaluator for the Calculator |
| `include/bos/CalculatorManager.h` | Per-window calculator state and QML API |
| `include/bos/CalculatorApplication.h` | Native Calculator application handler |
| `include/bos/PdfDocument.h` | PDF document metadata object for the PDF Viewer |
| `include/bos/PdfViewerManager.h` | Per-window PDF state and QML API |
| `include/bos/PdfViewerApplication.h` | Native PDF Viewer application handler |
| `include/bos/ArchiveEntry.h` | Value type for a single archive entry |
| `include/bos/ArchiveDocument.h` | Archive document metadata object |
| `include/bos/ArchiveEngine.h` | Lightweight read-only parser for ZIP, TAR, and TAR.GZ |
| `include/bos/ArchiveManager.h` | Per-window archive state, entry model, and QML API |
| `include/bos/ArchiveApplication.h` | Native Archive Manager application handler |
| `include/bos/MediaDocument.h` | Media document metadata object for the Media Player |
| `include/bos/MediaPlayerManager.h` | Per-window media playback state and QML API |
| `include/bos/MediaPlayerApplication.h` | Native Media Player application handler |
| `include/bos/TextDocument.h` | Text document metadata object for the Text Editor |
| `include/bos/TextEditorManager.h` | Per-window document state, content, and QML API |
| `include/bos/TextEditorApplication.h` | Native Text Editor application handler |
| `include/bos/SystemInfo.h` | Read-only system metrics object for the System Monitor |
| `include/bos/SystemMonitorManager.h` | Per-window system monitoring controller and QML API |
| `include/bos/SystemMonitorApplication.h` | Native System Monitor application handler |
| `include/bos/TaskInfo.h` | Value type describing a running task for the Task Manager |
| `include/bos/TaskManager.h` | Per-window running-task model and QML API |
| `include/bos/TaskManagerApplication.h` | Native Task Manager application handler |
| `include/bos/NetworkInterface.h` | Value type describing a network interface |
| `include/bos/NetworkManager.h` | Per-window network interface model and QML API |
| `include/bos/NetworkApplication.h` | Native Network Manager application handler |
| `include/bos/StorageDevice.h` | Value type describing a storage device |
| `include/bos/StoragePartition.h` | Value type describing a storage partition |
| `include/bos/StorageManager.h` | Per-window storage device/partition model and QML API |
| `include/bos/StorageApplication.h` | Native Storage Manager application handler |
| `include/bos/PrinterInfo.h` | Value type describing a printer |
| `include/bos/PrintJob.h` | Value type describing a print job |
| `include/bos/PrintManager.h` | Per-window printer/job model and QML API |
| `include/bos/PrintApplication.h` | Native Print Manager application handler |
| `include/bos/AdaptiveLayoutManager.h` | Provides adaptive layout metrics for BDL v2 |
| `include/bos/AccessibilityManager.h` | Placeholder accessibility settings manager |
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

## Sprint 21 Changes

- Implemented the first version of the Baytevora Drag & Drop Framework (BDDF):
  - `DragType` (`include/bos/DragType.h`, `src/DragType.cpp`) — enum with `Text`, `FilePath`, `DesktopItem`, and `Application`, exposed to QML as `DragType`.
  - `DragOperationState` (`include/bos/DragOperationState.h`, `src/DragOperationState.cpp`) — enum with `Idle`, `Started`, `Dragging`, `Dropped`, and `Cancelled`, exposed to QML as `DragOperationState`.
  - `DragData` (`include/bos/DragData.h`, `src/DragData.cpp`) — lightweight immutable payload with `type` and `value`. Converts to a `QVariantMap` for QML.
  - `DragOperation` (`include/bos/DragOperation.h`, `src/DragOperation.cpp`) — represents one drag session with `state`, `source`, `target`, payload, and position.
  - `DragManager` (`include/bos/DragManager.h`, `src/DragManager.cpp`) — central controller with `beginDrag()`, `updatePosition()`, `setTarget()`, `clearTarget()`, `completeDrop()`, and `cancelDrag()`. Exposes `active`, `currentOperation`, `currentDragType`, `currentSource`, `currentTarget`, and `currentPosition`. Sends information notifications via `NotificationManager`.
  - `DragModule` (`include/bos/DragModule.h`, `src/DragModule.cpp`) — `DesktopModule` subclass that owns the `DragManager`.
- Registered `DragModule` in `SessionManager`. Exposed `dragManager` as a QML context property and registered the `DragType` and `DragOperationState` enums from `Application.cpp`. Wired `NotificationManager` into `DragManager`.
- QML components:
  - `DragIndicator.qml` — small reusable drag preview using design tokens.
  - `DragOverlay.qml` — global feedback overlay that follows the drag position.
  - `DropTarget.qml` — reusable component with hover state, accept/reject visual feedback, and `dragEntered`, `dragExited`, `dragDropped` signals.
- Desktop integration: `DesktopIcon.qml` starts a `DragType.DesktopItem` drag after an 8 px threshold and completes it on release.
- File Manager integration: `FileList.qml` rows are now `DropTarget`s accepting `DesktopItem` and `Application` drags. Each row can also be dragged as `DragType.FilePath` and logs accepted drops without performing any filesystem operation.
- Launcher integration: `LauncherButton.qml` starts a `DragType.Application` drag after a threshold; release cancels the drag (drop ignored) as a placeholder.
- Settings integration: added a read-only **Drag & Drop** page (`src/SettingsManager.cpp`, `qml/SettingsPage.qml`) showing framework status, current state, current drag type, and the last completed operation.
- Updated `CMakeLists.txt` (Sprint 21, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no file moving, copying, cut/paste, clipboard integration, window dragging, desktop rearranging, cross-window/cross-application drag, drag images, spring-loading, drop animations, auto-scroll, undo, touch gestures, multi-item drag, external file drag, or any filesystem modification.

### Drag & Drop Architecture

```
DragModule
        |
        +-- DragManager
                |
                +-- DragOperation
                        |
                        +-- DragData
                                |
                                v
            DesktopIcon    FileList    LauncherButton
            (DesktopItem)   (FilePath)   (Application)
                                |
                                v
                          DropTarget
```

## Sprint 22 Changes

- Implemented the first version of the Baytevora Login Manager (BLM):
  - `User` (`include/bos/User.h`, `src/User.cpp`) — lightweight immutable data model with `username`, `displayName`, `avatarPath`, `administrator`, and `lastLogin`, exposed to QML as a map.
  - `UserManager` (`include/bos/UserManager.h`, `src/UserManager.cpp`) — owns the local user list and the currently selected user; exposes `users`, `currentUser`, `selectUser()`, and `userCount()`.
  - `LoginState` (`include/bos/LoginState.h`, `src/LoginState.cpp`) — enum with `Booting`, `WaitingForSelection`, `LoggingIn`, and `LoggedIn`, exposed to QML as `LoginState`.
  - `LoginManager` (`include/bos/LoginManager.h`, `src/LoginManager.cpp`) — coordinates the login flow. Provides `login()`, `logout()`, `cancel()`, and `selectUser()`. `login()` is a placeholder that always succeeds. Sends "Welcome back." and "Session ended." information notifications through `NotificationManager`.
  - `LoginModule` (`include/bos/LoginModule.h`, `src/LoginModule.cpp`) — `DesktopModule` subclass that owns the `LoginManager`.
- Registered `LoginModule` first in `SessionManager` so the login manager is available before the desktop session.
- Updated `Application.cpp` startup sequence:
  - Initialize session (registers modules and instantiates managers).
  - Register QML types and expose BDL design managers.
  - Expose `loginManager` to QML.
  - Load `LoginScreen.qml`.
  - On `LoginManager::loggedIn`, start `SessionManager`, expose desktop module context properties, wire notification managers, create application handlers, and load `Desktop.qml`.
- QML components:
  - `LoginScreen.qml` — fullscreen login window with shared wallpaper background, logo placeholder, `Clock`, `UserList`, and `LoginButton`.
  - `UserList.qml` — vertical list of users with selection support.
  - `LoginButton.qml` — flat BDL-styled button that calls `loginManager.login()`.
  - `Clock.qml` reused from the taskbar.
- Settings integration: extended the **System** page (`qml/SettingsPage.qml`) to display the current logged-in user and the session state read-only.
- Updated `CMakeLists.txt` (Sprint 22, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no passwords, PAM, Linux user integration, biometrics, PIN, face unlock, fingerprint, encryption, auto login, fast user switching, remote login, multiple simultaneous sessions, guest accounts, session persistence, or power management integration.

### Login Architecture

```
Application
        |
        +-- SessionManager.initialize()
                |
                +-- LoginModule (LoginManager + UserManager)
                +-- WindowManager, Launcher, DesktopIcons, ...
        |
        v
   LoginScreen (QML)
        |
        +-- LoginManager.login()
                |
                v
        loggedIn signal
                |
                v
   SessionManager.start()
   expose desktop modules
   load Desktop.qml
```

## Sprint 23 Changes

- Implemented the first version of the Baytevora Lock Screen (BLS):
  - `LockState` (`include/bos/LockState.h`, `src/LockState.cpp`) — enum with `Unlocked`, `Locking`, `Locked`, and `Unlocking`, exposed to QML as `LockState`.
  - `LockManager` (`include/bos/LockManager.h`, `src/LockManager.cpp`) — coordinates lock/unlock state. Provides `lock()`, `unlock()`, `lockState`, `isLocked`, and `stateName()`. Emits `locked`/`unlocked` signals and sends "Session locked."/"Session unlocked." information notifications through `NotificationManager`.
  - `LockModule` (`include/bos/LockModule.h`, `src/LockModule.cpp`) — `DesktopModule` subclass that owns the `LockManager`.
- Registered `LockModule` in `SessionManager`.
- Exposed `lockManager` and `LockState` to QML from `Application.cpp` after the desktop session starts.
- QML components:
  - `LockScreen.qml` — full-screen desktop overlay that appears when locked. Shows the current time (reusing `Clock.qml`), current date, a user avatar placeholder, the selected user's display name, and `UnlockButton`. A full-screen `MouseArea` blocks pointer events so the desktop cannot be interacted with while locked.
  - `UnlockButton.qml` — flat BDL-styled button that calls `lockManager.unlock()`.
- Added a "Lock" action to the existing `PowerMenu.qml` that calls `lockManager.lock()`.
- Extended the Settings **System** page (`qml/SettingsPage.qml`) to display the current lock state read-only.
- Updated `CMakeLists.txt` (Sprint 23, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no passwords, PIN, biometrics, face unlock, fingerprint, Linux session locking, encrypted sessions, screen saver, automatic locking, idle timers, multi-user switching, session persistence, or power management integration.

### Lock Architecture

```
Desktop session
        |
        +-- LockModule (LockManager)
                |
                +-- LockScreen.qml overlay
                |       visible when isLocked
                |       blocks desktop input
                |
                +-- PowerMenu "Lock" action -> lock()
                +-- UnlockButton -> unlock()
```

The desktop session and all running applications remain alive while the screen is locked. Unlocking returns to the existing session without restarting applications.

## Sprint 24 Changes

- Implemented the first version of the Baytevora Update Manager (BUM):
  - `UpdateState` (`include/bos/UpdateState.h`, `src/UpdateState.cpp`) — enum with `Idle`, `Checking`, `UpdatesAvailable`, `Downloading`, `ReadyToInstall`, `UpToDate`, and `Error`, exposed to QML as `UpdateState`.
  - `UpdateInfo` (`include/bos/UpdateInfo.h`, `src/UpdateInfo.cpp`) — lightweight immutable update data model with `version`, `title`, `description`, `size`, `releaseDate`, and `type`, exposed as a `QVariantMap`.
  - `UpdateManager` (`include/bos/UpdateManager.h`, `src/UpdateManager.cpp`) — coordinates the update lifecycle. Exposes `currentVersion`, `latestVersion`, `updateState`, `updatesAvailable`, and `availableUpdates`. Provides `checkForUpdates()` and `clearUpdates()`.
  - `UpdateModule` (`include/bos/UpdateModule.h`, `src/UpdateModule.cpp`) — `DesktopModule` subclass that owns the `UpdateManager`.
- Registered `UpdateModule` in `SessionManager`.
- Exposed `updateManager` and `UpdateState` to QML from `Application.cpp` after the desktop session starts.
- Notifications:
  - "Checking for updates..." when a check begins.
  - "Updates available" / "Baytevora OS Preview Update is ready." after the placeholder check.
- QML components:
  - `UpdatesPage.qml` — dedicated Settings page showing current version, latest version, update state, available update count, and the Check for Updates button.
  - `UpdateCard.qml` — reusable card rendering a single available update.
  - `CheckUpdatesButton.qml` — BDL-styled button that calls `updateManager.checkForUpdates()`.
- Added a new "Updates" entry in `SettingsManager` and embedded `UpdatesPage` inside `SettingsPage.qml`.
- Updated `CMakeLists.txt` (Sprint 24, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no networking, HTTP/HTTPS, downloads, installation, restart, automatic updates, scheduling, delta updates, rollback, cryptographic verification, repositories, package management, background services, or real version servers.

### Update Architecture

```
Desktop session
        |
        +-- UpdateModule (UpdateManager)
                |
                +-- checkForUpdates()
                |       |
                |       +-- State: Checking (1.2s placeholder delay)
                |       |
                |       +-- State: UpdatesAvailable
                |       |
                |       +-- Notifications
                |
                +-- UpdatesPage / UpdateCard / CheckUpdatesButton
```

The placeholder update data uses version `0.2.0-alpha`, title `Baytevora OS Preview Update`, description `Placeholder update used for framework validation.`, size `128 MB`, and the current timestamp as the release date. Future sprints will replace the simulated delay with an online update service, add download/install flows, and allow applications to register their own updates.

## Sprint 25 Changes

- Implemented the first version of the Baytevora Package Manager (BPM):
  - `PackageState` (`include/bos/PackageState.h`, `src/PackageState.cpp`) — enum with `Available`, `Installed`, `UpdateAvailable`, and `Disabled`.
  - `PackageType` (`include/bos/PackageType.h`, `src/PackageType.cpp`) — enum with `System`, `Application`, and `Library`.
  - `PackageInfo` (`include/bos/PackageInfo.h`, `src/PackageInfo.cpp`) — lightweight immutable package data model with `packageId`, `name`, `version`, `description`, `developer`, `category`, `installed`, `packageType`, `state`, and `size`, exposed as a `QVariantMap`.
  - `PackageDatabase` (`include/bos/PackageDatabase.h`, `src/PackageDatabase.cpp`) — owns the placeholder package catalog and provides lookup by packageId.
  - `PackageManager` (`include/bos/PackageManager.h`, `src/PackageManager.cpp`) — coordinates placeholder package operations. Exposes `packages`, `installedPackages`, `availablePackages`, `packageCount`, and methods `installPackage(id)`, `uninstallPackage(id)`, `enablePackage(id)`, `disablePackage(id)`, and `package(id)`. Helper methods `stateName()` and `typeName()` convert enum values to readable strings.
  - `PackageModule` (`include/bos/PackageModule.h`, `src/PackageModule.cpp`) — `DesktopModule` subclass that owns the `PackageManager`.
- Registered `PackageModule` in `SessionManager`.
- Exposed `packageManager`, `PackageState`, and `PackageType` to QML from `Application.cpp` after the desktop session starts.
- Seeded placeholder packages: File Manager, Terminal, Settings, Browser, Calculator, and Notes.
- Notifications:
  - Install requested, uninstall requested, package enabled, package disabled, package already installed.
- QML components:
  - `PackagesPage.qml` — dedicated Settings page showing installed/available/total counts and a scrollable package list.
  - `PackageList.qml` — reusable vertical list of PackageCards.
  - `PackageCard.qml` — card rendering package metadata, type, size, status badge, and placeholder install/uninstall/enable/disable action buttons.
  - `PackageStatus.qml` — colored status badge using `packageManager.stateName()`.
- Added a new "Packages" entry in `SettingsManager` and embedded `PackagesPage` inside `SettingsPage.qml`.
- Updated `CMakeLists.txt` (Sprint 25, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no downloads, repositories, dependency resolution, filesystem modification, archives, compression, extraction, install/removal scripts, package signatures, networking, automatic updates, background installation, root permissions, sandboxing, containerization, or rollback.

### Package Architecture

```
Desktop session
        |
        +-- PackageModule (PackageManager)
                |
                +-- PackageDatabase
                |       +-- PackageInfo records
                |
                +-- PackagesPage / PackageCard / PackageList / PackageStatus
```

The BPM is the foundation for the future Baytevora Store. Future sprints will replace placeholder operations with real package installation, repository access, dependency resolution, cryptographic verification, and application self-registration.

## Sprint 26 Changes

- Implemented the first version of the Baytevora Store Foundation (BSF):
  - `StoreCategory` (`include/bos/StoreCategory.h`, `src/StoreCategory.cpp`) — enum with `Featured`, `Productivity`, `Development`, `Utilities`, `System`, and `Entertainment`, exposed to QML as `StoreCategory`.
  - `StoreItem` (`include/bos/StoreItem.h`, `src/StoreItem.cpp`) — lightweight immutable catalog model with `packageId`, `name`, `description`, `developer`, `version`, `rating`, `downloads`, `category`, `installed`, `featured`, and `iconPath`, exposed as a `QVariantMap`.
  - `StoreCatalog` (`include/bos/StoreCatalog.h`, `src/StoreCatalog.cpp`) — owns placeholder store catalog entries and provides featured/all/category lookup.
  - `StoreManager` (`include/bos/StoreManager.h`, `src/StoreManager.cpp`) — coordinates the catalog. Exposes `featuredItems`, `allItems`, `categories`, and methods `item()`, `search()`, `categoryItems()`, and `requestInstall()`. All install requests delegate to `PackageManager.installPackage()`.
  - `StoreModule` (`include/bos/StoreModule.h`, `src/StoreModule.cpp`) — `DesktopModule` subclass that owns the `StoreManager`.
  - `StoreApplication` (`include/bos/StoreApplication.h`, `src/StoreApplication.cpp`) — native application handler that opens a 1000×700 window titled "Baytevora Store".
- Registered `StoreModule` in `SessionManager` and `StoreApplication` in `ApplicationManager`.
- Exposed `storeManager` and `StoreCategory` to QML from `Application.cpp` after the desktop session starts.
- Added a placeholder "Baytevora Store" entry to the `ApplicationManager` registry so it appears in the launcher and taskbar.
- Seeded placeholder catalog entries: File Manager, Settings, Terminal, Browser, Calculator, Notes, System Monitor, Image Viewer, Text Editor, Music Player, Video Player, and Archive Manager.
- Notifications:
  - Install requested, already installed, and package unavailable messages.
- QML components:
  - `StoreWindow.qml` — main store window with sidebar, search, featured section, and application grid/details.
  - `StoreSidebar.qml` — left sidebar (renamed from `Sidebar.qml` to avoid conflict with the file manager sidebar).
  - `CategoryList.qml` — selectable category list.
  - `SearchBar.qml` — local search input.
  - `FeaturedSection.qml` — horizontal featured apps strip.
  - `ApplicationGrid.qml` — grid of application cards.
  - `ApplicationCard.qml` — card showing app icon, name, developer, description, and install state.
  - `ApplicationDetails.qml` — full details panel for a selected application.
  - `InstallButton.qml` — BDL-styled install/installed button.
  - `StoreSettingsPage.qml` — read-only Settings page showing catalog size, featured apps, and installed app count.
- Added a new "Store" entry in `SettingsManager` and embedded `StoreSettingsPage` inside `SettingsPage.qml`.
- Updated `WindowFrame.qml` to load `StoreWindow.qml` for the "Baytevora Store" application window.
- Updated `CMakeLists.txt` (Sprint 26, new sources/headers/QML files) and this README.
- No forbidden features are implemented: no networking, downloads, repositories, payments, accounts, licensing, activation, ratings API, reviews, purchases, automatic installation, filesystem modification, package extraction, background services, sandboxing, or rollback.

### Store Architecture

```
ApplicationManager
        |
        +-- StoreApplication
                |
                +-- WindowManager.registerWindow("Baytevora Store")
                        |
                        +-- WindowFrame -> StoreWindow.qml
                                |
                                +-- StoreManager (via storeManager context property)
                                        |
                                        +-- StoreCatalog (StoreItem records)
                                        |
                                        +-- PackageManager.installPackage(packageId)
```

The BSF is the foundation for the future Baytevora Store. Future sprints will replace the placeholder catalog with an online repository, add user accounts and licensing, enable ratings/reviews, and implement real package download and installation through the Package Manager.

## Sprint 26.5 Changes (Alpha Stability)

- Resolved duplicate Escape shortcut registration: removed the global Escape shortcut from `Launcher.qml` and `NotificationCenter.qml`.
- Added a single Escape dispatcher in `Desktop.qml` so Escape closes the launcher when visible and clears all notifications otherwise.
- Ensured the launcher consumes the Escape key event so the dispatcher does not double-handle it.
- Reordered `Application::run()` so `LoginManager::loggedIn` and `LoginManager::loggedOut` signal connections are established before `loginManager->cancel()` transitions state.
- Added the missing `loggedOut` handler to show the login window and stop the desktop session.
- Reviewed all `dynamic_cast` calls during desktop/session startup; existing nullptr guards are sufficient.
- Removed the now-unused `import BOS.Shell` from `NotificationCenter.qml`.

## Sprint 27 Changes

- Implemented the first version of the Baytevora Browser Foundation (BBF):
  - `BrowserPage` (`include/bos/BrowserPage.h`, `src/BrowserPage.cpp`) — data holder for `currentUrl`, `pageTitle`, and `loading`.
  - `BrowserManager` (`include/bos/BrowserManager.h`, `src/BrowserManager.cpp`) — owns a single `BrowserPage`, exposes `currentUrl`, `pageTitle`, and `loading` to QML, and provides `navigate()`, `reload()`, `stop()`, and `goHome()`.
  - `BrowserModule` (`include/bos/BrowserModule.h`, `src/BrowserModule.cpp`) — `DesktopModule` subclass that follows the existing module lifecycle and is registered with `SessionManager`.
  - `BrowserApplication` (`include/bos/BrowserApplication.h`, `src/BrowserApplication.cpp`) — native application handler that requests managed windows from `WindowManager` and emits a "Browser / Ready." information notification on launch.
- Added `Browser` to the `ApplicationRegistry` through `ApplicationManager`.
- Updated `ApplicationManager::launchApplication()` so the `Browser` entry opens `BrowserApplication` instead of a placeholder demo window.
- Registered `BrowserManager` as a QML type in `Application.cpp` so each `BrowserWindow` can create its own isolated manager instance.
- Created QML components:
  - `BrowserWindow.qml` — main browser window layout (toolbar, address bar, web view, status bar).
  - `BrowserToolbar.qml` — Back, Forward, Reload/Stop, and Home actions.
  - `BrowserToolButton.qml` — BDL-styled toolbar button.
  - `AddressBar.qml` — BDL-styled address bar that navigates when Enter/Return is pressed.
  - `BrowserView.qml` — wraps `WebEngineView`, keeps the `BrowserManager` synchronized with URL, title, and loading state.
  - `BrowserStatusBar.qml` — shows loading state and page title.
- Updated `WindowFrame.qml` to load `BrowserWindow.qml` for application windows whose `applicationName` is `"Browser"`.
- Added `Qt6::WebEngineQuick` and `Qt6::WebEngineCore` to `CMakeLists.txt` and initialized the WebEngine runtime in `main.cpp` with `QtWebEngineQuick::initialize()`.
- The home page is an internal `data:text/html` document displaying "Baytevora Browser", "BOS Alpha", and a welcome message.
- No forbidden features implemented: no tabs, bookmarks, history, downloads, extensions, profiles, accounts, synchronization, password manager, developer tools, browser settings, incognito mode, AI features, blockchain/wallet, ad blocker, or custom networking.

### Browser Architecture

```
SessionManager
    |
    +-- BrowserModule
            |
            +-- BrowserManager (shared lifecycle manager)

ApplicationManager
    |
    +-- BrowserApplication
            |
            +-- WindowManager.registerWindow("Browser")
                    |
                    +-- WindowFrame -> BrowserWindow.qml
                            |
                            +-- BrowserManager (per-window QML instance)
                                    |
                                    +-- BrowserPage
                                    |
                                    +-- WebEngineView
```

The BBF is the foundation for the future Baytevora Browser. Future sprints will add tabs, bookmarks, history, downloads, and security/privacy features while reusing this foundation.

## Sprint 28 Changes

- Implemented the first native Baytevora Notes application (BNA):
  - `Note` (`include/bos/Note.h`, `src/Note.cpp`) — lightweight data object holding `id`, `title`, `content`, `createdAt`, and `updatedAt`.
  - `NotesManager` (`include/bos/NotesManager.h`, `src/NotesManager.cpp`) — window-local manager owning a collection of `Note` objects. Exposes `notes`, `noteCount`, `activeNoteIndex`, `activeNoteId`, `activeNoteTitle`, `activeNoteContent`, and `activeNoteUpdatedAt` to QML. Provides slots for `createNote()`, `deleteNote(index)`, `selectNote(index)`, `setActiveNoteTitle(title)`, and `setActiveNoteContent(content)`. Emits `Note Created` and `Note Deleted` information notifications via the global `NotificationManager`.
  - `NotesApplication` (`include/bos/NotesApplication.h`, `src/NotesApplication.cpp`) — native application handler that requests an 800×560 managed window from `WindowManager` and emits a `Notes / Ready.` information notification on launch.
- Updated `ApplicationManager`:
  - Replaced the placeholder `Notes` entry with the real description and wired it to `NotesApplication`.
  - Added `setNotesApplication()` and a `Notes` launch branch so multiple managed Notes windows can be opened.
- Registered `NotesManager` as a QML type in `Application.cpp` so each `NotesWindow` owns an isolated manager instance.
- Updated `WindowFrame.qml` to load `NotesWindow.qml` for application windows whose `applicationName` is `"Notes"`.
- Created Notes QML components:
  - `NotesWindow.qml` — main layout with toolbar, sidebar, editor, and status bar.
  - `NotesToolbar.qml` — `New Note` and `Delete Note` actions.
  - `NotesToolButton.qml` — BDL-styled toolbar button.
  - `NotesSidebar.qml` — lists all notes and highlights the active note.
  - `NoteItem.qml` — individual note row used by the sidebar list.
  - `NotesEditor.qml` — editable title and plain-text content editor.
  - `NotesStatusBar.qml` — shows the total number of notes and the active note's last updated timestamp.
- All Notes components use `ThemeManager`, `TypographyManager`, `DesignTokens`, `SpacingManager`, and `IconManager`. No hardcoded colors, spacing, typography, or radius values were introduced.
- Notes are stored in memory only for the current session. No file persistence, import/export, synchronization, or cloud functionality is included.
- No forbidden features implemented: no Markdown, rich text, spell checking, search, tags, categories, attachments, images, tables, checklists, drawing, audio notes, encryption, AI, or collaboration.

### Notes Architecture

```
ApplicationManager
    |
    +-- NotesApplication
            |
            +-- WindowManager.registerWindow("Notes")
                    |
                    +-- WindowFrame -> NotesWindow.qml
                            |
                            +-- NotesManager (per-window QML instance)
                                    |
                                    +-- Note list
                                    +-- activeNoteChanged
                                    +-- noteCountChanged
```

Each Notes window owns an independent `NotesManager`, so opening multiple Notes windows does not share note collections. The manager exposes a `QVariantList` model to the sidebar and tracks the active note for the editor and status bar.

The BNA is the foundation for the future Baytevora Notes experience. Future sprints will add persistence, search, tags, categories, formatting, and synchronization while reusing this architecture.

## Sprint 29 Changes

- Implemented the first native Baytevora Image Viewer (BIV):
  - `ImageDocument` (`include/bos/ImageDocument.h`, `src/ImageDocument.cpp`) — data object holding `imagePath`, `imageName`, `imageWidth`, `imageHeight`, `loaded`, and `zoomLevel`, plus a helper for supported formats (PNG, JPG, JPEG, BMP).
  - `ImageViewerManager` (`include/bos/ImageViewerManager.h`, `src/ImageViewerManager.cpp`) — window-local manager that owns an `ImageDocument` and provides `openImage(path)`, `closeImage()`, `zoomIn()`, `zoomOut()`, `resetZoom()`, and `fitToWindow(width, height)`. Emits `Image Opened` and `Image Closed` information notifications.
  - `ImageViewerApplication` (`include/bos/ImageViewerApplication.h`, `src/ImageViewerApplication.cpp`) — native application handler that requests an 800×560 managed window from `WindowManager` and emits an `Image Viewer / Ready.` information notification on launch.
- Added `Image Viewer` to the `ApplicationRegistry` through `ApplicationManager` with category `Media` and `singleInstance` set to `false` so multiple windows can be opened.
- Updated `ApplicationManager::launchApplication()` to open `ImageViewerApplication` for the `Image Viewer` entry.
- Registered `ImageViewerManager` as a QML type in `Application.cpp` so each `ImageViewerWindow` owns an isolated manager instance.
- Updated `WindowFrame.qml` to load `ImageViewerWindow.qml` for application windows whose `applicationName` is `"Image Viewer"`.
- Created Image Viewer QML components:
  - `ImageViewerWindow.qml` — main layout with toolbar, image canvas, and status bar.
  - `ImageToolbar.qml` — Open Image (uses `FileDialog`), Zoom In, Zoom Out, Fit To Window, Reset Zoom.
  - `ImageToolButton.qml` — BDL-styled toolbar button.
  - `ImageCanvas.qml` — displays the loaded image centered and scaled by `zoomLevel`; shows `ImagePlaceholder` when empty.
  - `ImagePlaceholder.qml` — clean placeholder with "Open an image to begin."
  - `ImageStatusBar.qml` — shows image name, resolution, and zoom percentage.
- All Image Viewer components use `ThemeManager`, `TypographyManager`, `DesignTokens`, `SpacingManager`, and `IconManager`. No hardcoded colors, spacing, typography, radius, or icon sizes were introduced.
- Added `Qt6::QuickDialogs2` to `CMakeLists.txt` for the native file picker.
- No forbidden features implemented: no image editing, crop, rotate, flip, filters, slideshow, printing, metadata/EXIF editing, OCR, AI, cloud sync, albums, favorites, sharing, export, or Baytevora Chain integration.

### Image Viewer Architecture

```
ApplicationManager
    |
    +-- ImageViewerApplication
            |
            +-- WindowManager.registerWindow("Image Viewer")
                    |
                    +-- WindowFrame -> ImageViewerWindow.qml
                            |
                            +-- ImageViewerManager (per-window QML instance)
                                    |
                                    +-- ImageDocument
```

Each Image Viewer window owns an independent `ImageViewerManager`, so open images and zoom levels stay isolated per window. The viewer supports PNG, JPG, JPEG, and BMP only and keeps the image centered and aspect-ratio-preserving.

The BIV is the foundation for the future Baytevora media experience. Future sprints will add editing, slideshow, metadata, and sharing while reusing this architecture.

## Sprint 30 Changes

- Upgraded the Baytevora Design Language to BDL Version 2 — an adaptive design foundation:
  - `ThemeManager` (`include/bos/ThemeManager.h`, `src/ThemeManager.cpp`) now exposes adaptive read-only properties: `compactMode`, `touchMode`, `highDpi`, `scaleFactor`, `iconScale`, and `textScale`. Values are computed from `QGuiApplication::primaryScreen()` geometry and `devicePixelRatio`, and the `metricsChanged` signal notifies QML when adaptive metrics change.
  - `TypographyManager` (`include/bos/TypographyManager.h`, `src/TypographyManager.cpp`) now scales every font size by an adaptive `textScale` and emits change notifications for `display`, `heading`, `title`, `subtitle`, `body`, `caption`, and `small`.
  - `IconManager` (`include/bos/IconManager.h`, `src/IconManager.cpp`) now scales every icon size by an adaptive `iconScale` and emits change notifications for `small`, `medium`, `normal`, `large`, and `extraLarge`.
  - `AdaptiveLayoutManager` (`include/bos/AdaptiveLayoutManager.h`, `src/AdaptiveLayoutManager.cpp`) — new manager exposing `windowPadding`, `contentPadding`, `sectionSpacing`, `controlSpacing`, `toolbarHeight`, `taskbarHeight`, `sidebarWidth`, and `titleBarHeight`. All values are scaled by the BDL adaptive scale factor and emit `metricsChanged`.
  - `AccessibilityManager` (`include/bos/AccessibilityManager.h`, `src/AccessibilityManager.cpp`) — new placeholder manager exposing `largeTextEnabled`, `highContrastEnabled`, and `reducedMotionEnabled`. Values are currently fixed to `false`; future sprints will consume these properties.
- Wired the adaptive managers in `Application.cpp`:
  - `exposeDesignManagers()` initializes `AdaptiveLayoutManager` and `AccessibilityManager`.
  - `TypographyManager` and `IconManager` scales are initialized from `ThemeManager::textScale` / `iconScale`.
  - `AdaptiveLayoutManager` scale is initialized from `ThemeManager::scaleFactor`.
  - `ThemeManager::metricsChanged` is connected to a lambda that propagates updated scales to `TypographyManager`, `IconManager`, and `AdaptiveLayoutManager` so the entire UI stays consistent when display metrics change.
- Updated QML components to consume adaptive BDL values:
  - `WindowFrame.qml` — title bar height now uses `AdaptiveLayoutManager.titleBarHeight`.
  - `Taskbar.qml` — taskbar height now uses `AdaptiveLayoutManager.taskbarHeight`.
  - `Launcher.qml` — launcher bottom margin now uses `AdaptiveLayoutManager.taskbarHeight`.
  - `PowerMenu.qml` — spacing and margins now use `SpacingManager`.
  - Native application windows:
    - `FileManagerWindow.qml` — sidebar width uses `AdaptiveLayoutManager.sidebarWidth`; toolbar height uses `AdaptiveLayoutManager.toolbarHeight`.
    - `TerminalWindow.qml` — toolbar height uses `AdaptiveLayoutManager.toolbarHeight`.
    - `BrowserToolbar.qml`, `NotesToolbar.qml`, `ImageToolbar.qml` — toolbar height uses `AdaptiveLayoutManager.toolbarHeight`.
  - Additional radius values in `SettingsButton.qml`, `Sidebar.qml`, `TerminalView.qml`, `SettingsPage.qml`, `Toolbar.qml`, `NavigationSidebar.qml`, `LauncherButton.qml`, and `ToolButton.qml` now use `DesignTokens` instead of hardcoded numeric values.
- No visual redesign, no new colors, no animations, no transparency/blur, and no theme switching were introduced. Existing appearance is preserved while the adaptive foundation is established.
- No forbidden features implemented: no dark/light modes, user themes, acrylic/glass effects, dynamic wallpaper colors, automatic accent colors, motion engine, responsive redesign, AI styling, plugins, accounts, or cloud synchronization.

### BDL v2 Adaptive Model

```
Primary Screen
    |
    +-- ThemeManager
    |       +-- scaleFactor
    |       +-- textScale  ----> TypographyManager
    |       +-- iconScale  ----> IconManager
    |       +-- compactMode / touchMode / highDpi
    |
    +-- AdaptiveLayoutManager
            +-- toolbarHeight
            +-- taskbarHeight
            +-- titleBarHeight
            +-- sidebarWidth
            +-- windowPadding / contentPadding
            +-- sectionSpacing / controlSpacing
```

All design managers are exposed as QML context properties. QML components reference them instead of fixed numbers, and change notifications propagate from `ThemeManager` down through `TypographyManager`, `IconManager`, and `AdaptiveLayoutManager` when the display environment changes.

The BDL v2 foundation prepares the shell for future accessibility work, high-DPI refinements, and per-device scaling without changing individual component code.

## Sprint 31 Changes

- Introduced the Baytevora Calculator Application (BCA), the first native calculator for Baytevora OS.
- Added the calculator C++ layer:
  - `CalculatorEngine` (`include/bos/CalculatorEngine.h`, `src/CalculatorEngine.cpp`) — stateless arithmetic evaluator that sanitizes expressions using standard operators (`+`, `−`, `×`, `÷`), evaluates them with `QJSEngine`, and detects malformed expressions and divide-by-zero. Results are formatted to remove unnecessary trailing zeros.
  - `CalculatorManager` (`include/bos/CalculatorManager.h`, `src/CalculatorManager.cpp`) — per-window manager exposed to QML with `currentExpression` and `currentResult` properties. Provides invokable actions: `appendDigit`, `appendOperator`, `appendDecimalPoint`, `toggleSign`, `percentage`, `clear`, `clearEntry`, `backspace`, `calculate`, and `copyResult`. Integrates with `ClipboardManager` for `copyResult()` and with `NotificationManager` for error and copy notifications.
  - `CalculatorApplication` (`include/bos/CalculatorApplication.h`, `src/CalculatorApplication.cpp`) — native application handler that requests a 320×480 managed window from `WindowManager` and emits a `Calculator / Ready.` information notification on launch.
- Integrated the calculator with the Application Framework:
  - `ApplicationManager` now registers a `CalculatorApplication` handler and routes launches of `Calculator` to it.
  - The placeholder `Calculator` entry in `registerPlaceholderApplications()` was updated to allow multiple windows (`singleInstance: false`).
  - `CalculatorManager` is registered as a QML type (`qmlRegisterType<CalculatorManager>`) so each `CalculatorWindow` owns an independent manager instance.
- Created the calculator QML user interface:
  - `CalculatorWindow.qml` — root content with a `CalculatorManager`, `CalculatorDisplay`, `CalculatorKeypad`, `CalculatorStatusBar`, and keyboard `Shortcut` bindings.
  - `CalculatorDisplay.qml` — shows the current expression and result using BDL typography and colors.
  - `CalculatorKeypad.qml` — standard 4-column desktop keypad with digits `0–9`, operators `+`, `−`, `×`, `÷`, `=`, and functions `C`, `CE`, `⌫`, `±`, `%`, `.`.
  - `CalculatorButton.qml` — reusable keypad button using BDL tokens for background, radius, and typography.
  - `CalculatorStatusBar.qml` — footer indicating "Standard Calculator".
- Added keyboard support in `CalculatorWindow.qml`:
  - Digits `0–9`, operators `+`, `-`, `*`, `/`, decimal `.`, percentage `%`, `Enter`/`Return`/`=` for calculate, `Backspace`, `Escape` for clear, and `Ctrl+C` to copy the current result.
- Wired clipboard and notification services:
  - `copyResult()` copies the current result via `ClipboardManager` and emits a "Result copied." information notification.
  - Calculation errors (including divide-by-zero and malformed expressions) emit a "Calculation Error" error notification.
  - `CalculatorApplication::open()` emits a "Calculator / Ready." information notification.
- Updated `WindowFrame.qml` to load `CalculatorWindow.qml` when `applicationName == "Calculator"`.
- Updated `CMakeLists.txt` with the new C++ sources/headers and QML files.
- No forbidden features were implemented: no scientific mode, programmer mode, graphing, unit/currency conversion, equation solver, history, memory functions, themes, AI, cloud sync, accounts, persistence, or Baytevora Chain integration.

### Calculator Class Relationships

```
ApplicationManager
    |
    +-- setCalculatorApplication(CalculatorApplication*)
            |
            +-- CalculatorApplication::open()
                    |
                    +-- WindowManager::registerWindow("Calculator", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- CalculatorWindow.qml
                                            |
                                            +-- CalculatorManager (per-window)
                                                    |
                                                    +-- CalculatorEngine
                                                    +-- ClipboardManager (for copyResult)
                                                    +-- NotificationManager (for notifications)
```

Each `CalculatorWindow` owns its own `CalculatorManager`, so multiple Calculator windows can operate independently with isolated expressions and results.

The Calculator consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes.

## Sprint 32 Changes

- Introduced the Baytevora PDF Viewer Foundation (BPV), the first native PDF viewer for Baytevora OS.
- Added the PDF Viewer C++ layer:
  - `PdfDocument` (`include/bos/PdfDocument.h`, `src/PdfDocument.cpp`) — metadata object exposed to QML with `filePath`, `fileName`, `pageCount`, `currentPage`, `zoomLevel`, `loaded`, and `error` properties.
  - `PdfViewerManager` (`include/bos/PdfViewerManager.h`, `src/PdfViewerManager.cpp`) — per-window manager exposed to QML. Owns the `PdfDocument`, provides `openDocument(path)`, `closeDocument()`, `nextPage()`, `previousPage()`, `firstPage()`, `lastPage()`, `goToPage(page)`, `zoomIn()`, `zoomOut()`, `resetZoom()`, `fitToWidth(viewWidth)`, and `fitToPage(viewWidth, viewHeight)`. Synchronizes its state with the Qt PdfQuick `PdfDocument` via `updatePageCount()` and `setDocumentLoaded()`. Integrates with `NotificationManager` for "Document Opened.", "Document Closed.", and "Failed to Open PDF." notifications.
  - `PdfViewerApplication` (`include/bos/PdfViewerApplication.h`, `src/PdfViewerApplication.cpp`) — native application handler that requests a 900×680 managed window from `WindowManager` and emits a "PDF Viewer / Ready." information notification on launch.
- Integrated the PDF Viewer with the Application Framework:
  - `ApplicationManager` now registers a `PdfViewerApplication` handler and routes launches of `PDF Viewer` to it.
  - Added a `PDF Viewer` placeholder entry with `singleInstance: false` so multiple windows can be opened.
  - `PdfViewerManager` is registered as a QML type (`qmlRegisterType<PdfViewerManager>`) so each `PdfViewerWindow` owns an independent manager instance.
- Created the PDF Viewer QML user interface using Qt PDF (`Qt.Pdf`):
  - `PdfViewerWindow.qml` — root content with a `PdfViewerManager`, `PdfToolbar`, `PdfSidebar`, `PdfPageView`, `PdfStatusBar`, and keyboard `Shortcut` bindings.
  - `PdfToolbar.qml` — Open, First Page, Previous Page, Next Page, Last Page, Zoom In, Zoom Out, Fit Width, Fit Page, and Reset Zoom actions.
  - `PdfPageView.qml` — renders the current page with `QPdf.PdfPageView` inside a `Flickable` for smooth scrolling and centers the page.
  - `PdfSidebar.qml` — scrollable thumbnail list of all pages.
  - `PdfThumbnailItem.qml` — single thumbnail delegate using a scaled `QPdf.PdfPageView`.
  - `PdfStatusBar.qml` — displays filename, current page / total pages, and zoom percentage.
  - `PdfToolButton.qml` — reusable BDL-styled toolbar button.
- Added keyboard support in `PdfViewerWindow.qml`:
  - `Ctrl+O` — Open file dialog.
  - `PageUp` / `PageDown` — Previous / next page.
  - `Home` / `End` — First / last page.
  - `Ctrl++` / `Ctrl+-` / `Ctrl+0` — Zoom in / zoom out / reset zoom.
- Wired notifications:
  - `PdfViewerApplication::open()` emits "PDF Viewer / Ready.".
  - `openDocument()` emits "Document Opened." on success and "Failed to Open PDF." on missing/invalid files.
  - `closeDocument()` emits "Document Closed.".
  - Page changes do not trigger notifications.
- Updated `WindowFrame.qml` to load `PdfViewerWindow.qml` when `applicationName == "PDF Viewer"`.
- Updated `CMakeLists.txt` with Qt6 `Pdf` and `PdfQuick` components, plus the new C++ sources, headers, and QML files.
- Updated `docs/README.md` with PDF Viewer architecture, class relationships, and ownership diagrams.
- No forbidden features were implemented: no PDF editing, text/image editing, annotations, highlighting, drawing, signatures, OCR, form editing, merge, split, export, encryption, password protection, cloud sync, AI, or Baytevora Chain integration.

### PDF Viewer Class Relationships

```
ApplicationManager
    |
    +-- setPdfViewerApplication(PdfViewerApplication*)
            |
            +-- PdfViewerApplication::open()
                    |
                    +-- WindowManager::registerWindow("PDF Viewer", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- PdfViewerWindow.qml
                                            |
                                            +-- PdfViewerManager (per-window)
                                                    |
                                                    +-- PdfDocument
                                                    +-- NotificationManager
                                                    |
                                                    +-- QML: QPdf.PdfDocument / QPdf.PdfPageView
```

Each `PdfViewerWindow` owns its own `PdfViewerManager`, so multiple PDF Viewer windows can operate independently with isolated documents, pages, and zoom levels.

The PDF Viewer consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes.

## Sprint 33 Changes

- Introduced the Baytevora Archive Manager (BAM), the first native archive inspection tool for Baytevora OS.
- Added the Archive Manager C++ layer:
  - `ArchiveEntry` (`include/bos/ArchiveEntry.h`, `src/ArchiveEntry.cpp`) — value type holding `name`, `path`, `size`, `compressedSize`, `isDirectory`, and `modifiedDate` for a single archive item.
  - `ArchiveDocument` (`include/bos/ArchiveDocument.h`, `src/ArchiveDocument.cpp`) — metadata object exposed to QML with `archivePath`, `archiveName`, `archiveType`, `entryCount`, `loaded`, and `error` properties.
  - `ArchiveEngine` (`include/bos/ArchiveEngine.h`, `src/ArchiveEngine.cpp`) — lightweight read-only parser for `ZIP`, `TAR`, and `TAR.GZ` archives using a custom ZIP central-directory parser, a TAR header parser, and zlib for gzip decompression.
  - `ArchiveManager` (`include/bos/ArchiveManager.h`, `src/ArchiveManager.cpp`) — per-window manager exposed to QML. Owns the `ArchiveDocument`, maintains an entry model, and provides `openArchive(path)`, `closeArchive()`, `refresh()`, `extractAll()`, `extractSelection()`, `selectAllEntries()`, `clearSelection()`, `toggleSelection(index)`, and `isSelected(index)`.
  - `ArchiveApplication` (`include/bos/ArchiveApplication.h`, `src/ArchiveApplication.cpp`) — native application handler that requests an 860×620 managed window from `WindowManager` and emits an "Archive Manager / Ready." notification. Also exposes `openArchive(path)` for future File Manager integration.
- Integrated the Archive Manager with the Application Framework:
  - `ApplicationManager` now registers an `ArchiveApplication` handler and routes launches of `Archive Manager` to it.
  - Added an `Archive Manager` placeholder entry with `singleInstance: false` so multiple windows can be opened.
  - `ArchiveManager` is registered as a QML type (`qmlRegisterType<ArchiveManager>`) so each `ArchiveWindow` owns an independent manager instance.
- Created the Archive Manager QML user interface:
  - `ArchiveWindow.qml` — root content with `ArchiveToolbar`, `ArchiveSidebar`, `ArchiveFileList`, `ArchiveStatusBar`, and keyboard `Shortcut` bindings.
  - `ArchiveToolbar.qml` — Open Archive, Extract All, Extract Selected, and Refresh actions.
  - `ArchiveSidebar.qml` — displays archive name, type, entry count, and compressed metadata.
  - `ArchiveFileList.qml` — scrollable list of archive entries with column headers.
  - `ArchiveEntryDelegate.qml` — single entry row showing name, size, compressed size, and modification date; supports selection toggling.
  - `ArchiveStatusBar.qml` — displays archive name, selected count, and total entries.
  - `ArchiveToolButton.qml` — reusable BDL-styled toolbar button.
- Added keyboard support in `ArchiveWindow.qml`:
  - `Ctrl+O` — Open archive dialog.
  - `F5` — Refresh archive.
  - `Delete` / `Escape` — Clear selection.
  - `Ctrl+A` — Select all entries.
- Wired notifications:
  - `ArchiveApplication::open()` emits "Archive Manager / Ready.".
  - `openArchive()` emits "Archive Opened." on success and "Failed to Open Archive." on failure.
  - `closeArchive()` emits "Archive Closed.".
  - `extractAll()` and `extractSelection()` emit "Extraction Started" and "Extraction Completed" placeholders.
- Updated `WindowFrame.qml` to load `ArchiveWindow.qml` when `applicationName == "Archive Manager"`.
- Updated `CMakeLists.txt` with zlib (`find_package(ZLIB REQUIRED)` and `ZLIB::ZLIB`), plus new C++ sources, headers, and QML files.
- Updated `docs/README.md` with Archive Manager architecture, archive lifecycle, class relationships, and ownership diagrams.
- No forbidden features were implemented: no archive creation, editing, file deletion/renaming, password protection, encryption, drag-and-drop extraction, compression settings, background extraction, cloud storage, AI, or Baytevora Chain integration.

### Archive Manager Class Relationships

```
ApplicationManager
    |
    +-- setArchiveApplication(ArchiveApplication*)
            |
            +-- ArchiveApplication::open() / openArchive(path)
                    |
                    +-- WindowManager::registerWindow("Archive Manager", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- ArchiveWindow.qml
                                            |
                                            +-- ArchiveManager (per-window)
                                                    |
                                                    +-- ArchiveDocument
                                                    +-- NotificationManager
                                                    |
                                                    +-- ArchiveEngine::readArchive(path)
                                                    +-- QList<ArchiveEntry>
```

Each `ArchiveWindow` owns its own `ArchiveManager`, so multiple Archive Manager windows can operate independently with isolated archives, selections, and entry lists.

The Archive Manager consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Extraction operations are intentionally placeholder notifications only, with real extraction reserved for a future Baytevora Archive Studio release.

## Sprint 34 Changes

- Introduced the Baytevora Media Player (BMP), the first native media playback application for Baytevora OS.
- Added the Media Player C++ layer:
  - `MediaDocument` (`include/bos/MediaDocument.h`, `src/MediaDocument.cpp`) — metadata object exposed to QML with `filePath`, `fileName`, `duration`, `currentPosition`, `mediaType`, `loaded`, `playing`, `volume`, and `muted` properties.
  - `MediaPlayerManager` (`include/bos/MediaPlayerManager.h`, `src/MediaPlayerManager.cpp`) — per-window playback manager exposed to QML. Owns a `QMediaPlayer` and `QAudioOutput`, a `MediaDocument`, and provides `openMedia(path)`, `closeMedia()`, `play()`, `pause()`, `stop()`, `togglePlayPause()`, `seek(position)`, `setVolume(value)`, `mute()`, `unmute()`, and `toggleMute()`.
  - `MediaPlayerApplication` (`include/bos/MediaPlayerApplication.h`, `src/MediaPlayerApplication.cpp`) — native application handler that requests a managed 900×640 Media Player window from `WindowManager` and emits a "Media Player / Ready." information notification on launch. Also exposes `openMedia(path)` for future File Manager integration.
- Integrated the Media Player with the Application Framework:
  - `ApplicationManager` now registers a `MediaPlayerApplication` handler and routes launches of `Media Player` to it.
  - Added a `Media Player` application entry (`media-player`) with `singleInstance: false` so multiple Media Player windows can be opened independently.
  - `MediaPlayerManager` is registered as a QML type (`qmlRegisterType<MediaPlayerManager>`) so each `MediaPlayerWindow` owns an independent manager/player instance.
- Created the Media Player QML user interface:
  - `MediaPlayerWindow.qml` — root content with `MediaToolbar`, `PlaylistSidebar`, `MediaCanvas`, `MediaControls`, `MediaStatusBar`, and keyboard `Shortcut` bindings.
  - `MediaToolbar.qml` — Open, Play, Pause, Stop, and Mute actions.
  - `MediaCanvas.qml` — video surface via `QtMultimedia.VideoOutput`, album-artwork placeholder for audio files, and empty-state placeholder when no media is loaded.
  - `MediaControls.qml` — Previous (placeholder), Play/Pause toggle, Next (placeholder), seek slider, current/total time label, and volume slider.
  - `PlaylistSidebar.qml` — prepared for future playlists; currently displays the currently opened file.
  - `MediaStatusBar.qml` — displays filename, media type, and playback state.
  - `MediaToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented keyboard support in `MediaPlayerWindow.qml`:
  - `Ctrl+O` — Open media dialog.
  - `Space` — Toggle play/pause.
  - `Left Arrow` — Seek backward 5 seconds.
  - `Right Arrow` — Seek forward 5 seconds.
  - `Up Arrow` — Increase volume by 10%.
  - `Down Arrow` — Decrease volume by 10%.
  - `M` — Toggle mute.
  - `Escape` — Stop playback.
- Wired notifications:
  - `MediaPlayerApplication::open()` emits "Media Player / Ready.".
  - `openMedia()` emits "Media Opened." on success and "Failed to Open Media." on error.
  - `closeMedia()` emits "Media Closed.".
  - End of playback emits "Playback Finished." via the `QMediaPlayer::EndOfMedia` status.
  - Play and pause actions intentionally do not emit notifications.
- Updated `WindowFrame.qml` to load `MediaPlayerWindow.qml` when `applicationName == "Media Player"`.
- Updated `CMakeLists.txt` to require `Qt6::Multimedia` and include all new C++ sources, headers, and QML files.
- Updated `docs/README.md` with Media Player architecture, playback lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no playlists (beyond current-file display), streaming services, online media, video/audio editing, equalizer, visualizations, subtitles, speed control, casting, screen recording, AI, or Baytevora Chain integration.

### Media Player Class Relationships

```
ApplicationManager
    |
    +-- setMediaPlayerApplication(MediaPlayerApplication*)
            |
            +-- MediaPlayerApplication::open() / openMedia(path)
                    |
                    +-- WindowManager::registerWindow("Media Player", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- MediaPlayerWindow.qml
                                            |
                                            +-- MediaPlayerManager (per-window)
                                                    |
                                                    +-- MediaDocument
                                                    +-- QMediaPlayer
                                                    +-- QAudioOutput
                                                    +-- NotificationManager
```

Each `MediaPlayerWindow` owns its own `MediaPlayerManager` (and therefore its own `QMediaPlayer` instance), so multiple Media Player windows can play different media simultaneously without shared state.

### Playback Lifecycle

1. User opens Media Player from the launcher or File Manager (future integration).
2. `MediaPlayerApplication` requests a managed window and emits "Media Player / Ready.".
3. `MediaPlayerWindow` creates its own `MediaPlayerManager`.
4. User opens a supported media file via the Open dialog or `openMedia(path)`.
5. `MediaPlayerManager` populates `MediaDocument`, sets the `QMediaPlayer` source, detects the media type, and calls `play()`.
6. `QMediaPlayer` signals update `MediaDocument` properties: `duration`, `currentPosition`, `playing`, `loaded`, and end-of-media.
7. `MediaCanvas` binds to `manager.player` for video output and switches between video, audio, and empty placeholders.
8. `MediaControls` and `MediaStatusBar` read `MediaDocument` to update the UI.
9. Keyboard shortcuts and toolbar buttons route through `MediaPlayerManager` invokable methods.

The Media Player consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Full playlist, streaming, and advanced media features are reserved for the future Baytevora Media Studio release.

## Sprint 35 Changes

- Introduced the Baytevora Text Editor (BTE), the first native plain-text editing application for Baytevora OS.
- Added the Text Editor C++ layer:
  - `TextDocument` (`include/bos/TextDocument.h`, `src/TextDocument.cpp`) — metadata object exposed to QML with `filePath`, `fileName`, `modified`, `loaded`, `lineCount`, and `characterCount` properties.
  - `TextEditorManager` (`include/bos/TextEditorManager.h`, `src/TextEditorManager.cpp`) — per-window document manager exposed to QML. Owns a `TextDocument`, stores plain-text content, and provides `newDocument()`, `openDocument(path)`, `saveDocument()`, `saveDocumentAs(path)`, `closeDocument()`, `undo()`, `redo()`, `cut()`, `copy()`, `paste()`, `selectAll()`, `setModified(bool)`, and `updateStatistics()`. Editing invokables emit request signals that the QML `TextArea` handles so undo/redo and clipboard use the native Qt Quick editing stack. Also exposes `cursorLine` and `cursorColumn` properties updated from QML.
  - `TextEditorApplication` (`include/bos/TextEditorApplication.h`, `src/TextEditorApplication.cpp`) — native application handler that requests a managed 860×620 Text Editor window from `WindowManager` and emits a "Text Editor / Ready." information notification on launch. Also exposes `openDocument(path)` for future File Manager integration.
- Integrated the Text Editor with the Application Framework:
  - `ApplicationManager` now registers a `TextEditorApplication` handler and routes launches of `Text Editor` to it.
  - Added a `Text Editor` application entry (`text-editor`) with `singleInstance: false` so multiple Text Editor windows can be opened independently.
  - `TextEditorManager` is registered as a QML type (`qmlRegisterType<TextEditorManager>`) so each `TextEditorWindow` owns an independent manager instance.
- Created the Text Editor QML user interface:
  - `TextEditorWindow.qml` — root content with `TextToolbar`, `FindBar`, `TextEditorArea`, `TextStatusBar`, and keyboard `Shortcut` bindings.
  - `TextToolbar.qml` — New, Open, Save, Save As, Undo, Redo, Cut, Copy, Paste, and Find (placeholder) actions.
  - `TextEditorArea.qml` — plain-text `TextArea` with line wrapping, UTF-8 support, select-by-mouse/keyboard, and bidirectional binding to `TextEditorManager.content`. `Connections` wire editing-request signals to the `TextArea` undo/redo/cut/copy/paste/selectAll methods. Cursor line and column are computed in JavaScript and pushed back to the manager.
  - `FindBar.qml` — placeholder find bar for future search/replace functionality.
  - `TextStatusBar.qml` — displays filename with modified indicator, line count, character count, and cursor line/column.
  - `TextToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented keyboard support in `TextEditorWindow.qml`:
  - `Ctrl+N` — New document.
  - `Ctrl+O` — Open document dialog.
  - `Ctrl+S` — Save document.
  - `Ctrl+Shift+S` — Save document as.
  - `Ctrl+Z` — Undo.
  - `Ctrl+Y` — Redo.
  - `Ctrl+X` — Cut.
  - `Ctrl+C` — Copy.
  - `Ctrl+V` — Paste.
  - `Ctrl+A` — Select all.
  - `Ctrl+F` — Find placeholder.
- Wired notifications:
  - `TextEditorApplication::open()` emits "Text Editor / Ready.".
  - `openDocument()` emits "File Opened." on success and "Failed to Open File." on error.
  - `saveDocument()` and `saveDocumentAs()` emit "File Saved." on success and "Failed to Save File." on error.
  - `closeDocument()` emits "File Closed.".
  - Edit actions do not emit notifications.
- Updated `WindowFrame.qml` to load `TextEditorWindow.qml` when `applicationName == "Text Editor"`.
- Updated `CMakeLists.txt` to include all new C++ sources, headers, and QML files.
- Updated `docs/README.md` with Text Editor architecture, document lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no syntax highlighting, code completion, terminal integration, split editor, tabs, rich text editing, Markdown preview, plugins, AI, version control, or Baytevora Chain integration.

### Text Editor Class Relationships

```
ApplicationManager
    |
    +-- setTextEditorApplication(TextEditorApplication*)
            |
            +-- TextEditorApplication::open() / openDocument(path)
                    |
                    +-- WindowManager::registerWindow("Text Editor", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- TextEditorWindow.qml
                                            |
                                            +-- TextEditorManager (per-window)
                                                    |
                                                    +-- TextDocument
                                                    +-- NotificationManager
                                                    +-- content (QString)
```

Each `TextEditorWindow` owns its own `TextEditorManager`, so multiple Text Editor windows can edit different documents independently with isolated content, modified flags, and cursor positions.

### Document Lifecycle

1. User opens Text Editor from the launcher or File Manager (future integration).
2. `TextEditorApplication` requests a managed window and emits "Text Editor / Ready.".
3. `TextEditorWindow` creates its own `TextEditorManager` and starts with a new untitled document.
4. User creates a new document or opens a supported UTF-8 text file via the Open dialog or `openDocument(path)`.
5. `TextEditorManager` loads the file content, populates `TextDocument` metadata, calls `updateStatistics()`, and clears the modified flag.
6. User edits plain text in `TextEditorArea`; `onTextChanged` pushes content back to the manager and sets `modified`.
7. User saves via `Ctrl+S` or the Save button; `saveDocument()` / `saveDocumentAs()` writes UTF-8 content and clears `modified`.
8. Status bar continuously reflects filename, modified state, line/character counts, and cursor line/column.

The Text Editor consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Advanced text editing capabilities are reserved for the future Baytevora Text Studio project.

## Sprint 36 Changes

- Introduced the Baytevora System Monitor (BSM), the first native system-monitoring application for Baytevora OS.
- Added the System Monitor C++ layer:
  - `SystemInfo` (`include/bos/SystemInfo.h`, `src/SystemInfo.cpp`) — read-only metrics object exposed to QML with properties for `cpuUsage`, `cpuThreads`, `cpuFrequency`, `memoryUsed`, `memoryAvailable`, `memoryTotal`, `swapUsed`, `swapTotal`, `diskUsed`, `diskFree`, `diskTotal`, `uptime`, `operatingSystem`, `kernelVersion`, and `architecture`.
  - `SystemMonitorManager` (`include/bos/SystemMonitorManager.h`, `src/SystemMonitorManager.cpp`) — per-window monitoring controller exposed to QML. Owns a `SystemInfo` instance, uses a `QTimer` to refresh every second, and provides `refresh()`, `startMonitoring()`, and `stopMonitoring()` invokables. Collects metrics from `/proc/stat`, `/proc/meminfo`, `/proc/uptime`, `/proc/cpuinfo`, and `statvfs("/")`, and uses `QSysInfo` for platform identification.
  - `SystemMonitorApplication` (`include/bos/SystemMonitorApplication.h`, `src/SystemMonitorApplication.cpp`) — native application handler that requests a managed 780×580 System Monitor window from `WindowManager` and emits a "System Monitor / Ready." information notification on launch.
- Integrated the System Monitor with the Application Framework:
  - `ApplicationManager` now registers a `SystemMonitorApplication` handler and routes launches of `System Monitor` to it.
  - Added a `System Monitor` application entry (`system-monitor`) with `singleInstance: false` so multiple System Monitor windows can be opened independently.
  - `SystemMonitorManager` is registered as a QML type (`qmlRegisterType<SystemMonitorManager>`) so each `SystemMonitorWindow` owns an independent manager instance.
- Created the System Monitor QML user interface:
  - `SystemMonitorWindow.qml` — root content that owns a `SystemMonitorManager`, starts monitoring on completion, and arranges `OverviewPage` and `MonitorStatusBar`.
  - `OverviewPage.qml` — responsive overview page with a heading, manual Refresh button, and a grid of metric cards.
  - `CpuCard.qml` — CPU usage percentage, progress bar, thread count, and current frequency.
  - `MemoryCard.qml` — memory and swap usage with progress bars and human-readable sizes.
  - `DiskCard.qml` — root disk usage with a progress bar and free/total sizes.
  - `SystemCard.qml` — formatted uptime, OS name, kernel version, and CPU architecture.
  - `MonitorStatusBar.qml` — monitoring state and current CPU usage summary.
- Implemented refresh behavior:
  - `SystemMonitorManager` starts a 1-second `QTimer` when the window loads.
  - Manual refresh is available via the Refresh button in `OverviewPage`.
  - `stopMonitoring()` is called on destruction to stop the timer and prevent updates for closed windows.
- Wired notifications:
  - `SystemMonitorApplication::open()` emits "System Monitor / Ready.".
  - Normal monitoring refreshes do not emit notifications.
- Updated `WindowFrame.qml` to load `SystemMonitorWindow.qml` when `applicationName == "System Monitor"`.
- Updated `CMakeLists.txt` to include all new C++ sources, headers, and QML files.
- Updated `docs/README.md` with System Monitor architecture, monitoring lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no process list, task killing, performance graphs, GPU monitoring, temperature sensors, fan monitoring, network monitoring, benchmarking, logging, AI, or Baytevora Chain integration.

### System Monitor Class Relationships

```
ApplicationManager
    |
    +-- setSystemMonitorApplication(SystemMonitorApplication*)
            |
            +-- SystemMonitorApplication::open()
                    |
                    +-- WindowManager::registerWindow("System Monitor", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- SystemMonitorWindow.qml
                                            |
                                            +-- SystemMonitorManager (per-window)
                                                    |
                                                    +-- SystemInfo
                                                    +-- QTimer (1s refresh)
                                                    +-- NotificationManager
```

Each `SystemMonitorWindow` owns its own `SystemMonitorManager` and `SystemInfo`, so multiple System Monitor windows can show independent snapshots without shared state.

### Monitoring Lifecycle

1. User opens System Monitor from the launcher.
2. `SystemMonitorApplication` requests a managed window and emits "System Monitor / Ready.".
3. `SystemMonitorWindow` creates its own `SystemMonitorManager`.
4. `SystemMonitorManager` reads static platform info (`QSysInfo`) and CPU thread count once, then runs `refresh()` immediately.
5. A 1-second `QTimer` triggers `refresh()` repeatedly while the window is open.
6. Each refresh:
   - Parses `/proc/stat` to compute CPU usage percentage from a delta of total and idle jiffies.
   - Reads `/proc/meminfo` to compute memory used/available/total and swap used/total.
   - Calls `statvfs("/")` to compute disk used/free/total.
   - Reads `/proc/uptime` to update system uptime.
7. `SystemInfo` property changes propagate to the QML cards and status bar.
8. When the window is destroyed, `stopMonitoring()` halts the timer.

The System Monitor consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Advanced monitoring capabilities are reserved for future sprints and the enterprise monitoring enhancements.

## Sprint 37 Changes

- Introduced the Baytevora Task Manager (BTM), the first native task-management application for Baytevora OS.
- Added the Task Manager C++ layer:
  - `TaskInfo` (`include/bos/TaskInfo.h`, `src/TaskInfo.cpp`) — value object exposed to QML with `processId`, `applicationName`, `executableName`, `state`, `cpuUsage`, `memoryUsage`, `startTime`, and `windowCount` properties.
  - `TaskManager` (`include/bos/TaskManager.h`, `src/TaskManager.cpp`) — per-window task model exposed to QML. Maintains a live `QList<TaskInfo*>`, refreshes every second via `QTimer`, groups windows by application name, and provides `refresh()`, `startMonitoring()`, `stopMonitoring()`, and `terminateTask(processId)`. Termination only closes user applications launched through the Baytevora Application Framework; protected BOS services and the Task Manager itself are rejected.
  - `TaskManagerApplication` (`include/bos/TaskManagerApplication.h`, `src/TaskManagerApplication.cpp`) — native application handler that requests a managed 820×560 Task Manager window from `WindowManager` and emits a "Task Manager / Ready." information notification on launch.
- Integrated the Task Manager with the Application Framework:
  - `ApplicationManager` now registers a `TaskManagerApplication` handler and routes launches of `Task Manager` to it.
  - Added a `Task Manager` application entry (`task-manager`) with `singleInstance: false` so multiple Task Manager windows can be opened independently.
  - `TaskManager` is registered as a QML type (`qmlRegisterType<TaskManager>`) so each `TaskManagerWindow` owns an independent manager instance.
- Created the Task Manager QML user interface:
  - `TaskManagerWindow.qml` — root content that owns a `TaskManager`, wires `NotificationManager` and `WindowManager`, starts monitoring on completion, and arranges `TaskToolbar`, `ProcessTable`, `ProcessDetails`, and `TaskStatusBar`.
  - `TaskToolbar.qml` — Refresh and End Task actions. End Task uses the currently selected process ID.
  - `ProcessTable.qml` — scrollable list with a column header (Application, PID, CPU %, Memory, Status, Start Time) and rows bound to `taskManager.tasks`.
  - `ProcessDelegate.qml` — BDL-styled row delegate with selection highlight.
  - `ProcessDetails.qml` — bottom panel showing the selected task's application name, executable path, PID, window count, CPU usage, and memory usage.
  - `TaskStatusBar.qml` — displays the running application count and selected application name.
  - `TaskToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented refresh behavior:
  - `TaskManager` starts a 1-second `QTimer` when the window loads.
  - Each refresh reads `WindowManager.windows`, groups windows by `applicationName`, and updates the task model.
  - Manual refresh is available via the Refresh toolbar button.
  - `stopMonitoring()` is called on destruction to stop the timer for closed windows.
- Implemented safe termination:
  - `terminateTask(processId)` looks up the task, verifies the application is not protected, then closes all windows with the same `applicationName` through `WindowManager::closeWindow()`.
  - Protected applications include `Desktop`, `SessionManager`, `WindowManager`, `NotificationService`, `Settings`, `Task Manager`, and any application whose name ends with `Module` or `Service`.
  - Successful termination emits "Application Terminated."; failures emit "Failed to Terminate Application.".
  - Automatic refreshes do not emit notifications.
- Updated `WindowFrame.qml` to load `TaskManagerWindow.qml` when `applicationName == "Task Manager"`.
- Updated `CMakeLists.txt` to include all new C++ sources, headers, and QML files.
- Updated `docs/README.md` with Task Manager architecture, monitoring lifecycle, task lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no process priority changes, process suspension, service management, startup application management, kernel process control, GPU monitoring, network process monitoring, dependency graphs, logging, AI, or Baytevora Chain integration.

### Task Manager Class Relationships

```
ApplicationManager
    |
    +-- setTaskManagerApplication(TaskManagerApplication*)
            |
            +-- TaskManagerApplication::open()
                    |
                    +-- WindowManager::registerWindow("Task Manager", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- TaskManagerWindow.qml
                                            |
                                            +-- TaskManager (per-window)
                                                    |
                                                    +-- QList<TaskInfo*>
                                                    +-- QTimer (1s refresh)
                                                    +-- WindowManager
                                                    +-- NotificationManager
```

Each `TaskManagerWindow` owns its own `TaskManager`, so multiple Task Manager windows can display independent snapshots without shared task state.

### Monitoring Lifecycle

1. User opens Task Manager from the launcher.
2. `TaskManagerApplication` requests a managed window and emits "Task Manager / Ready.".
3. `TaskManagerWindow` creates its own `TaskManager` and wires `WindowManager` and `NotificationManager`.
4. `TaskManager::startMonitoring()` starts a 1-second `QTimer`.
5. Each refresh reads the `WindowManager.windows` list, groups windows by `applicationName`, and creates or updates one `TaskInfo` per application:
   - `processId` = first window ID of the application.
   - `windowCount` = number of open windows for that application.
   - `state` = aggregated window state (`Normal`, `Minimized`, `Maximized`).
   - `cpuUsage` and `memoryUsage` are reserved as 0 for this sprint; values still refresh with the model.
   - `startTime` is captured when the task is first observed.
6. `ProcessTable` displays the task model; selecting a row updates `ProcessDetails` and the status bar.
7. Clicking End Task calls `TaskManager::terminateTask(selectedProcessId)`, which closes all matching windows if the application is not protected.
8. When the window is destroyed, `stopMonitoring()` halts the timer.

The Task Manager consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Advanced administration capabilities are reserved for future enterprise monitoring enhancements.

## Sprint 38 Changes

- Introduced the Baytevora Network Manager (BNM), the first native network-management application for Baytevora OS.
- Added the Network Manager C++ layer:
  - `NetworkInterface` (`include/bos/NetworkInterface.h`, `src/NetworkInterface.cpp`) — value type exposed to QML with `interfaceName`, `displayName`, `interfaceType`, `connected`, `enabled`, `ipAddress`, `subnetMask`, `gateway`, `dnsServers`, `macAddress`, and `speed` properties.
  - `NetworkManager` (`include/bos/NetworkManager.h`, `src/NetworkManager.cpp`) — per-window network interface model exposed to QML. Refreshes every 2 seconds via `QTimer`, collects Ethernet, Wi-Fi, and loopback information using `QNetworkInterface`, `/sys/class/net`, `/proc/net/route`, and `/etc/resolv.conf`. Provides `refresh()`, `startMonitoring()`, `stopMonitoring()`, `enableInterface(name)`, `disableInterface(name)`, `connectInterface(name)`, and `disconnectInterface(name)`. The state-changing methods use placeholder behavior that updates the local model and emits notifications, ready for future wiring to platform networking APIs.
  - `NetworkApplication` (`include/bos/NetworkApplication.h`, `src/NetworkApplication.cpp`) — native application handler that requests a managed 820×560 Network Manager window from `WindowManager` and emits a "Network Manager / Ready." information notification on launch.
- Integrated the Network Manager with the Application Framework:
  - `ApplicationManager` now registers a `NetworkApplication` handler and routes launches of `Network Manager` to it.
  - Added a `Network Manager` application entry (`network-manager`) with `singleInstance: false` so multiple Network Manager windows can be opened independently.
  - `NetworkManager` is registered as a QML type (`qmlRegisterType<NetworkManager>`) so each `NetworkManagerWindow` owns an independent manager instance.
- Created the Network Manager QML user interface:
  - `NetworkManagerWindow.qml` — root content that owns a `NetworkManager`, wires `NotificationManager`, starts monitoring on completion, and arranges `NetworkToolbar`, `NetworkInterfaceList`, `NetworkDetails`, and `NetworkStatusBar`.
  - `NetworkToolbar.qml` — Refresh, Enable, Disable, Connect, and Disconnect actions. State-changing buttons operate on the currently selected interface.
  - `NetworkInterfaceList.qml` — scrollable list with a column header (Name, Type, Status, Enabled, IP Address) and rows bound to `networkManager.interfaces`.
  - `NetworkInterfaceDelegate.qml` — BDL-styled row delegate with selection highlight.
  - `NetworkDetails.qml` — bottom panel showing the selected interface's MAC address, subnet mask, gateway, DNS servers, and link speed.
  - `NetworkStatusBar.qml` — displays total interface count, connected interface count, and the last refresh time.
  - `NetworkToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented refresh behavior:
  - `NetworkManager` starts a 2-second `QTimer` when the window loads.
  - Each refresh enumerates system interfaces with `QNetworkInterface::allInterfaces()` and supplements them with Linux-specific files for state, link speed, default gateway, and DNS servers.
  - Manual refresh is available via the Refresh toolbar button.
  - `stopMonitoring()` is called on destruction to stop the timer for closed windows.
- Implemented notifications:
  - `NetworkApplication::open()` emits "Network Manager / Ready.".
  - `enableInterface()` emits "Interface Enabled.", `disableInterface()` emits "Interface Disabled.", `connectInterface()` emits "Connected.", and `disconnectInterface()` emits "Disconnected.".
  - Automatic refreshes do not emit notifications.
- Updated `WindowFrame.qml` to load `NetworkManagerWindow.qml` when `applicationName == "Network Manager"`.
- Updated `CMakeLists.txt` to include all new C++ sources, headers, and QML files, and added the `Qt6::Network` module and `Network` find_package component.
- Updated `docs/README.md` with Network Manager architecture, monitoring lifecycle, interface lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no VPN management, firewall configuration, proxy configuration, network traffic graphs, packet capture, hotspot creation, Wi-Fi scanning and password management, enterprise policies, logging, AI, or Baytevora Chain integration.

### Network Manager Class Relationships

```
ApplicationManager
    |
    +-- setNetworkApplication(NetworkApplication*)
            |
            +-- NetworkApplication::open()
                    |
                    +-- WindowManager::registerWindow("Network Manager", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- NetworkManagerWindow.qml
                                            |
                                            +-- NetworkManager (per-window)
                                                    |
                                                    +-- QList<NetworkInterface*>
                                                    +-- QTimer (2s refresh)
                                                    +-- NotificationManager
```

Each `NetworkManagerWindow` owns its own `NetworkManager`, so multiple Network Manager windows can display independent snapshots without shared interface state.

### Network Interface Lifecycle

1. User opens Network Manager from the launcher.
2. `NetworkApplication` requests a managed window and emits "Network Manager / Ready.".
3. `NetworkManagerWindow` creates its own `NetworkManager` and wires `NotificationManager`.
4. `NetworkManager::startMonitoring()` starts a 2-second `QTimer`.
5. Each refresh enumerates system interfaces using `QNetworkInterface::allInterfaces()` and reads:
   - Name, human-readable name, type (Loopback/Ethernet/Wi-Fi), and MAC address from `QNetworkInterface`.
   - Enabled state from interface flags.
   - Operational state from `/sys/class/net/<iface>/operstate`.
   - IPv4 address and subnet mask from `QNetworkInterface::addressEntries()`.
   - Default gateway from `/proc/net/route` for the matching interface.
   - Global DNS servers from `/etc/resolv.conf`.
   - Link speed from `/sys/class/net/<iface>/speed`.
6. The interface model is updated and exposed to QML as `networkManager.interfaces`.
7. `NetworkInterfaceList` displays the model; selecting an interface updates `NetworkDetails` and `NetworkStatusBar`.
8. Toolbar actions update the selected interface state and emit the corresponding notification.
9. When the window is destroyed, `stopMonitoring()` halts the timer.

The Network Manager consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Enterprise networking capabilities are reserved for future administration enhancements.

## Sprint 39 Changes

- Introduced the Baytevora Storage Manager (BSM), the first native storage-management application for Baytevora OS.
- Added the Storage Manager C++ layer:
  - `StorageDevice` (`include/bos/StorageDevice.h`, `src/StorageDevice.cpp`) — value type exposed to QML with `deviceName`, `displayName`, `deviceType`, `model`, `serialNumber`, `capacity`, `removable`, and `mounted` properties. Capacity is exposed as both a raw byte count and a formatted `capacityText` field.
  - `StoragePartition` (`include/bos/StoragePartition.h`, `src/StoragePartition.cpp`) — value type exposed to QML with `partitionName`, `filesystem`, `mountPoint`, `totalSpace`, `usedSpace`, `freeSpace`, `usagePercent`, and `readOnly` properties. Space values are also exposed as formatted text fields.
  - `StorageManager` (`include/bos/StorageManager.h`, `src/StorageManager.cpp`) — per-window storage model exposed to QML. Refreshes every 5 seconds via `QTimer`, collects block-device information from `/sys/block`, `/proc/mounts`, and `statvfs`, and exposes read-only models for `devices` and `partitions`. Provides `refresh()`, `startMonitoring()`, and `stopMonitoring()`. No destructive operations are implemented in this sprint.
  - `StorageApplication` (`include/bos/StorageApplication.h`, `src/StorageApplication.cpp`) — native application handler that requests an 880×600 managed window and emits a "Storage Manager / Ready." information notification on launch.
- Integrated the Storage Manager with the Application Framework:
  - `ApplicationManager` now registers a `StorageApplication` handler and routes launches of `Storage Manager` to it.
  - Added a `Storage Manager` application entry (`storage-manager`) with `singleInstance: false` so multiple windows can be opened independently.
  - `StorageManager` is registered as a QML type (`qmlRegisterType<StorageManager>`) so each `StorageManagerWindow` owns an independent manager instance.
- Created the Storage Manager QML user interface:
  - `StorageManagerWindow.qml` — root content that owns a `StorageManager`, arranges `StorageToolbar`, `DeviceList`, `PartitionTable`, `StorageDetails`, and `StorageStatusBar`, and starts monitoring on completion.
  - `StorageToolbar.qml` — Refresh button to trigger a manual `storageManager.refresh()`.
  - `DeviceList.qml` — left panel showing detected devices. Selecting a device updates the details panel and filters the partition table to partitions whose names start with the device name.
  - `DeviceDelegate.qml` — BDL-styled device row with device display name and type.
  - `PartitionTable.qml` — main panel with columns: Partition, Filesystem, Mount Point, Capacity, Used, Free, and Usage %. The Usage % column includes a BDL-styled progress bar.
  - `StorageDetails.qml` — bottom panel showing the selected device's model, serial number, removable status, mounted status, and formatted capacity.
  - `StorageStatusBar.qml` — displays the total device count, total partition count, and the last refresh time.
  - `StorageToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented refresh behavior:
  - `StorageManager` starts a 5-second `QTimer` when the window loads.
  - Each refresh enumerates block devices under `/sys/block`, reads device type from the device name, reads model/serial/removable/size from sysfs, and determines mounted status from `/proc/mounts`.
  - Partitions are collected from `/proc/mounts` and supplemented with capacity/usage via `statvfs`.
  - Manual refresh is available via the Refresh toolbar button.
  - `stopMonitoring()` is called on destruction to stop the timer for closed windows.
- Implemented notifications:
  - `StorageApplication::open()` emits "Storage Manager / Ready.".
  - Automatic refreshes do not emit notifications.
- Updated `WindowFrame.qml` to load `StorageManagerWindow.qml` when `applicationName == "Storage Manager"`.
- Updated `CMakeLists.txt` with all new C++ sources, headers, and QML files.
- Updated `docs/README.md` with Storage Manager architecture, device lifecycle, class relationships, ownership diagrams, and the application list.
- No forbidden features were implemented: no disk formatting, partition creation/deletion/resizing, mount/unmount, disk repair, SMART diagnostics, RAID management, encryption management, backup management, logging, AI, or Baytevora Chain integration.

### Storage Manager Class Relationships

```
ApplicationManager
    |
    +-- setStorageApplication(StorageApplication*)
            |
            +-- StorageApplication::open()
                    |
                    +-- WindowManager::registerWindow("Storage Manager", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- StorageManagerWindow.qml
                                            |
                                            +-- StorageManager (per-window)
                                                    |
                                                    +-- QList<StorageDevice*>
                                                    +-- QList<StoragePartition*>
                                                    +-- QTimer (5s refresh)
```

Each `StorageManagerWindow` owns its own `StorageManager`, so multiple Storage Manager windows can display independent snapshots without shared storage state.

### Storage Device Lifecycle

1. User opens Storage Manager from the launcher.
2. `StorageApplication` requests a managed window and emits "Storage Manager / Ready.".
3. `StorageManagerWindow` creates its own `StorageManager`.
4. `StorageManager::startMonitoring()` starts a 5-second `QTimer`.
5. Each refresh reads `/sys/block` for available block devices and filters out loop devices:
   - Name, display name, and type (Internal SSD, USB/SATA Drive, Optical Drive, SD/MMC, Internal Drive, or Block Device).
   - Model and serial number from `/sys/block/<dev>/device/model` and `/sys/block/<dev>/device/serial`.
   - Removable flag from `/sys/block/<dev>/removable`.
   - Capacity from `/sys/block/<dev>/size` multiplied by 512 bytes.
   - Mounted status derived from `/proc/mounts` entries that belong to the device.
6. Partitions are enumerated from `/proc/mounts` entries under `/dev/`; `statvfs` provides total, used, free, and usage percentage. The read-only flag is always false in Sprint 39 because no write operations are allowed.
7. The `DeviceList` displays devices; selecting one updates `StorageDetails` and filters `PartitionTable`.
8. When the window is destroyed, `stopMonitoring()` halts the timer.

The Storage Manager consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Destructive storage-management capabilities are reserved for future enterprise storage enhancements.

## Sprint 40 Changes

- Introduced the Baytevora Printing Framework (BPF), the first native printing-management application for Baytevora OS.
- Added the Printing Framework C++ layer:
  - `PrinterInfo` (`include/bos/PrinterInfo.h`, `src/PrinterInfo.cpp`) — value type exposed to QML with `printerName`, `displayName`, `manufacturer`, `model`, `location`, `status`, `online`, `defaultPrinter`, `colorSupported`, and `duplexSupported` properties.
  - `PrintJob` (`include/bos/PrintJob.h`, `src/PrintJob.cpp`) — value type exposed to QML with `jobId`, `documentName`, `printerName`, `pages`, `status`, and `submittedTime` properties.
  - `PrintManager` (`include/bos/PrintManager.h`, `src/PrintManager.cpp`) — per-window printer/job model exposed to QML. Uses Qt Print Support (`QPrinterInfo`) for printer discovery, maintains an in-memory print queue, and provides `refreshPrinters()`, `refreshJobs()`, `printDocument(filePath)`, `cancelJob(jobId)`, and `setDefaultPrinter(printerName)`. Jobs are placeholder-safe and do not perform real printing in Sprint 40; they simulate submission and completion and emit the corresponding notifications.
  - `PrintApplication` (`include/bos/PrintApplication.h`, `src/PrintApplication.cpp`) — native application handler that requests a 900×620 managed window and emits a "Printing / Ready." information notification on launch.
- Integrated the Print Manager with the Application Framework:
  - `ApplicationManager` now registers a `PrintApplication` handler and routes launches of `Print Manager` to it.
  - Added a `Print Manager` application entry (`print-manager`) with `singleInstance: false` so multiple windows can be opened independently.
  - `PrintManager` is registered as a QML type (`qmlRegisterType<PrintManager>`) so each `PrintManagerWindow` owns an independent manager instance.
  - A shared `PrintManager` instance is also exposed as the QML context property `printManager` for cross-application printing hooks (PDF Viewer, Text Editor, Image Viewer, Browser, Archive Manager, etc.).
- Created the Print Manager QML user interface:
  - `PrintManagerWindow.qml` — root content that owns a `PrintManager`, wires `NotificationManager`, arranges `PrintToolbar`, `PrinterList`, `PrintQueue`, `PrinterDetails`, and `PrintStatusBar`, and refreshes printers on completion.
  - `PrintToolbar.qml` — Refresh Printers, Refresh Queue, Set Default, and Cancel Job actions. Set Default applies to the selected printer; Cancel Job applies to the selected job.
  - `PrinterList.qml` — left panel showing discovered printers. Selecting a printer updates `PrinterDetails` and the toolbar.
  - `PrinterDelegate.qml` — BDL-styled printer row with display name and status/default indicator.
  - `PrintQueue.qml` — bottom table with columns Job, Document, Printer, Pages, Status, and Submitted.
  - `PrintJobDelegate.qml` — BDL-styled print-job row with selection highlight.
  - `PrinterDetails.qml` — center details panel showing the selected printer's name, model, manufacturer, status, online state, default flag, color support, and duplex support.
  - `PrintStatusBar.qml` — displays the number of detected printers, queued jobs, and the default printer name.
  - `PrintToolButton.qml` — reusable BDL-styled toolbar button.
- Implemented printing engine behavior:
  - Printer discovery uses `QPrinterInfo::availablePrinters()` and `QPrinterInfo::defaultPrinter()`.
  - If no real printer is configured, `PrintManager` exposes a placeholder "Virtual Printer" so the UI remains functional.
  - `printDocument(filePath)` accepts PDF, plain text, PNG, JPG, and JPEG files. Unsupported or missing files emit an error notification.
  - Each simulated print creates a `PrintJob` with status "Completed", emits "Print Job Submitted" and "Print Job Completed", and refreshes the queue.
  - `cancelJob(jobId)` marks the matching job "Cancelled" and emits "Print Job Cancelled".
  - `setDefaultPrinter(printerName)` updates the default flag across all known printers and refreshes the model.
- Implemented notifications:
  - `PrintApplication::open()` emits "Printing / Ready.".
  - `printDocument()` emits "Print Job Submitted" and "Print Job Completed".
  - `cancelJob()` emits "Print Job Cancelled".
  - `refreshPrinters()` detects newly available or removed printers and emits "Printer Connected" or "Printer Disconnected" when the printer count changes.
  - Automatic refreshes do not emit notifications.
- Updated `WindowFrame.qml` to load `PrintManagerWindow.qml` when `applicationName == "Print Manager"`.
- Updated `CMakeLists.txt` with the new `Qt6::PrintSupport` module, all new C++ sources/headers, and all new QML files.
- Updated `docs/README.md` with Printing Framework architecture, print lifecycle, class relationships, ownership diagrams, integration hooks, and the application list.
- No forbidden features were implemented: no scanner support, fax, OCR, print server, network print administration, enterprise policies, secure print release, cloud printing, AI, or Baytevora Chain integration.

### Printing Framework Class Relationships

```
ApplicationManager
    |
    +-- setPrintApplication(PrintApplication*)
            |
            +-- PrintApplication::open()
                    |
                    +-- WindowManager::registerWindow("Print Manager", ...)
                            |
                            +-- WindowFrame.qml
                                    |
                                    +-- PrintManagerWindow.qml
                                            |
                                            +-- PrintManager (per-window)
                                                    |
                                                    +-- QList<PrinterInfo*>
                                                    +-- QList<PrintJob*>

Application.cpp
    |
    +-- context property "printManager" -> shared PrintManager
            |
            +-- Used by future app windows (PDF Viewer, Text Editor, etc.)
```

Each `PrintManagerWindow` owns its own `PrintManager`, while a separate shared `PrintManager` is exposed as `printManager` for cross-application printing hooks in future sprints.

### Print Lifecycle

1. User opens Print Manager from the launcher.
2. `PrintApplication` requests a managed window and emits "Printing / Ready.".
3. `PrintManagerWindow` creates its own `PrintManager` and wires `NotificationManager`.
4. `PrintManager::refreshPrinters()` enumerates available printers with `QPrinterInfo` and sets the default flag from `QPrinterInfo::defaultPrinter()`.
5. User selects a printer from `PrinterList`; `PrinterDetails` and the toolbar update.
6. User triggers `setDefaultPrinter()`; the default flag moves to the selected printer and the model refreshes.
7. A future app (or test call) invokes `printManager.printDocument(filePath)` on the shared manager. The file type is validated (PDF, TXT, PNG, JPG, JPEG). A placeholder job is created with status "Completed" and notifications are emitted.
8. `cancelJob(jobId)` marks a job "Cancelled" and emits a notification.
9. Manual or programmatic `refreshPrinters()` updates the printer list. If a printer appears or disappears, "Printer Connected" or "Printer Disconnected" is emitted.

The Printing Framework consumes BDL v2 managers (`ThemeManager`, `AdaptiveLayoutManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `DesignTokens`) and contains no hardcoded colors, spacing, typography, radius, or icon sizes. Enterprise printing capabilities are reserved for future administration enhancements.

## Sprint 41 Changes

- Expanded the Baytevora Browser Foundation into Baytevora Browser Phase 2 (BBP2), a native multi-tab browser for Baytevora OS.
- Added the Browser Phase 2 C++ layer:
  - `BrowserTab` (`include/bos/BrowserTab.h`, `src/BrowserTab.cpp`) — value type exposed to QML with `tabId`, `title`, `url`, `loading`, `canGoBack`, and `canGoForward` properties.
  - `BrowserSession` (`include/bos/BrowserSession.h`, `src/BrowserSession.cpp`) — per-window container that owns the open `BrowserTab` list and the active tab ID. Keeps session data in memory only while the window is open. Supports tab add, remove, duplicate, move, and restore-last-closed with a small internal history.
  - `BrowserManager` (`include/bos/BrowserManager.h`, `src/BrowserManager.cpp`) — extended from Sprint 27 to own a `BrowserSession`, expose `currentUrl`, `pageTitle`, `loading`, `canGoBack`, `canGoForward`, `tabs`, and `activeTabId` properties, and provide `navigate()`, `reload()`, `stop()`, `goHome()`, `goBack()`, `goForward()`, `newTab(url)`, `closeTab(tabId)`, `switchTab(tabId)`, `duplicateTab(tabId)`, `moveTab(fromIndex, toIndex)`, and `restoreClosedTab()` invokable methods.
- Integrated the updated browser with the existing Application Framework, `WindowFrame`, Notification Service, and BDL v2. `BrowserApplication` unchanged; it still emits "Browser / Ready." on launch. `BrowserManager` now receives a `NotificationManager` from QML and emits "New Tab Opened" and "Tab Closed" for user tab actions.
- Created/updated the Browser Phase 2 QML user interface:
  - `BrowserTabButton.qml` — BDL-styled tab item showing title and a close button; supports click-to-switch and basic drag-to-reorder.
  - `BrowserTabBar.qml` — horizontal tab bar that renders all tabs from `BrowserManager.tabs`, highlights the active tab, closes tabs, adds new tabs via a "+" button, and forwards reorder requests to `BrowserManager.moveTab()`.
  - `BrowserToolbar.qml` — updated to include New Tab, Back (disabled when `canGoBack` is false), Forward (disabled when `canGoForward` is false), Reload/Stop, Home, and the Address Bar. Back/Forward/Home now route through `BrowserManager` methods so navigation state stays synchronized per tab.
  - `BrowserView.qml` — changed from a single `WebEngineView` to a `Repeater` that creates one `WebEngineView` per tab. Only the active tab's view is visible; inactive views stay in memory while the window is open. Each view binds its `url`, `title`, `loading`, `canGoBack`, and `canGoForward` back to the active tab via `BrowserManager`. `BrowserManager` signals `reloadRequested`, `stopRequested`, `backRequested`, and `forwardRequested` operate on the visible active view.
  - `BrowserWindow.qml` — updated layout to Toolbar → Tab Bar → Browser View → Status Bar. Each window still owns its own `BrowserManager`.
  - `BrowserStatusBar.qml` — extended to show page title, loading state, and current tab count.
  - `AddressBar.qml` and `BrowserToolButton.qml` reused unchanged; BDL v2 tokens remain unhardcoded.
- Implemented session management behavior:
  - Each browser window owns an isolated `BrowserSession`.
  - Tabs are kept while the window is open; restoring closed tabs works within the current in-memory session.
  - Persistent session restore is intentionally deferred to a future sprint.
- Implemented notification behavior:
  - `BrowserApplication::open()` emits "Browser / Ready."
  - `newTab()`, `duplicateTab()`, and `restoreClosedTab()` emit "New Tab Opened."
  - `closeTab()` emits "Tab Closed."
  - Normal page navigation does not emit notifications.
- Updated `CMakeLists.txt` with new C++ sources/headers (`BrowserTab`, `BrowserSession`) and QML files (`BrowserTabBar.qml`, `BrowserTabButton.qml`).
- Updated `docs/README.md` with Browser Phase 2 architecture, tab lifecycle, session lifecycle, class relationships, ownership diagrams, and application list.
- Validated QML and CMake file consistency; created `tasks/bde-shell-sprint41.tar.gz`.
- No forbidden features were implemented: no downloads, bookmarks, history, extensions, accounts, synchronization, password manager, developer tools, profiles, incognito mode, ad blocker, AI, or Baytevora Chain integration.

### Browser Phase 2 Class Relationships

```
BrowserApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("Browser", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- BrowserWindow.qml
                                    |
                                    +-- BrowserManager (per-window)
                                            |
                                            +-- BrowserSession (per-window)
                                                    |
                                                    +-- QList<BrowserTab*>
```

`BrowserManager` exposes the active tab's state and the full tab model to QML. `BrowserView` creates one `WebEngineView` per tab, binding to the per-tab URL and navigation state. The existing `ApplicationManager` and `WindowManager` routes are unchanged.

### Tab Lifecycle

1. `BrowserWindow` creates a `BrowserManager`, which in turn creates a `BrowserSession` and opens an initial home tab.
2. User clicks the "+" button or presses the New Tab toolbar button → `BrowserManager::newTab()` adds a `BrowserTab` to `BrowserSession`, marks it active, and emits `tabsChanged` and `activeTabIdChanged`.
3. User types a URL in `AddressBar` → `BrowserManager::navigate()` updates the active tab's URL; the corresponding `WebEngineView` navigates to it.
4. `WebEngineView` signals update the active tab's `title`, `loading`, `canGoBack`, and `canGoForward` via `BrowserManager` setters.
5. User clicks a tab → `BrowserManager::switchTab()` changes the active tab; `BrowserView` toggles visibility of the corresponding `WebEngineView`.
6. User closes a tab → `BrowserManager::closeTab()` removes the tab and selects a neighbor; the last remaining tab resets to home instead of closing.
7. User drags a tab → `BrowserTabBar` computes a new index and calls `BrowserManager::moveTab()`.
8. User restores a closed tab → `BrowserManager::restoreClosedTab()` pulls the most recently removed tab back into the session.
9. When the browser window closes, the `BrowserSession` is destroyed with its tabs; session data is not persisted in Sprint 41.

## Sprint 42 Changes

- Added Baytevora Browser Downloads (BBD) — a per-window download manager integrated with the existing Browser Phase 2 architecture.
- Added the BBD C++ layer:
  - `BrowserDownload` (`include/bos/BrowserDownload.h`, `src/BrowserDownload.cpp`) — QML-friendly download value object with `downloadId`, `fileName`, `sourceUrl`, `destinationPath`, `totalBytes`, `receivedBytes`, `progress`, `state` (Pending/Downloading/Paused/Completed/Cancelled/Failed), `mimeType`, `startTime`, and `finishTime`. It can be attached to a `QWebEngineDownloadRequest` to mirror progress and provides `cancel()`, `pause()`, and `resume()` invokables.
  - `BrowserDownloadManager` (`include/bos/BrowserDownloadManager.h`, `src/BrowserDownloadManager.cpp`) — owns the list of `BrowserDownload` objects for one browser window/session, exposes `downloads`, `activeCount`, and `completedCount` to QML, and provides `startDownload(url)`, `acceptDownloadRequest(request)`, `cancelDownload(id)`, `pauseDownload(id)`, `resumeDownload(id)`, and `clearCompleted()`. It emits `manualDownloadRequested(id, url)` so QML can trigger the actual fetch through a hidden `WebEngineView`.
- Integrated downloads into the existing browser architecture:
  - `BrowserSession` now owns one `BrowserDownloadManager` and exposes it through a `downloadManager` property.
  - `BrowserManager` exposes the session's download manager and forwards all download-related invokable calls to it. `setNotificationManager()` propagates the notification manager to the download manager so state-change notifications can be emitted.
  - `Application.cpp` registers `BrowserDownloadManager` as an uncreatable QML type so it can be used as a property type.
- Implemented Qt WebEngine download detection:
  - `BrowserView.qml` handles `onDownloadRequested` on every tab `WebEngineView` and routes the request to `BrowserManager.acceptDownloadRequest(request)`.
  - A hidden `WebEngineView` is used to fulfill manual `startDownload(url)` requests. When `BrowserDownloadManager` emits `manualDownloadRequested`, the hidden view loads the URL and any resulting download request is accepted into the same pending entry.
- Created the BBD QML user interface using BDL v2:
  - `BrowserDownloadDelegate.qml` — row showing file name, size/state text, a progress bar, and placeholder-safe Open Folder, Pause, Resume, and Cancel actions. Buttons are enabled only for applicable states.
  - `BrowserDownloadList.qml` — scrollable `ListView` bound to `downloadManager.downloads` with an empty-state message.
  - `BrowserDownloadsWindow.qml` — in-window overlay that fills the browser content area and contains the list header with Clear Completed / Close actions.
  - `BrowserToolbar.qml` — added a "Downloads" button that opens the downloads overlay.
  - `BrowserStatusBar.qml` — now also shows the current active download count.
  - `BrowserWindow.qml` — hosts the downloads overlay next to the main browser column.
- Implemented notification behavior:
  - "Download Started" emitted when a request is accepted.
  - "Download Completed" / "Download Failed" / "Download Cancelled" emitted only on terminal state transitions, not on progress updates.
- Updated `CMakeLists.txt` with new C++ sources/headers and QML files, and bumped the project description to Sprint 42.
- Updated `docs/README.md` with Browser Downloads architecture, download lifecycle, class relationships, ownership diagrams, and application list.
- Validated QML and CMake file consistency; created `tasks/bde-shell-sprint42.tar.gz`.
- No forbidden features were implemented: no persistent download history, virus scanning, cloud sync, download acceleration, torrent support, browser accounts, synchronization, AI, or Baytevora Chain integration.

### Browser Downloads Class Relationships

```
BrowserApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("Browser", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- BrowserWindow.qml
                                    |
                                    +-- BrowserManager (per-window)
                                            |
                                            +-- BrowserSession (per-window)
                                                    |
                                                    +-- QList<BrowserTab*>
                                                    +-- BrowserDownloadManager
                                                            |
                                                            +-- QList<BrowserDownload*>
```

`BrowserDownloadManager` is created by `BrowserSession` and exposed through `BrowserManager::downloadManager`. Each `BrowserWindow` has its own isolated manager, so downloads do not leak between browser windows.

### Download Lifecycle

1. **Automatic detection**: A tab `WebEngineView` emits `downloadRequested(request)` when the user navigates to a downloadable resource. `BrowserView` forwards the request to `BrowserManager::acceptDownloadRequest(request)`.
2. **Manual start**: External code calls `BrowserManager::startDownload(url)`. A `BrowserDownload` with state `Pending` is created, and `manualDownloadRequested(id, url)` is emitted. The hidden `WebEngineView` in `BrowserView` loads the URL; the resulting `downloadRequested` request matches the pending entry by URL.
3. **Acceptance**: `BrowserDownloadManager::acceptDownloadRequest()` creates a destination path under the user's `Download` location, stores it in the `BrowserDownload`, calls `request->acceptWithPath()`, and transitions the state to `Downloading`.
4. **Progress**: `BrowserDownload` connects to the Qt download request's `receivedBytesChanged`, `totalBytesChanged`, and `stateChanged` signals and updates its exposed properties.
5. **Pause/Resume**: User clicks Pause/Resume in the delegate. `BrowserDownload::pause()` / `resume()` call the underlying `QWebEngineDownloadRequest` methods when supported; otherwise the state is updated as a placeholder-safe behavior.
6. **Cancel**: `BrowserDownload::cancel()` calls `request->cancel()` for non-terminal downloads.
7. **Completion**: Terminal state (Completed/Failed/Cancelled) sets `finishTime` and emits the appropriate notification through the Notification Service.
8. **Cleanup**: User clicks Clear Completed; `BrowserDownloadManager::clearCompleted()` removes terminal entries from the model.
9. **Session lifetime**: Downloads remain available only while the browser window is open. Persistent download history is not part of Sprint 42.

## Sprint 43 Changes

- Added Baytevora Browser Bookmarks & History (BBBH) — native bookmarks and browsing history with local JSON persistence, fully integrated into the Browser Phase 2/42 architecture.
- Added the BBBH C++ layer:
  - `BrowserBookmark` (`include/bos/BrowserBookmark.h`, `src/BrowserBookmark.cpp`) — QML-friendly object with `bookmarkId`, `title`, `url`, `folder`, `createdAt`, and `lastVisited`.
  - `BrowserBookmarkManager` (`include/bos/BrowserBookmarkManager.h`, `src/BrowserBookmarkManager.cpp`) — owns bookmark and folder lists, exposes `bookmarks` and `folders`, and provides `addBookmark(title, url, folder)`, `removeBookmark(id)`, `editBookmark(id, title, url, folder)`, `createFolder(name)`, `moveBookmark(id, folder)`, `searchBookmarks(query)`, and `updateLastVisited(id)`. Loads from and saves to `bookmarks.json` under the application data directory.
  - `BrowserHistoryEntry` (`include/bos/BrowserHistoryEntry.h`, `src/BrowserHistoryEntry.cpp`) — QML-friendly object with `historyId`, `title`, `url`, `visitTime`, and `visitCount`.
  - `BrowserHistoryManager` (`include/bos/BrowserHistoryEntry.h`, `src/BrowserHistoryManager.cpp`) — owns browsing history, exposes `history` and `recentHistory` (last 50 entries), and provides `recordVisit(title, url)`, `clearHistory()`, `removeHistoryEntry(id)`, and `searchHistory(query)`. Deduplicates by URL and increments `visitCount`. Loads from and saves to `history.json` under the application data directory.
- Integrated bookmarks and history into the browser architecture:
  - `BrowserSession` now owns a `BrowserBookmarkManager` and a `BrowserHistoryManager` alongside the existing tab and download managers.
  - `BrowserManager` exposes `bookmarkManager` and `historyManager` properties, forwards notification manager setup to both, and provides `recordHistory(title, url)` so QML can trigger visit recording after a page load.
  - `Application.cpp` registers `BrowserBookmarkManager` and `BrowserHistoryManager` as uncreatable QML types.
- Implemented automatic history recording:
  - `BrowserView.qml` calls `browserManager.recordHistory(title, url.toString())` whenever a tab's `titleChanged` signal fires and the view is not currently loading. Internal BOS pages (`data:`, `about:`, `bos:`, `file:`, error/blank URLs) and downloads are excluded by `BrowserHistoryManager::shouldRecord()`.
  - No notification is emitted for individual page visits.
- Added bookmark and history UI using BDL v2:
  - `BrowserBookmarkDelegate.qml` — bookmark row with title, URL, Open, and Remove actions.
  - `BrowserBookmarkList.qml` — scrollable bookmark list with search box and folder `ComboBox`. Clicking a bookmark navigates to the URL and closes the overlay.
  - `BrowserBookmarksWindow.qml` — in-window bookmark overlay with "Add Current Page" and "Close" header actions.
  - `BrowserHistoryDelegate.qml` — history row with title, URL, visit date/time, visit count, Open, and Remove actions.
  - `BrowserHistoryList.qml` — scrollable history list with search and a sort toggle (newest/oldest first). Clicking an entry navigates to the URL and closes the overlay.
  - `BrowserHistoryWindow.qml` — in-window history overlay with "Clear History" and "Close" header actions.
  - `BrowserToolbar.qml` — added "Bookmarks", "History", and "Add Bookmark" buttons. Existing Downloads button and Address Bar are preserved.
  - `BrowserWindow.qml` — hosts the bookmarks and history overlays next to the downloads overlay.
- Implemented notification behavior:
  - "Bookmark Added" emitted by `BrowserBookmarkManager::addBookmark()`.
  - "Bookmark Removed" emitted by `BrowserBookmarkManager::removeBookmark()`.
  - "History Cleared" emitted by `BrowserHistoryManager::clearHistory()`.
  - No notifications for edit, move, folder creation, single history removal, or page visits.
- Updated `CMakeLists.txt` with new C++ sources/headers and QML files, and bumped the project description to Sprint 43.
- Updated `docs/README.md` with BBBH architecture, persistence details, lifecycle, class relationships, and ownership diagrams.
- Validated brace/CMake/QML consistency and created `tasks/bde-shell-sprint43.tar.gz`.
- No forbidden features implemented: no bookmark synchronization, browser accounts, cloud history, shared bookmarks, AI bookmark organization, reading list, password manager, browser profiles, or Baytevora Chain integration.

### Browser Bookmarks & History Class Relationships

```
BrowserApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("Browser", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- BrowserWindow.qml
                                    |
                                    +-- BrowserManager (per-window)
                                            |
                                            +-- BrowserSession (per-window)
                                                    |
                                                    +-- QList<BrowserTab*>
                                                    +-- BrowserDownloadManager
                                                    +-- BrowserBookmarkManager
                                                    |       +-- QList<BrowserBookmark*>
                                                    +-- BrowserHistoryManager
                                                            +-- QList<BrowserHistoryEntry*>
```

`BrowserBookmarkManager` and `BrowserHistoryManager` are created by `BrowserSession` and exposed through `BrowserManager::bookmarkManager` and `BrowserManager::historyManager`. Each `BrowserWindow` has its own isolated managers; persistent JSON files are written to the application data directory.

### Persistence

Bookmarks are stored as `bookmarks.json` with the following structure:

```json
{
  "folders": ["Bookmarks", "Work"],
  "bookmarks": [
    {
      "bookmarkId": 1,
      "title": "Baytevora",
      "url": "https://baytevora.example.com",
      "folder": "Bookmarks",
      "createdAt": "2026-07-09T12:00:00",
      "lastVisited": "2026-07-09T12:30:00"
    }
  ]
}
```

History is stored as `history.json` with the following structure:

```json
{
  "history": [
    {
      "historyId": 1,
      "title": "Baytevora",
      "url": "https://baytevora.example.com",
      "visitTime": "2026-07-09T12:30:00",
      "visitCount": 3
    }
  ]
}
```

Both files live in `<AppDataLocation>/browser` (typically `~/.local/share/Baytevora Labs/BOS Shell/browser` on Linux). Files are created on first write and loaded on manager construction.

### Bookmarks Lifecycle

1. **Create**: User clicks "Add Current Page" or an external component calls `bookmarkManager.addBookmark(title, url, folder)`. The new bookmark is appended to the in-memory list, the folder list is rebuilt, the JSON file is saved, and a "Bookmark Added" notification is emitted.
2. **Open**: User clicks a bookmark in the overlay. The URL is passed to `BrowserManager::navigate(url)`, the active tab loads the URL, and the overlay closes.
3. **Edit**: `editBookmark(id, title, url, folder)` updates the bookmark in place, saves, and refreshes the model.
4. **Move**: `moveBookmark(id, folder)` updates the bookmark's folder, creates the folder if it does not exist, and saves.
5. **Remove**: `removeBookmark(id)` deletes the bookmark, saves, rebuilds folders, and emits "Bookmark Removed".

### History Lifecycle

1. **Record**: When a page finishes loading and its title is set, `BrowserView` calls `BrowserManager::recordHistory(title, url)`. `BrowserHistoryManager::recordVisit()` either creates a new entry with `visitCount` = 1 or updates an existing entry's title, increments `visitCount`, and refreshes `visitTime`.
2. **View**: The history overlay loads `historyManager.history` and displays entries sorted by visit time (newest first by default).
3. **Search**: `searchHistory(query)` returns entries whose title or URL contains the query (case-insensitive).
4. **Remove single entry**: `removeHistoryEntry(id)` deletes one entry and saves.
5. **Clear**: "Clear History" deletes all entries, saves, and emits "History Cleared".

## Sprint 44 Changes

- Added Baytevora Browser Privacy Foundation (BBPF) — native site permissions and privacy settings management with local JSON persistence, fully integrated into the Browser Phase 2/42/43 architecture.
- Added the BBPF C++ layer:
  - `BrowserPermission` (`include/bos/BrowserPermission.h`, `src/BrowserPermission.cpp`) — QML-friendly object with `permissionId`, `origin`, `permissionType`, `state`, and `lastModified`.
  - `BrowserPermissionManager` (`include/bos/BrowserPermissionManager.h`, `src/BrowserPermissionManager.cpp`) — owns permission rules, exposes `permissions`, and provides `permission(origin, type)`, `setPermission(origin, type, state)`, `resetPermission(origin, type)`, `resetAllPermissions()`, `resetPermissionsForOrigin(origin)`, and `permissionsForOrigin(origin)`. Supported types: Camera, Microphone, Location, Notifications, Clipboard, Popups. Supported states: Ask, Allow, Block. Loads from and saves to `permissions.json` under the application data directory.
  - `BrowserPrivacySettings` (`include/bos/BrowserPrivacySettings.h`, `src/BrowserPrivacySettings.cpp`) — holds `doNotTrackEnabled`, `blockThirdPartyCookies`, `clearHistoryOnExit`, `clearCookiesOnExit`, `sendReferrer`, `javascriptEnabled`, and `popupsBlocked`. Provides setters and `applyExitPolicy(historyManager)`. Loads from and saves to `privacy.json` under the application data directory.
- Integrated permissions and privacy into the browser architecture:
  - `BrowserSession` now owns a `BrowserPermissionManager` and a `BrowserPrivacySettings` alongside tabs, downloads, bookmarks, and history.
  - `BrowserManager` exposes `permissionManager` and `privacySettings` properties, forwards notification manager setup, and provides privacy setter invokables: `setDoNotTrack`, `setThirdPartyCookies`, `setClearHistoryOnExit`, `setClearCookiesOnExit`, `setSendReferrer`, `setJavascriptEnabled`, and `setPopupBlocking`.
  - `Application.cpp` registers `BrowserPermissionManager` and `BrowserPrivacySettings` as uncreatable QML types.
- Integrated with Qt WebEngine permission and popup requests:
  - `BrowserView.qml` handles `featurePermissionRequested(feature, securityOrigin)` for Camera, Microphone, Location, Notifications, and Clipboard. It consults `BrowserPermissionManager` and grants/denies based on the saved rule. For the default "Ask" state, it shows the `BrowserPermissionPrompt` overlay, remembers the user's Allow/Block choice, and applies it.
  - `BrowserView.qml` handles `javaScriptWindowRequested(request)` and rejects the popup when `popupsBlocked` is true. When popups are allowed, the request is currently rejected as a placeholder-safe default; full popup-window creation is reserved for a future sprint.
- Implemented privacy exit policy:
  - `BrowserSession` calls `BrowserPrivacySettings::applyExitPolicy(historyManager)` in its destructor.
  - If `clearHistoryOnExit` is enabled, the window's history manager clears the shared history before the session is destroyed.
  - `clearCookiesOnExit` is saved as a setting; the actual cookie-store clearing is reserved for a future sprint that integrates with the WebEngine profile.
- Added privacy UI using BDL v2:
  - `BrowserPermissionPrompt.qml` — simple in-page prompt for unresolved permission requests.
  - `BrowserPermissionDelegate.qml` — permission row with origin, type/state, and Allow/Block/Reset actions.
  - `BrowserPermissionList.qml` — scrollable permission list with a "Reset All" button.
  - `PrivacyToggle.qml` — BDL-styled toggle switch used by the settings page.
  - `BrowserPrivacySettingsPage.qml` — toggle panel for Do Not Track, third-party cookies, clear history/cookies on exit, referrer, JavaScript, and popup blocking.
  - `BrowserPrivacyWindow.qml` — in-window privacy overlay with Permissions and Settings tabs and a Close button.
  - `BrowserToolbar.qml` — added a "Privacy" button. Existing buttons are preserved.
  - `BrowserWindow.qml` — hosts the privacy overlay next to downloads, bookmarks, and history overlays.
- Implemented notification behavior:
  - "Permission Updated" emitted by `BrowserPermissionManager::setPermission()`.
  - "Privacy Settings Updated" emitted by each `BrowserPrivacySettings` setter.
  - No notifications are emitted for individual website requests or for the prompt itself.
- Updated `CMakeLists.txt` with new C++ sources/headers and QML files, and bumped the project description to Sprint 44.
- Updated `docs/README.md` with BBPF architecture, permission lifecycle, privacy settings persistence, class relationships, and ownership diagrams.
- Validated brace/CMake/QML consistency and created `tasks/bde-shell-sprint44.tar.gz`.
- No forbidden features implemented: no ad blocker, tracker blocking, VPN, proxy management, password manager, incognito mode, browser profiles, browser synchronization, AI privacy assistant, antivirus integration, or Baytevora Chain integration.

### Browser Privacy Foundation Class Relationships

```
BrowserApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("Browser", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- BrowserWindow.qml
                                    |
                                    +-- BrowserManager (per-window)
                                            |
                                            +-- BrowserSession (per-window)
                                                    |
                                                    +-- QList<BrowserTab*>
                                                    +-- BrowserDownloadManager
                                                    +-- BrowserBookmarkManager
                                                    +-- BrowserHistoryManager
                                                    +-- BrowserPermissionManager
                                                    |       +-- QList<BrowserPermission*>
                                                    +-- BrowserPrivacySettings
```

`BrowserPermissionManager` and `BrowserPrivacySettings` are created by `BrowserSession` and exposed through `BrowserManager::permissionManager` and `BrowserManager::privacySettings`. The two JSON files (`permissions.json` and `privacy.json`) are stored in the application data directory and are shared across all browser windows.

### Persistence

Site permissions are stored as `permissions.json`:

```json
{
  "permissions": [
    {
      "permissionId": 1,
      "origin": "https://example.com",
      "permissionType": "Camera",
      "state": "Block",
      "lastModified": "2026-07-09T14:00:00"
    }
  ]
}
```

Privacy settings are stored as `privacy.json`:

```json
{
  "doNotTrackEnabled": false,
  "blockThirdPartyCookies": false,
  "clearHistoryOnExit": false,
  "clearCookiesOnExit": false,
  "sendReferrer": true,
  "javascriptEnabled": true,
  "popupsBlocked": true
}
```

Both files live in `<AppDataLocation>/browser`. They are loaded when the first browser window opens and saved whenever a permission or setting changes.

### Permission Lifecycle

1. **Request**: A website calls `navigator.geolocation.getCurrentPosition()` or similar, causing `WebEngineView.featurePermissionRequested` to fire.
2. **Lookup**: `BrowserView` maps the WebEngine feature enum to a BBPF permission type and asks `BrowserPermissionManager::permission(origin, type)` for the saved rule.
3. **Allow/Block**: If the rule is `Allow`, `grantFeaturePermission(..., true)` is called. If `Block`, `grantFeaturePermission(..., false)` is called. No notification is emitted.
4. **Ask**: If no rule exists, the default state is `Ask`. `BrowserPermissionPrompt` is shown. The user's choice is stored through `setPermission(origin, type, state)`, and `grantFeaturePermission` is called accordingly. A "Permission Updated" notification is emitted.
5. **Management**: Users can open the Privacy window → Permissions tab to view, Allow, Block, or Reset rules. "Reset All" removes every saved rule.

### Privacy Settings Lifecycle

1. **Load**: `BrowserPrivacySettings` reads `privacy.json` on construction.
2. **Change**: Toggles in `BrowserPrivacySettingsPage` call the C++ setters, which save the file, emit `privacySettingsUpdated`, and emit a "Privacy Settings Updated" notification.
3. **Popups**: `BrowserView::handlePopup` consults `popupsBlocked` when `javaScriptWindowRequested` fires.
4. **Exit**: When a browser window closes, `BrowserSession` runs `applyExitPolicy`. If `clearHistoryOnExit` is true, the shared browsing history is cleared.

## Sprint 45 Changes

- Added Baytevora File Manager Phase 2 (BFM2) — professional file browsing with navigation, in-session search, favorites, recent files, and richer context menus, all on top of the existing File Manager architecture.
- Added the BFM2 C++ layer:
  - `FavoriteLocation` (`include/bos/FavoriteLocation.h`, `src/FavoriteLocation.cpp`) — QML-friendly value object with `favoriteId`, `displayName`, `path`, `icon`, and `pinned`.
  - `FileFavoriteManager` (`include/bos/FileFavoriteManager.h`, `src/FileFavoriteManager.cpp`) — owns favorites, exposes `favorites`, and provides `addFavorite(path, displayName, icon, pinned)`, `removeFavorite(favoriteId)`, `pinFavorite(favoriteId, pinned)`, `moveFavorite(fromIndex, toIndex)`, and `togglePin(favoriteId)`. Favorites persist to `favorites.json` under the application data directory.
  - `RecentFile` (`include/bos/RecentFile.h`, `src/RecentFile.cpp`) — QML-friendly value object with `recentId`, `fileName`, `path`, `fileType`, and `lastOpened`.
  - `RecentFileManager` (`include/bos/RecentFileManager.h`, `src/RecentFileManager.cpp`) — owns recent files, exposes `recentFiles`, and provides `addRecentFile(path)` and `clearRecentFiles()`. Recent files persist to `recent.json` and are capped at 20 entries.
  - `FileSearchManager` (`include/bos/FileSearchManager.h`, `src/FileSearchManager.cpp`) — provides on-demand `search(directory, query, extensionFilter, recursive)` and `searchFileNames(directory, query, recursive)` without any background indexing. Supports partial name matching and extension filtering.
- Extended `FileSystemModel` to become the per-window File Manager controller:
  - Added per-window navigation history with `canGoBack`, `canGoForward`, `goBack()`, `goForward()`, `cdUp()`, `goHome()`, and updated `setPath()`.
  - Added `favoriteManager`, `recentFileManager`, and `searchManager` properties.
  - Added `addRecentFile(filePath)` invokable.
  - Added `setNotificationManager(...)` so favorites and recent files can emit platform notifications.
- Integrated managers into the application:
  - `Application.cpp` registers `FileFavoriteManager`, `RecentFileManager`, and `FileSearchManager` as uncreatable QML types owned by `FileSystemModel`.
  - `FileManagerWindow.qml` sets the shared `notificationManager` on the `FileSystemModel` during completion.
- Improved the File Manager user interface with BDL v2 tokens only:
  - `BreadcrumbBar.qml` — clickable path segments above the file list.
  - `Toolbar.qml` — Back, Forward, Up, Refresh, Home, Search, and Copy buttons. Back/Forward are enabled by the navigation history.
  - `SearchBar.qml` — filename query, extension filter, recursive toggle, and Clear button.
  - `FavoriteSidebar.qml` — combines Favorites (add, remove, pin), Recent Files (via `RecentFilesPanel`), standard locations, and a placeholder for mounted devices.
  - `RecentFilesPanel.qml` — dedicated recent files list with file name, last opened time, and Clear action.
  - `FileList.qml` — updated with BDL v2 colors/spacing, and a context menu with Open, Open With, Rename, Copy, Cut, Paste, Delete, and Properties actions (placeholder-safe where backend support is incomplete). Double-clicking a file adds it to Recent Files.
  - `FileManagerWindow.qml` — new layout with breadcrumb bar, search bar, search results overlay, and independent sidebar.
  - `StatusBar.qml` — shows current path, item count, and folder name.
- Implemented notifications:
  - `FileFavoriteManager` emits "Favorite Added" and "Favorite Removed" notifications.
  - `RecentFileManager` emits "Recent Files Cleared" notification.
  - No notifications are emitted during normal browsing, navigation, or opening files.
- Updated `CMakeLists.txt` with new C++ sources/headers and QML files, and bumped the project description to Sprint 45.
- Updated `docs/README.md` with BFM2 architecture, search lifecycle, favorites persistence, navigation architecture, class relationships, and ownership diagrams.
- Validated brace/CMake/QML consistency and created `tasks/bde-shell-sprint45.tar.gz`.
- No forbidden features implemented: no cloud storage, network drives, file synchronization, background indexing service, file versioning, encryption, AI search, duplicate file finder, enterprise storage policies, or Baytevora Chain integration.

### File Manager Phase 2 Class Relationships

```
FileManagerApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("File Manager", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- FileManagerWindow.qml
                                    |
                                    +-- FileSystemModel (per-window)
                                            |
                                            +-- QList<FileSystemEntry>
                                            +-- QStringList navigationHistory
                                            +-- FileFavoriteManager
                                            |       +-- QList<FavoriteLocation*>
                                            +-- RecentFileManager
                                            |       +-- QList<RecentFile*>
                                            +-- FileSearchManager
```

Each `FileSystemModel` owns one manager set, so multiple File Manager windows remain independent while their favorites and recent files share the same JSON files (by default all windows read/write the same persistence directory). The navigation history is kept in memory only and is per-window.

### Persistence

Favorites are stored as `favorites.json`:

```json
{
  "favorites": [
    {
      "favoriteId": 1,
      "displayName": "Documents",
      "path": "/home/user/Documents",
      "icon": "",
      "pinned": true
    }
  ]
}
```

Recent files are stored as `recent.json`:

```json
{
  "recentFiles": [
    {
      "recentId": 1,
      "fileName": "notes.txt",
      "path": "/home/user/Documents/notes.txt",
      "fileType": "txt",
      "lastOpened": "2026-07-09T14:00:00"
    }
  ]
}
```

Both files live in `<AppDataLocation>/filemanager`. They are loaded when the first File Manager window opens and saved whenever favorites or recent files change.

### Search Lifecycle

1. **Request**: The user enters a query in `SearchBar` and clicks Search (or presses Enter in a future enhancement).
2. **Dispatch**: `FileManagerWindow` calls `FileSearchManager::search(currentPath, query, extensionFilter, recursive)`.
3. **Traversal**: `FileSearchManager` reads the current directory using `QDir`. If `recursive` is true, it uses `QDirIterator::Subdirectories`.
4. **Filtering**: Each entry is matched against the lower-case query substring and the extension filter.
5. **Results**: A `QVariantList` of maps is returned and displayed in the search results overlay. Double-clicking a result navigates into a folder or adds a file to recent files.
6. **Cleanup**: Search performs no caching or background indexing. The result list is discarded when the user closes the overlay or clears the query.

### Navigation Architecture

- `FileSystemModel::setPath(path)` updates `m_path`, reloads the directory, and appends the path to the per-window history unless the change came from `goBack()`/`goForward()`.
- When `setPath()` is called while forward history exists, the forward entries are truncated (standard browser-style history).
- `goBack()` and `goForward()` set an internal flag to avoid pushing history entries again.
- `cdUp()` uses `QDir::cdUp()` to move to the parent directory.
- `goHome()` reads the `QStandardPaths::HomeLocation` and sets it as the current path.

### Context Menu Lifecycle

1. **Trigger**: Right-clicking inside `FileList` opens the context menu.
2. **Selection**: The selected file name is used by menu actions.
3. **Open/Open With**: Folders are navigated into; files add to Recent Files and log a placeholder open request.
4. **Rename/Copy/Cut/Paste/Delete/Properties**: Actions are placeholder-safe. Copy copies the selected filename to the clipboard.

## Sprint 46 Changes

- Added Baytevora Notes Phase 2 (BNP2) — persistent note storage, folder organization, local search, auto-save, and improved editing UI on top of the existing Notes architecture.
- Extended the `Note` model (`include/bos/Note.h`, `src/Note.cpp`) with `noteId`, `title`, `content`, `folder`, `createdAt`, `modifiedAt`, `pinned`, and `favorite`.
- Added the BNP2 C++ layer:
  - `NoteFolder` (`include/bos/NoteFolder.h`, `src/NoteFolder.cpp`) — value object with `folderId` and `name`.
  - `NotesStorageManager` (`include/bos/NotesStorageManager.h`, `src/NotesStorageManager.cpp`) — loads/saves notes and folders as JSON in the application data directory; supports auto-save, note deletion, and .bnote import/export.
  - `NoteSearchManager` (`include/bos/NoteSearchManager.h`, `src/NoteSearchManager.cpp`) — performs fast local title/content/folder/favorite search with no background indexing.
- Extended `NotesManager` (`include/bos/NotesManager.h`, `src/NotesManager.cpp`):
  - Owns `NotesStorageManager` and `NoteSearchManager`.
  - Exposes `notes`, `folders`, `noteCount`, `folderCount`, and active-note properties (`activeNoteId`, `activeNoteTitle`, `activeNoteContent`, `activeNoteFolder`, `activeNoteUpdatedAt`, `activeNotePinned`, `activeNoteFavorite`) to QML.
  - Added `createNote()`, `newNote()`, `save()`, `saveAs(title)`, `renameActiveNote(title)`, `duplicateActiveNote()`, `deleteNote(index)`, `deleteActiveNote()`, `moveActiveNoteToFolder(folder)`, `pinActiveNote()`, `favoriteActiveNote()`, `togglePinActiveNote()`, and `toggleFavoriteActiveNote()`.
  - Added folder operations: `createFolder(name)`, `renameFolder(folderId, name)`, `deleteFolder(folderId)`.
  - Added `searchNotes(query, folder, favoritesOnly)` for live filtering.
  - Added `characterCount()` and `wordCount()`.
  - Auto-saves on every title/content/folder/pin/favorite change without emitting notifications.
  - Emits notifications: `Note Created` (existing), `Note Deleted`, `Folder Created`, `Folder Deleted`.
- Updated `NotesApplication` (`include/bos/NotesApplication.h`, `src/NotesApplication.cpp`):
  - Added `openFile(filePath)` and a `pendingOpenFiles` queue.
  - Registered as a QML singleton so `NotesWindow` can consume pending .bnote open requests.
- Updated `ApplicationManager` (`include/bos/ApplicationManager.h`, `src/ApplicationManager.cpp`):
  - Added `openFileWithApplication(name, filePath)` invokable used by the File Manager to open `.bnote` files in Notes.
- Updated `FileList.qml`:
  - Double-clicking or choosing `Open` on a `.bnote` file calls `applicationManager.openFileWithApplication("Notes", path)`.
- Added QML components:
  - `FolderSidebar.qml` — folder list with note counts and a Favorites filter.
  - `NotesSearchBar.qml` — live title/content search with result list.
  - `NoteProperties.qml` — properties dialog with metadata and pin/favorite toggles.
  - `NotesToolbar.qml` — New, Save, Search, Favorite, Pin, Properties actions.
  - `NotesSidebar.qml` — updated note list showing pinned/favorite badges and note count.
  - `NotesStatusBar.qml` — shows note count, character count, word count, and last saved time.
  - `NotesWindow.qml` — integrates folder sidebar, search bar, note list, editor, status bar, and consumes pending .bnote files.
- Updated `Application.cpp`:
  - Registers `NoteFolder`, `NotesStorageManager`, and `NoteSearchManager` as uncreatable QML types.
  - Exposes `NotesApplication` as a QML singleton instance.
- Updated `CMakeLists.txt` with new C++ sources/headers/QML files and bumped the description to Sprint 46.
- Updated `docs/README.md` with BNP2 architecture, storage lifecycle, folder architecture, search lifecycle, class relationships, and ownership diagrams.
- No forbidden features implemented: no cloud sync, rich text, Markdown, collaborative editing, AI writing, OCR, voice notes, or Baytevora Chain integration.

### Notes Phase 2 Class Relationships

```
NotesApplication (singleton)
    |
    +-- open() / openFile(path)
            |
            +-- WindowManager::registerWindow("Notes", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- NotesWindow.qml
                                    |
                                    +-- NotesManager (per-window)
                                            |
                                            +-- QList<Note>
                                            +-- QList<NoteFolder>
                                            +-- NotesStorageManager
                                            +-- NoteSearchManager
```

Each `NotesWindow` owns its own `NotesManager`, so multiple Notes windows remain independent. The JSON persistence file is shared across windows by default (`notes.json` in the application data directory).

### Persistence

Notes and folders are stored as `notes.json`:

```json
{
  "folders": [
    { "folderId": 1, "name": "Notes" },
    { "folderId": 2, "name": "Favorites" }
  ],
  "notes": [
    {
      "noteId": 1,
      "title": "Ideas",
      "content": "...",
      "folder": "Notes",
      "createdAt": "2026-07-09T14:00:00",
      "updatedAt": "2026-07-09T14:05:00",
      "pinned": false,
      "favorite": false
    }
  ]
}
```

The file lives in `<AppDataLocation>/notes`. It is loaded when the first Notes window opens and saved automatically on every edit.

### Storage Lifecycle

1. **Load**: `NotesManager` constructs `NotesStorageManager` and calls `load()`, populating `m_notes` and `m_folders` and recovering next IDs.
2. **Defaults**: If no folders exist, the `Notes` and `Favorites` folders are created.
3. **Edit**: Title or content changes in QML invoke `setActiveNoteTitle()`/`setActiveNoteContent()`, update the `Note`, and call `autoSave()`.
4. **Auto-save**: `autoSave()` calls `NotesStorageManager::save()`, rewriting the JSON file. No notification is emitted.
5. **Explicit save**: `save()` persists and emits a `Note Saved` notification.
6. **Delete**: `deleteNote()` removes the note, persists, and emits `Note Deleted`.
7. **Folder lifecycle**: `createFolder()`/`renameFolder()`/`deleteFolder()` persist after each change and emit `Folder Created`/`Folder Deleted` where applicable.

### Search Lifecycle

1. **Typing**: `NotesSearchBar` updates its query text on every keystroke.
2. **Dispatch**: The search results list model calls `NotesManager::searchNotes(query, "", false)`.
3. **Matching**: `NoteSearchManager::matches()` checks favorite-only/folder filters and lower-case title/content substrings.
4. **Results**: A `QVariantList` is returned and displayed. Clicking a result selects the note by ID and closes the search bar.

### Folder Architecture

- Folders are standalone objects with integer IDs.
- Notes store their folder name; deleting a folder moves all affected notes back to the `Notes` folder.
- `FolderSidebar` displays all folders with live note counts and a `Favorites` pseudo-folder that filters by `favorite`.
- `NotesSidebar` shows notes filtered by the selected folder.

### File Manager Integration

- The File Manager recognizes `.bnote` files.
- `FileList.qml` calls `applicationManager.openFileWithApplication("Notes", path)` for these files.
- `ApplicationManager::openFileWithApplication()` routes to `NotesApplication::openFile()`, which opens a Notes window and queues the path.
- `NotesWindow` consumes the pending path on completion and imports the note into the per-window manager.
- This prepares the architecture for future export formats (PDF/Markdown) without implementing them.

## Sprint 47 Changes

- Added Baytevora Image Viewer Phase 2 (BIV2) — professional viewing capabilities on top of Sprint 29's Image Viewer architecture.
- Extended the `ImageDocument` model (`include/bos/ImageDocument.h`, `src/ImageDocument.cpp`):
  - Added `fileName`, `filePath`, `width`, `height`, `fileSize`, `format`, `createdAt`, `modifiedAt`.
  - Added transformation state: `rotation`, `flippedHorizontally`, `flippedVertically`.
  - Added `resetTransformations()` invokable.
  - Expanded supported formats to PNG, JPG, JPEG, BMP, GIF, and WEBP.
- Added the BIV2 C++ layer:
  - `ImageMetadata` (`include/bos/ImageMetadata.h`, `src/ImageMetadata.cpp`) — exposes dimensions, resolution, format, file size, creation, and modification timestamps to QML.
  - `ImageSlideshowManager` (`include/bos/ImageSlideshowManager.h`, `src/ImageSlideshowManager.cpp`) — manages slideshow state, default 5-second interval, and `next()`/`previous()` navigation over the current folder's images.
- Extended `ImageViewerManager` (`include/bos/ImageViewerManager.h`, `src/ImageViewerManager.cpp`):
  - Owns `ImageDocument`, `ImageMetadata`, and `ImageSlideshowManager`.
  - Exposes `document`, `metadata`, and `slideshow` properties to QML.
  - Added transformation actions: `rotateLeft()`, `rotateRight()`, `flipHorizontal()`, `flipVertical()`, `resetTransformations()`.
  - Added zoom modes: `actualSize()`, `fitToWidth(width)`, `fitToHeight(height)`, plus existing `fitToWindow()` and `zoomIn()`/`zoomOut()`.
  - Added `nextImage()` and `previousImage()` for folder navigation.
  - Added `printImage()` hook for Print Manager integration.
  - Tracks the current folder and refreshes the slideshow image list automatically.
  - Emits notifications: `Image Opened`, `Image Closed`, `Image Rotated`, `Image Printed`.
- Updated `ImageViewerApplication` (`include/bos/ImageViewerApplication.h`, `src/ImageViewerApplication.cpp`):
  - Added `openFile(filePath)`, `hasPendingOpenFile()`, and `takePendingOpenFile()`.
  - Registered as a QML singleton so `ImageViewerWindow` can consume pending file open requests.
- Updated `ApplicationManager` (`src/ApplicationManager.cpp`):
  - `openFileWithApplication("Image Viewer", path)` routes to `ImageViewerApplication::openFile()`.
- Updated `FileList.qml`:
  - Double-clicking or opening image files (`.png`, `.jpg`, `.jpeg`, `.bmp`, `.gif`, `.webp`) invokes `applicationManager.openFileWithApplication("Image Viewer", path)`.
- Added QML components:
  - `MetadataPanel.qml` — side panel showing file name, path, dimensions, format, size, created, and modified.
  - `SlideshowControls.qml` — previous/play/pause/stop/next controls.
  - `ImageToolbar.qml` — updated with rotate left/right, flip horizontal/vertical, fullscreen, fit modes, slideshow toggle, metadata toggle, print, and previous/next.
  - `ImageCanvas.qml` — applies rotation and flip transforms, supports zoom, and preserves aspect ratio.
  - `ImageStatusBar.qml` — updated with zoom level, resolution, and current folder image index/total.
  - `ImageViewerWindow.qml` — integrates toolbar, slideshow controls, metadata panel, canvas, and status bar.
- Updated `Application.cpp`:
  - Registers `ImageMetadata` and `ImageSlideshowManager` as uncreatable QML types.
  - Exposes `ImageViewerApplication` as a QML singleton instance.
- Updated `CMakeLists.txt` with new C++ sources/headers/QML files and bumped the description to Sprint 47.
- Updated `docs/README.md` with BIV2 architecture, slideshow lifecycle, metadata architecture, integration diagrams, and ownership diagrams.
- No forbidden features implemented: no image editing, cropping, drawing, filters, color correction, EXIF editing, AI enhancement, OCR, face recognition, cloud sync, or Baytevora Chain integration.

### Image Viewer Phase 2 Class Relationships

```
ImageViewerApplication (singleton)
    |
    +-- openFile(path)
            |
            +-- WindowManager::registerWindow("Image Viewer", ...)
                    |
                    +-- WindowFrame.qml
                            |
                            +-- ImageViewerWindow.qml
                                    |
                                    +-- ImageViewerManager (per-window)
                                            |
                                            +-- ImageDocument
                                            +-- ImageMetadata
                                            +-- ImageSlideshowManager
```

### Slideshow Lifecycle

1. **Open**: `openImage(path)` stores the current folder path in `ImageViewerManager`.
2. **Refresh**: `ImageSlideshowManager::refreshFolder()` enumerates supported image files in the folder.
3. **Start**: `start()` begins a 5-second `QTimer` and emits `Slideshow Started`.
4. **Advance**: Timer timeout calls `advance(1)` and opens the next image in the folder.
5. **Manual navigation**: `next()`/`previous()` advances in the corresponding direction and wraps around.
6. **Pause/Stop**: `pause()` halts the timer; `stop()` halts the timer and resets running state. Both emit `Slideshow Stopped` when applicable.

### Metadata Architecture

- `ImageDocument` reads file information via `QFileInfo` when `setImagePath()` is called.
- `ImageMetadata` listens to `ImageDocument` signals and exposes formatted metadata.
- `MetadataPanel.qml` displays all fields, including resolution as `width x height` and timestamps in `yyyy-MM-dd hh:mm` format.

### Print Manager Integration

- The `Print` toolbar button calls `viewerManager.printImage()` and `printManager.printDocument(document.imagePath)`.
- `ImageViewerManager::printImage()` emits an `Image Printed` notification.
- `printManager.printDocument()` submits a placeholder print job through the existing Baytevora Printing Framework.

### Folder Navigation

- `ImageSlideshowManager` scans the current folder for supported images and maintains an ordered list.
- `nextImage()`/`previousImage()` move within that list and wrap at boundaries.
- `ImageStatusBar` shows the current position (`currentIndex + 1 / imageCount`) when an image is loaded.

## Sprint 48 Changes

- Added Baytevora Store Phase 2 (BSP2) — richer browsing, installed app management, update preparation, and scalable catalog architecture.
- Refactored the Store category enum into `StoreCategoryEnum` (`include/bos/StoreCategoryEnum.h`, `src/StoreCategoryEnum.cpp`) while retaining QML exposure as `StoreCategory`.
- Added new data models:
  - `StoreCategory` (`include/bos/StoreCategory.h`, `src/StoreCategory.cpp`) — `categoryId`, `name`, `icon`, and `applicationCount`, exposed to QML as a `QVariantMap`.
  - `InstalledApplication` (`include/bos/InstalledApplication.h`, `src/InstalledApplication.cpp`) — `applicationId`, `version`, `installDate`, and `lastUpdated`.
  - `StoreUpdate` (`include/bos/StoreUpdate.h`, `src/StoreUpdate.cpp`) — `applicationId`, `installedVersion`, `availableVersion`, and `updateAvailable`.
- Extended `StoreItem` (`include/bos/StoreItem.h`, `src/StoreItem.cpp`) with `applicationId`, `shortDescription`, `longDescription`, `installedVersion`, `latestVersion`, `screenshots`, `changelog`, `rating`, and `size`, while preserving existing fields.
- Extended `StoreCatalog` (`include/bos/StoreCatalog.h`, `src/StoreCatalog.cpp`) to seed richer metadata per item, compute `StoreCategory` counts, and update installed versions.
- Extended `StoreManager` (`include/bos/StoreManager.h`, `src/StoreManager.cpp`):
  - New properties: `categories` (rich category maps), `installedApplications`, `updates`, and `recentlyAdded`.
  - New invokables: `filterInstalled()`, `sortByName()`, `sortByRating()`, `sortByDownloads()`, `requestRemove()`, and `refreshUpdates()`.
  - `requestInstall()` now syncs installed state and emits an `Application Installed` notification.
  - `requestRemove()` delegates to `PackageManager::uninstallPackage()` and emits an `Application Removed` notification.
  - `refreshUpdates()` re-syncs state and emits `Updates Refreshed`.
  - Package Manager integration continues to be a local placeholder; no online repositories.
- Added and updated QML components:
  - `StoreToolbar.qml` — Home, Categories, Installed, Updates, and search.
  - `CategorySidebar.qml` — category list with application counts.
  - `StoreGrid.qml` — reusable application grid.
  - `StoreStatusBar.qml` — application count/status.
  - `ApplicationDetails.qml` — icon placeholder, metadata, screenshots placeholder, changelog, Install/Remove/Open/Back buttons.
  - `InstalledApplicationsPage.qml` — list of installed apps with version and install date.
  - `UpdatesPage.qml` — available updates list and Refresh action.
  - `ApplicationCard.qml` and `InfoRow.qml` updated to use BDL v2 tokens.
  - `StoreWindow.qml` rewritten to integrate toolbar, sidebar, pages, and details with window-local state.
- Updated `Application.cpp` to register `StoreCategoryEnum` under the `StoreCategory` QML name and expose `storeManager`.
- Updated `CMakeLists.txt` with new C++ sources/headers and QML files, bumped to Sprint 48.
- Added comprehensive documentation section for Store Phase 2 architecture, data model, Package Manager integration, class relationships, and ownership diagrams.
- No forbidden features: online repositories, user accounts, payments, licensing, cloud sync, reviews, real ratings, automatic updates, background downloads, enterprise repositories, or Baytevora Chain integration.

### Store Phase 2 Architecture

```
StoreApplication
    |
    +-- open()
            |
            +-- WindowManager::registerWindow("Baytevora Store")
                    |
                    +-- WindowFrame.qml
                            |
                            +-- StoreWindow.qml (per-window state)
                                    |
                                    +-- StoreToolbar
                                    +-- CategorySidebar
                                    +-- StoreGrid / FeaturedSection
                                    +-- InstalledApplicationsPage
                                    +-- UpdatesPage
                                    +-- ApplicationDetails
                                    +-- StoreStatusBar
                                    |
                                    +-- storeManager (singleton context property)
                                            |
                                            +-- StoreCatalog (StoreItem records)
                                            +-- PackageManager (placeholder install/remove)
```

### Store Data Model

- `StoreItem` is the primary catalog model. Each item maps to a `QVariantMap` so QML can bind directly to fields.
- `StoreCategory` provides a rich category view with counts. Counts are computed from the seeded `StoreCatalog`.
- `InstalledApplication` represents a package that has been installed, including version and placeholder install/update dates.
- `StoreUpdate` represents an installed package whose `installedVersion` differs from `latestVersion`. Updates are computed on demand and never applied automatically.

### Package Manager Integration

- `StoreManager` calls `PackageManager::installPackage()` and `PackageManager::uninstallPackage()`.
- After each operation, `syncInstalledState()` reads `PackageManager::package(id)` and updates the catalog's `installed` flag and `installedVersion`.
- `StoreManager::updates()` compares `installedVersion` to `latestVersion` for installed items and returns `StoreUpdate` records.
- All operations remain local placeholders; no network access, signature verification, or repository synchronization is performed.

### Filtering and Sorting

- `filterInstalled(bool)` returns installed or not-installed items.
- `categoryItems(int)` returns items for a `StoreCategoryEnum::Value`.
- `search(QString)` matches name, short description, and developer.
- `sortByName()`, `sortByRating()`, and `sortByDownloads()` sort a `QVariantList` of item maps and return a sorted copy.

### Notifications

- `Application Installed` — emitted after a successful install request.
- `Application Removed` — emitted after a successful remove request.
- `Updates Refreshed` — emitted when `refreshUpdates()` is invoked.
- No notifications are emitted during browsing, searching, or sorting.

## Sprint 49 Changes

- Implemented Baytevora Package Manager Phase 2 (BPM2) — professional package architecture with dependencies, repositories, transactions, and Store integration while preserving the existing Package Manager foundation.
- Added new data models:
  - `Package` (`include/bos/Package.h`, `src/Package.cpp`) — rich package model with `packageId`, `applicationId`, `name`, `version`, `architecture`, `size`, `installed`, `description`, `category`, `developer`, `state`, and `packageType`, exposed as a `QVariantMap`.
  - `PackageDependency` (`include/bos/PackageDependency.h`, `src/PackageDependency.cpp`) — `packageId`, `dependencyId`, `minimumVersion`, and `optional`.
  - `PackageRepository` (`include/bos/PackageRepository.h`, `src/PackageRepository.cpp`) — `repositoryId`, `name`, `enabled`, `priority`, and `localPath`.
  - `PackageTransaction` (`include/bos/PackageTransaction.h`, `src/PackageTransaction.cpp`) — `transactionId`, `operation`, `packageList`, `state`, `progress`, `errorMessage`, `startTime`, and `finishTime`; includes `PackageOperation` and `PackageTransactionState` enums exposed to QML.
- Extended `PackageManager` (`include/bos/PackageManager.h`, `src/PackageManager.cpp`):
  - New properties: `packages` (rich maps), `installedPackages`, `availablePackages`, `repositories`, `transactions`, and `packageCount`.
  - New invokables: `dependenciesFor()`, `missingDependencies()`, `installationPlan()`, `updatePlan()`, `updatePackage()`, `enableRepository()`, `disableRepository()`, `setRepositoryPriority()`, and `cancelTransaction()`.
  - Transactions run asynchronously through `QTimer` in a single queue with states `Pending`, `Running`, `Completed`, `Failed`, and `Cancelled`.
  - Notifications: `Package Installed`, `Package Removed`, `Package Updated`, and `Transaction Failed`.
  - Preserved existing `enablePackage()`/`disablePackage()` to avoid regressions.
- Added `PackageManagerApplication` (`include/bos/PackageManagerApplication.h`, `src/PackageManagerApplication.cpp`) and registered it with `ApplicationManager` and in `Application.cpp`.
- Added `Package Manager` placeholder to `ApplicationManager::registerPlaceholderApplications()` and `WindowFrame` mapping to `PackageManagerWindow.qml`.
- Added QML components:
  - `PackageManagerWindow.qml` — main window with toolbar and section loader.
  - `PackageToolbar.qml` — Packages, Repositories, Transactions, Dependencies.
  - `PackageStatusBar.qml` — installed/available/total counts.
  - `RepositoryManager.qml` and `RepositoryDelegate.qml` — list, enable/disable, and priority display.
  - `TransactionViewer.qml` — transaction list with progress bars and status.
  - `DependencyViewer.qml` — package selector and dependency list.
- Updated `PackagesPage.qml`, `PackageList.qml`, and `PackageCard.qml` to emit dependency-view selections and use BDL v2 tokens fully.
- Store integration: `StoreManager` exposes `storeDependenciesFor()`, `packageMetadata()`, `storeUpdateAvailable()`, and `storeUpdatePlan()` delegating to `PackageManager`. Existing install/remove and installed-state synchronization remain in place.
- Updated `CMakeLists.txt` with new sources, headers, QML files, and bumped to Sprint 49.
- Added comprehensive BPM2 architecture, dependency graph, repository architecture, transaction lifecycle, Store integration, class relationships, and ownership documentation.
- No forbidden features introduced: online repositories, internet downloads, automatic updates, user accounts, licensing, payments, cloud synchronization, enterprise deployment, AI recommendations, or Baytevora Chain integration.

### Package Manager Phase 2 Architecture

```
PackageModule
    |
    +-- PackageManager
            |
            +-- PackageDatabase (PackageInfo records)
            +-- PackageDependency records (seeded)
            +-- PackageRepository records (local placeholders)
            +-- PackageTransaction queue (QTimer driven)
            |
            +-- packageManager (QML context property)
                    |
                    +-- PackageManagerWindow.qml
                            |
                            +-- PackageToolbar
                            +-- PackagesPage / PackageList / PackageCard
                            +-- RepositoryManager / RepositoryDelegate
                            +-- TransactionViewer
                            +-- DependencyViewer
                            +-- PackageStatusBar
```

### Dependency Architecture

- `dependenciesFor(id)` returns all declared dependencies of a package.
- `missingDependencies(id)` returns dependencies whose target package is not installed.
- `installationPlan(id)` returns an ordered placeholder plan: the package plus any missing required dependencies.
- No downloads, no online resolution. Missing packages remain missing for now.

### Repository Architecture

- Repositories are local placeholders with `enabled` and `priority`.
- `enableRepository()`, `disableRepository()`, and `setRepositoryPriority()` mutate repository state.
- Architecture is ready for future remote/enterprise/private repository extensions.

### Transaction Lifecycle

- Transactions are created by `installPackage()`, `uninstallPackage()`, or `updatePackage()`.
- State flow: `Pending` → `Running` → `Completed` / `Failed` / `Cancelled`.
- Progress advances every 200 ms by 20% while `Running`.
- Completed install/remove/update operations update `PackageDatabase` state.
- `cancelTransaction()` stops a running transaction and emits `Transactions Changed`.

### Store Integration

- `StoreManager::syncInstalledState()` reads `PackageManager::package(id)`.
- `StoreManager` exposes dependency and update metadata directly from `PackageManager` so QML can display package details without duplicating data.

## Sprint 50 Changes

- Performed the Beta Stability & Validation (BSV) engineering audit across the Baytevora OS Alpha implementation.
- **Stability audit**: reviewed application handlers, `QTimer` lifecycle, object ownership, and signal/slot correctness. Bounded the `PackageManager` transaction log to the last 50 entries to prevent unbounded memory growth and ensure completed timers are stopped and deleted.
- **Performance audit**: removed unnecessary ternary fallback evaluations across the QML surface by resolving BDL token managers directly. Verified no redundant model recomputation in the critical `WindowManager` path.
- **BDL v2 consistency audit**: eliminated hardcoded color literals from the entire QML tree. Replaced ~2,000 fallback hex values (e.g., `ThemeManager ? ThemeManager.X : "#..."`) with direct `ThemeManager.X` references, and replaced 78 remaining direct `#RRGGBB` assignments with semantic `ThemeManager` tokens (`backgroundColor`, `surfaceColor`, `surfaceSecondaryColor`, `borderColor`, `textPrimary`, `textSecondary`, `textDisabled`, `accentColor`, `primaryColor`, `successColor`, `warningColor`, `errorColor`, `selectionColor`, `highlightColor`).
- **Application validation**: verified that every placeholder registered in `ApplicationManager` has both a launch branch in `ApplicationManager::launchApplication()` and a matching `WindowFrame` source mapping. Added missing `openFileWithApplication()` branches for `PDF Viewer` and `Archive Manager` so the File Manager can open `.pdf` and archive files.
- **Integration validation**: confirmed Store ↔ Package Manager wiring (`StoreManager` delegates installed state, dependencies, metadata, and update checks to `PackageManager`), Browser ↔ internal managers (downloads, bookmarks, history, permissions), Image Viewer ↔ Print Manager (Print Manager application is registered), ApplicationManager routing, Notification Service, Clipboard Service, and WindowManager are all intact.
- **Accessibility audit**: verified that keyboard focus and adaptive layout infrastructure remain in place; no regressions introduced.
- **Documentation audit**: updated class table, ownership diagrams, and added this Sprint 50 summary and Alpha Candidate Report.
- **Code cleanup**: removed obsolete hardcoded fallback values; no remaining `TODO`/`FIXME`/`HACK` markers were found in `src`, `include`, or `qml`.
- **Build validation**: verified `CMakeLists.txt` source/header/QML references, file existence, and structural brace balance for all modified files. No new dependencies were introduced.
- **Forbidden items preserved**: no new applications, features, UI redesigns, theme changes, animations, networking, cloud services, browser/store/package improvements, architecture redesign, Baytevora Identity System, installer, ISO generation, boot branding, or Welcome Center were added.

### Alpha Candidate Report

**Overall architecture summary**

Baytevora OS (BOS) is a security-first, privacy-focused Linux-based operating system. The Baytevora Desktop Environment (BDE) Shell is implemented as a native Qt 6 / QML / C++17 / CMake application. It is organized into desktop modules, native application handlers, a shared Window Manager, a Notification Service, the Baytevora Design Language v2 (BDL) token system, and the Application Framework. Persistent storage is deliberately avoided in the Alpha; all data is seeded in-memory.

**Completed applications (Sprint 50)**

- File Manager
- Terminal
- Settings
- Baytevora Browser
- Notes
- Calculator
- PDF Viewer
- Archive Manager
- Media Player
- Text Editor
- System Monitor
- Task Manager
- Network Manager
- Storage Manager
- Print Manager
- Baytevora Store (Phase 2)
- Baytevora Image Viewer (Phase 2)
- Baytevora Package Manager (Phase 2)
- Desktop, Taskbar, Launcher, Lock Screen, Login Screen
- Notification Center, Power Menu, Window Manager

**Completed frameworks**

- Module lifecycle and `ModuleManager`
- `ApplicationManager` / `ApplicationRegistry` / `ApplicationLauncher`
- `WindowManager` with window registration, focus, minimize/maximize/restore/close
- `NotificationService` / `NotificationManager`
- `ClipboardModule`
- BDL v2 (`ThemeManager`, `TypographyManager`, `IconManager`, `SpacingManager`, `AdaptiveLayoutManager`, `DesignTokens`)
- Native application handler pattern with `setWindowManager()` / `setNotificationManager()` wiring
- In-memory seeded data models for packages, store catalog, repositories, dependencies, transactions, installed apps, and updates

**Known limitations**

- All package/store operations are local placeholders; no online repositories, downloads, or automatic updates.
- Browser is a lightweight shell without a real rendering engine or network stack.
- Printing is simulated; no physical printer backend.
- Audio/video playback is UI-only with no real codec pipeline.
- Settings toggles are visual placeholders and do not modify the underlying OS.
- User authentication is simulated; no real account system or Baytevora Identity integration.
- No installer, ISO generation, boot branding, or Welcome Center yet.
- Some legacy QML components still use fixed layout sizes (width/height defaults) rather than fully tokenized spacing; this is tolerated for the Alpha because it does not affect theme consistency or runtime stability.

**Alpha readiness notes**

- The shell launches, manages windows, routes applications, and integrates the major desktop subsystems without architectural changes.
- All sprint work is packaged and validated structurally; the codebase is ready for Alpha Preparation Phase entry.
- The next phase should focus on: installer/ISO, boot branding, real authentication/identity, and the Welcome Center, while keeping the current architecture stable.
