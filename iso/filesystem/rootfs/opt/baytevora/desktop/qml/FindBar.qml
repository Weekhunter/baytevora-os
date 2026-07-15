import QtQuick

/**
 * @brief Placeholder find bar for the Text Editor.
 *
 * Full find/replace functionality is reserved for a future Baytevora Text
 * Studio release.
 */
Rectangle {
    id: root

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: SpacingManager.space12
        text: "Find functionality coming soon"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
    }
}
