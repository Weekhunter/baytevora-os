import QtQuick

/**
 * @brief BDL-styled tool button for the Print Manager toolbar.
 */
Rectangle {
    id: root

    property string label: ""

    signal clicked()

    width: buttonLabel.width + (SpacingManager.space20)
    height: parent ? parent.height : 28
    radius: DesignTokens.radiusSmall
    color: mouseArea.containsPress
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.surfaceColor)
    border.color: ThemeManager.borderColor
    border.width: 1

    Text {
        id: buttonLabel

        anchors.centerIn: parent
        text: root.label
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        onClicked: root.clicked()
    }
}
