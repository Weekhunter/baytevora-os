cmake_minimum_required(VERSION 3.16)

project(Baytevora_OS_Installer
    VERSION 0.1.0
    DESCRIPTION "Baytevora OS Installer (BOI) - Milestone G"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick QuickControls2 Widgets)

qt_standard_project_setup()

set(SHELL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../desktop/shell)

set(SOURCES
    src/main.cpp
    src/InstallerApplication.cpp
    src/InstallerManager.cpp
    src/InstallerSession.cpp
    src/InstallationTarget.cpp
    src/InstallationSummary.cpp
    ${SHELL_DIR}/src/BrandingManager.cpp
    ${SHELL_DIR}/src/StorageManager.cpp
    ${SHELL_DIR}/src/StorageDevice.cpp
    ${SHELL_DIR}/src/StoragePartition.cpp
    ${SHELL_DIR}/src/ThemeManager.cpp
    ${SHELL_DIR}/src/TypographyManager.cpp
    ${SHELL_DIR}/src/SpacingManager.cpp
    ${SHELL_DIR}/src/DesignTokens.cpp
    ${SHELL_DIR}/src/IconManager.cpp
    ${SHELL_DIR}/src/AdaptiveLayoutManager.cpp
)

set(HEADERS
    include/boi/InstallerApplication.h
    include/boi/InstallerManager.h
    include/boi/InstallerSession.h
    include/boi/InstallationTarget.h
    include/boi/InstallationSummary.h
)

set(QML_FILES
    qml/InstallerWindow.qml
    qml/InstallerToolbar.qml
    qml/InstallerSidebar.qml
    qml/InstallerProgress.qml
    qml/InstallerStatusBar.qml
    qml/InstallerButton.qml
    qml/WelcomePage.qml
    qml/LanguagePage.qml
    qml/KeyboardPage.qml
    qml/LicensePage.qml
    qml/InstallationTypePage.qml
    qml/DiskSelectionPage.qml
    qml/DiskSelector.qml
    qml/PartitionSummaryPage.qml
    qml/SummaryPage.qml
    qml/InstallationProgressPage.qml
    qml/CompletionPage.qml
)

qt_add_executable(Baytevora_OS_Installer
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Baytevora_OS_Installer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SHELL_DIR}/include
)

target_compile_definitions(Baytevora_OS_Installer PRIVATE
    BAYTEVORA_BRANDING_DIR="../../tasks/Branding"
)

target_link_libraries(Baytevora_OS_Installer PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
)

qt_add_qml_module(Baytevora_OS_Installer
    URI BOI.Installer
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES ${QML_FILES}
)

# Ensure the license text is bundled as a resource.
qt_add_resources(Baytevora_OS_Installer "installer_data"
    PREFIX "/"
    FILES
        data/license.txt
)
