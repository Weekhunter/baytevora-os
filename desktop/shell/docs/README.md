# BDE Shell Sprint 1

## Overview

The foundational native Qt application for the Baytevora Desktop Environment (BDE).

This sprint delivers a minimal, modular shell that opens a borderless fullscreen window with a solid background color. No desktop features are implemented yet.

## Technology Stack

- C++17
- Qt 6
- Qt Quick (QML)
- CMake

## Build Requirements

- CMake 3.16 or newer
- Qt 6.2 or newer with the `Quick` module installed
- A C++17-compatible compiler (GCC, Clang, MSVC)

## Qt Dependencies

- Qt6::Core
- Qt6::Quick
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
| `assets/wallpapers/default.jpg` | Default wallpaper image |
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
