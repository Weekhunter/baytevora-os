import QtQuick

/**
 * @brief Archive Manager sidebar displaying archive metadata.
 */
Rectangle {
    id: root

    property var archiveManager: null

    width: AdaptiveLayoutManager.sidebarWidth
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space12

        Text {
            width: parent.width
            text: "Archive Information"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Column {
            width: parent.width
            spacing: SpacingManager.space8

            Text {
                width: parent.width
                text: root.archiveManager && root.archiveManager.document && root.archiveManager.document.loaded
                      ? root.archiveManager.document.archiveName
                      : "No archive open"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                wrapMode: Text.Wrap
            }

            Text {
                width: parent.width
                text: root.archiveManager && root.archiveManager.document && root.archiveManager.document.loaded
                      ? "Type: " + root.archiveManager.document.archiveType
                      : "Type: -"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                width: parent.width
                text: root.archiveManager
                      ? "Entries: " + root.archiveManager.totalEntries
                      : "Entries: 0"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                width: parent.width
                text: root.archiveManager && root.archiveManager.document && root.archiveManager.document.loaded
                      ? "Compressed: " + root.archiveManager.totalCompressedSize + " B"
                      : "Compressed: -"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
