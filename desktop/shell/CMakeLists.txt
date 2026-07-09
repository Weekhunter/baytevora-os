cmake_minimum_required(VERSION 3.16)

project(BOS_Shell
    VERSION 0.1.0
    DESCRIPTION "Baytevora OS Desktop Environment Shell - Sprint 1"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt6 components required for this sprint.
find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

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
