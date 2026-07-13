import QtQuick

/**
 * @brief Playlist sidebar for the Media Player.
 *
 * This sprint only displays the currently opened file. Full playlist support
 * is reserved for a future Baytevora Media Studio release.
 */
Rectangle {
    id: root

    property var mediaManager: null

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
            text: "Playlist"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            width: parent.width
            text: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                  ? root.mediaManager.document.fileName
                  : "No media open"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
        }
    }
}
