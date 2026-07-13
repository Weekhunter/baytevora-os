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

    property alias powerMenu: powerMenu

    color: ThemeManager.taskbarBackground
    height: AdaptiveLayoutManager.taskbarHeight
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    z: 100

    // Top border
    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: 1
        color: ThemeManager.borderColor
    }

    // Clicking on the taskbar outside the power menu closes the menu.
    MouseArea {
        anchors.fill: parent
        enabled: powerMenu.menuOpen
        visible: enabled
        z: 10
        onClicked: {
            powerMenu.menuOpen = false;
            powerMenu.menuClosed();
        }
    }

    TaskbarButton {
        id: bosButton

        anchors.left: parent.left
        anchors.leftMargin: SpacingManager.space8
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
        id: clock

        anchors.right: powerButton.left
        anchors.rightMargin: SpacingManager.space4
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
    }

    TaskbarButton {
        id: powerButton

        anchors.right: parent.right
        anchors.rightMargin: SpacingManager.space8
        anchors.verticalCenter: parent.verticalCenter
        z: 11
        width: 40
        text: "P"
        active: powerMenu ? powerMenu.menuOpen : false
        onClicked: {
            if (powerMenu) {
                powerMenu.menuOpen = !powerMenu.menuOpen;
            }
        }
    }

    PowerMenu {
        id: powerMenu

        anchors.bottom: parent.top
        anchors.right: parent.right
        anchors.rightMargin: SpacingManager.space8
        anchors.bottomMargin: SpacingManager.space4
        z: 11
    }
}
