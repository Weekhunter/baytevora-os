import QtQuick

/**
 * @brief Delegate for a single permission rule.
 */
Rectangle {
    id: root

    property var permission: null
    property var permissionManager: null

    height: 56
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusSmall

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space12

        Column {
            width: parent.width - actionRow.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space4

            Text {
                width: parent.width
                text: root.permission ? root.permission.origin : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.Medium
                elide: Text.ElideRight
            }

            Text {
                width: parent.width
                text: root.permission
                      ? "Type: " + root.permission.permissionType + " | State: " + root.permission.state
                      : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                elide: Text.ElideRight
            }
        }

        Row {
            id: actionRow

            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space8

            BrowserToolButton {
                label: "Allow"
                onClicked: {
                    if (root.permissionManager && root.permission) {
                        root.permissionManager.setPermission(
                            root.permission.origin, root.permission.permissionType, "Allow");
                    }
                }
            }

            BrowserToolButton {
                label: "Block"
                onClicked: {
                    if (root.permissionManager && root.permission) {
                        root.permissionManager.setPermission(
                            root.permission.origin, root.permission.permissionType, "Block");
                    }
                }
            }

            BrowserToolButton {
                label: "Reset"
                onClicked: {
                    if (root.permissionManager && root.permission) {
                        root.permissionManager.resetPermission(
                            root.permission.origin, root.permission.permissionType);
                    }
                }
            }
        }
    }
}
