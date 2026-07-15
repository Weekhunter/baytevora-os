import QtQuick

/**
 * @brief Status bar for the Archive Manager.
 */
Rectangle {
    id: root

    property var archiveManager: null

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.archiveManager && root.archiveManager.document && root.archiveManager.document.loaded
                  ? root.archiveManager.document.archiveName
                  : "No archive open"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.archiveManager
                  ? "Selected: " + root.archiveManager.selectedCount
                  : "Selected: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.archiveManager
                  ? "Total: " + root.archiveManager.totalEntries
                  : "Total: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
