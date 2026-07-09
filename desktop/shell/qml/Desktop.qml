import QtQuick
import QtQuick.Window

/**
 * @brief Root window of the Baytevora Desktop Environment Shell.
 *
 * Sprint 1: opens a borderless fullscreen window.
 * Sprint 2: loads the DesktopSurface component that displays the wallpaper.
 */
Window {
    id: root

    visible: true
    flags: Qt.FramelessWindowHint
    visibility: Window.FullScreen
    color: "#0f172a"

    DesktopSurface {
        anchors.fill: parent
    }
}
