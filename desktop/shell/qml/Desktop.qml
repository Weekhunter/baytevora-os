import QtQuick
import QtQuick.Window

/**
 * @brief Root window of the Baytevora Desktop Environment Shell.
 *
 * Sprint 1: opens a borderless fullscreen window.
 * Sprint 2: loads the DesktopSurface component that displays the wallpaper.
 * Sprint 8: adds the Taskbar at the bottom of the screen.
 * Sprint 9: adds the Launcher overlay.
 * Sprint 11: adds the NotificationCenter overlay.
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

    Taskbar {
        id: taskbar

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Launcher {
        anchors.fill: parent
    }

    NotificationCenter {
        anchors.top: parent.top
        anchors.right: parent.right
    }

    // Sprint 20: clicking on the desktop surface while the power menu is open
    // closes the menu. The overlay sits below the taskbar so taskbar controls
    // remain usable.
    MouseArea {
        anchors.fill: parent
        enabled: taskbar.powerMenu.menuOpen
        visible: enabled
        z: 90
        onClicked: {
            taskbar.powerMenu.menuOpen = false;
            taskbar.powerMenu.menuClosed();
        }
    }
}
