import QtQuick

/**
 * @brief The bottom-of-screen taskbar for the BDE Shell.
 *
 * Taskbar provides a dark charcoal bar with a subtle top border. It contains
 * the BOS button on the left, a list of running applications in the center,
 * and a digital clock on the right. It renders above desktop windows so that
 * it remains usable while windows are maximized.
 */
Rectangle {
    id: root

    color: "#1e293b"
    height: 40
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    z: 100

    // Top border
    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: 1
        color: "#475569"
    }

    TaskbarButton {
        id: bosButton

        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: parent.verticalCenter
        width: 48
        text: "BOS"
        active: launcher ? launcher.visible : false
        onClicked: {
            if (launcher) {
                launcher.toggleLauncher()
            }
        }
    }

    RunningApps {
        id: runningApps

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
    }

    Clock {
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
    }
}
