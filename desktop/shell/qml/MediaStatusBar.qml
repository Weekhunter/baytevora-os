import QtQuick

/**
 * @brief Status bar for the Media Player.
 */
Rectangle {
    id: root

    property var mediaManager: null

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
            text: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                  ? root.mediaManager.document.fileName
                  : "No media open"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                  ? root.mediaManager.document.mediaType
                  : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.mediaManager && root.mediaManager.document
                  ? (root.mediaManager.document.playing ? "Playing" : "Paused")
                  : "Stopped"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
