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
    color: "ThemeManager.backgroundColor"

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

    // Sprint 21: global drag feedback overlay that follows the active drag
    // operation. It is rendered above all other desktop content.
    DragOverlay {
        z: 250
    }

    // Sprint 23: session lock overlay. When active it covers the desktop and
    // blocks interaction with running applications.
    LockScreen {
        z: 300
    }

    // Sprint 26.5: single Escape dispatcher. The launcher and notification center
    // previously both registered a global Escape shortcut, which caused a conflict.
    // Launcher now consumes Escape locally when it has focus, and this dispatcher
    // handles Escape for the notification center when no focused overlay consumed it.
    Item {
        anchors.fill: parent
        focus: true
        z: 5

        Keys.onEscapePressed: (event) => {
            if (launcher && launcher.visible) {
                launcher.closeLauncher();
                event.accepted = true;
                return;
            }
            if (notificationManager && notificationManager.notifications.length > 0) {
                notificationManager.clearNotifications();
                event.accepted = true;
            }
        }
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
