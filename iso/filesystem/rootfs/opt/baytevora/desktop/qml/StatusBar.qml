import QtQuick

/**
 * @brief Status bar for the File Manager.
 *
 * Shows the current path, item count, and current folder name. All values are
 * bound to the FileSystemModel properties and update automatically.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    height: AdaptiveLayoutManager.titleBarHeight
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space16

        Text {
            width: parent.width * 0.6
            anchors.verticalCenter: parent.verticalCenter
            text: root.fileSystemModel ? root.fileSystemModel.path : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideLeft
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.fileSystemModel ? root.fileSystemModel.itemCount + " items" : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.fileSystemModel ? root.fileSystemModel.currentFolderName : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
