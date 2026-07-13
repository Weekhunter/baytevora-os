import QtQuick

/**
 * @brief Network Manager toolbar with refresh and interface actions.
 */
Rectangle {
    id: root

    property var networkManager: null
    property string selectedInterface: ""

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        NetworkToolButton {
            label: "Refresh"
            onClicked: {
                if (root.networkManager) {
                    root.networkManager.refresh();
                }
            }
        }

        NetworkToolButton {
            label: "Enable"
            onClicked: {
                if (root.networkManager && root.selectedInterface.length > 0) {
                    root.networkManager.enableInterface(root.selectedInterface);
                }
            }
        }

        NetworkToolButton {
            label: "Disable"
            onClicked: {
                if (root.networkManager && root.selectedInterface.length > 0) {
                    root.networkManager.disableInterface(root.selectedInterface);
                }
            }
        }

        NetworkToolButton {
            label: "Connect"
            onClicked: {
                if (root.networkManager && root.selectedInterface.length > 0) {
                    root.networkManager.connectInterface(root.selectedInterface);
                }
            }
        }

        NetworkToolButton {
            label: "Disconnect"
            onClicked: {
                if (root.networkManager && root.selectedInterface.length > 0) {
                    root.networkManager.disconnectInterface(root.selectedInterface);
                }
            }
        }
    }
}
