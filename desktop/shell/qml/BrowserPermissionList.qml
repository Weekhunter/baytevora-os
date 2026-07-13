import QtQuick

/**
 * @brief Scrollable list of site permission rules.
 */
Rectangle {
    id: root

    property var permissionManager: null

    color: ThemeManager.backgroundColor

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: controls

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space8

                BrowserToolButton {
                    label: "Reset All"
                    onClicked: {
                        if (root.permissionManager) {
                            root.permissionManager.resetAllPermissions();
                        }
                    }
                }
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - controls.height
            anchors.margins: 0
            spacing: SpacingManager.space8
            clip: true
            model: root.permissionManager ? root.permissionManager.permissions : []

            delegate: BrowserPermissionDelegate {
                width: listView.width - (SpacingManager.space24)
                anchors.horizontalCenter: parent.horizontalCenter
                permission: modelData
                permissionManager: root.permissionManager
            }

            Text {
                anchors.centerIn: parent
                visible: listView.count === 0
                text: "No site permissions set"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
