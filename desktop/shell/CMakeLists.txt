cmake_minimum_required(VERSION 3.16)

project(BOS_Shell
    VERSION 0.1.0
    DESCRIPTION "Baytevora OS Desktop Environment Shell - Sprint 20"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt6 components required for this sprint.
find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Widgets)

# Standard Qt project setup. This helper enables Qt's recommended CMake
# defaults and improves IDE compatibility (Qt Creator, CLion, command line).
qt_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/SessionManager.cpp
    src/ModuleManager.cpp
    src/DesktopSurfaceModule.cpp
    src/WallpaperModule.cpp
    src/WindowManager.cpp
    src/Window.cpp
    src/TaskbarModule.cpp
    src/LauncherModule.cpp
    src/ApplicationRegistry.cpp
    src/ApplicationLauncher.cpp
    src/ApplicationManager.cpp
    src/NotificationModule.cpp
    src/NotificationManager.cpp
    src/FileSystemModel.cpp
    src/FileManagerApplication.cpp
    src/SettingsManager.cpp
    src/SettingsApplication.cpp
    src/TerminalSession.cpp
    src/TerminalManager.cpp
    src/TerminalApplication.cpp
    src/ThemeManager.cpp
    src/DesignTokens.cpp
    src/TypographyManager.cpp
    src/SpacingManager.cpp
    src/IconManager.cpp
    src/DesktopItem.cpp
    src/DesktopModel.cpp
    src/DesktopManager.cpp
    src/DesktopIconsModule.cpp
    src/ClipboardItem.cpp
    src/ClipboardManager.cpp
    src/ClipboardModule.cpp
    src/Shortcut.cpp
    src/ShortcutManager.cpp
    src/ShortcutModule.cpp
    src/SearchCategory.cpp
    src/SearchItem.cpp
    src/SearchManager.cpp
    src/SearchModule.cpp
    src/ApplicationSearchProvider.cpp
    src/DesktopSearchProvider.cpp
    src/SettingsSearchProvider.cpp
    src/PowerActionType.cpp
    src/PowerAction.cpp
    src/PowerManager.cpp
    src/PowerModule.cpp
)

set(HEADERS
    include/bos/Application.h
    include/bos/SessionManager.h
    include/bos/DesktopModule.h
    include/bos/ModuleManager.h
    include/bos/DesktopSurfaceModule.h
    include/bos/WallpaperModule.h
    include/bos/WindowManager.h
    include/bos/Window.h
    include/bos/TaskbarModule.h
    include/bos/LauncherModule.h
    include/bos/ApplicationInfo.h
    include/bos/ApplicationRegistry.h
    include/bos/ApplicationLauncher.h
    include/bos/ApplicationManager.h
    include/bos/Notification.h
    include/bos/NotificationManager.h
    include/bos/NotificationModule.h
    include/bos/FileSystemModel.h
    include/bos/FileManagerApplication.h
    include/bos/SettingsPage.h
    include/bos/SettingsManager.h
    include/bos/SettingsApplication.h
    include/bos/TerminalSession.h
    include/bos/TerminalManager.h
    include/bos/TerminalApplication.h
    include/bos/ThemeManager.h
    include/bos/DesignTokens.h
    include/bos/TypographyManager.h
    include/bos/SpacingManager.h
    include/bos/IconManager.h
    include/bos/DesktopItem.h
    include/bos/DesktopModel.h
    include/bos/DesktopManager.h
    include/bos/DesktopIconsModule.h
    include/bos/ClipboardItem.h
    include/bos/ClipboardManager.h
    include/bos/ClipboardModule.h
    include/bos/ShortcutContext.h
    include/bos/Shortcut.h
    include/bos/ShortcutManager.h
    include/bos/ShortcutModule.h
    include/bos/SearchCategory.h
    include/bos/SearchItem.h
    include/bos/SearchProvider.h
    include/bos/SearchManager.h
    include/bos/SearchModule.h
    include/bos/ApplicationSearchProvider.h
    include/bos/DesktopSearchProvider.h
    include/bos/SettingsSearchProvider.h
    include/bos/PowerActionType.h
    include/bos/PowerAction.h
    include/bos/PowerManager.h
    include/bos/PowerModule.h
)

qt_add_executable(BOS_Shell
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(BOS_Shell PRIVATE
    include
)

target_link_libraries(BOS_Shell PRIVATE
    Qt6::Quick
    Qt6::Widgets
)

# Embed QML files as a QML module. This keeps the QML source tree clean and
# lets the application load the interface via module URI and type name.
qt_add_qml_module(BOS_Shell
    URI BOS.Shell
    VERSION 1.0
    QML_FILES
        qml/Desktop.qml
        qml/DesktopSurface.qml
        qml/Wallpaper.qml
        qml/WindowFrame.qml
        qml/WindowButton.qml
        qml/Taskbar.qml
        qml/TaskbarButton.qml
        qml/RunningApps.qml
        qml/Clock.qml
        qml/Launcher.qml
        qml/LauncherButton.qml
        qml/LauncherGrid.qml
        qml/LauncherHeader.qml
        qml/SearchField.qml
        qml/SearchResults.qml
        qml/SearchResultItem.qml
        qml/PowerMenu.qml
        qml/PowerMenuItem.qml
        qml/NotificationCenter.qml
        qml/NotificationPopup.qml
        qml/FileManagerWindow.qml
        qml/Sidebar.qml
        qml/FileList.qml
        qml/Toolbar.qml
        qml/StatusBar.qml
        qml/ToolButton.qml
        qml/HeaderLabel.qml
        qml/CellLabel.qml
        qml/SettingsWindow.qml
        qml/NavigationSidebar.qml
        qml/SettingsContent.qml
        qml/SettingsPage.qml
        qml/SettingsButton.qml
        qml/InfoRow.qml
        qml/TerminalWindow.qml
        qml/TerminalToolbar.qml
        qml/TerminalView.qml
        qml/TerminalStatusBar.qml
        qml/DesktopIcons.qml
        qml/DesktopIcon.qml
        qml/DesktopSelection.qml
)

# Copy assets from the source tree into the build directory so the executable
# can resolve relative paths at runtime. The copy is performed at build time
# and is skipped if the assets directory is absent, which lets the application
# gracefully fall back to the solid color background when no wallpaper exists.
set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
if(EXISTS "${ASSETS_SOURCE_DIR}")
    add_custom_command(TARGET BOS_Shell POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${ASSETS_SOURCE_DIR}" "$<TARGET_FILE_DIR:BOS_Shell>/assets"
        COMMENT "Copying assets to build directory"
    )
endif()

# Cross-platform target properties. On Windows the executable is a GUI
# application; on macOS it is packaged as a bundle.
set_target_properties(BOS_Shell PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
