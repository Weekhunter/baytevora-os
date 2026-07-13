import QtQuick

/**
 * @brief Outline tab for the PDF Studio document panel.
 *
 * Shows the PDF outline (table of contents) when available. The current
 * foundation shows a placeholder; navigation hooks are wired for future
 * expansion.
 */
Rectangle {
    id: root

    property var studioManager: null

    width: parent ? parent.width : 260
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor

    Text {
        anchors.centerIn: parent
        text: "Outline not available for this document"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        width: parent.width - SpacingManager.space24
    }
}
