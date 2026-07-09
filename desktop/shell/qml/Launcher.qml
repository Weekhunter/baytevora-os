import QtQuick

/**
 * @brief The Baytevora Launcher overlay and panel.
 *
 * Launcher is a full-screen overlay that appears when launcher.visible is true.
 * A click anywhere outside the panel closes the launcher, and pressing Escape
 * closes it as well. The panel is anchored to the bottom-left of the screen,
 * directly above the taskbar.
 *
 * The launcher has rounded corners, a dark background, and a thin border.
 * It uses no see-through effects, blur, or motion effects.
 */
Item {
    id: root

    anchors.fill: parent
    visible: launcher ? launcher.visible : false
    z: 200
    focus: visible

    Keys.onEscapePressed: {
        if (launcher) {
            launcher.closeLauncher()
        }
    }

    // Full-screen overlay behind the panel. Clicking it closes the launcher.
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (launcher) {
                launcher.closeLauncher()
            }
        }
    }

    // Launcher panel
    Rectangle {
        id: panel

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 40
        anchors.leftMargin: 8
        width: 320
        height: 280
        color: "#1e293b"
        border.color: "#475569"
        border.width: 1
        radius: 8

        // Absorb clicks on the panel so they do not propagate to the overlay.
        MouseArea {
            anchors.fill: parent
        }

        Column {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 16

            LauncherHeader {
                id: header

                width: parent.width
            }

            LauncherGrid {
                width: parent.width
                height: parent.height - header.height - parent.spacing
            }
        }
    }
}
