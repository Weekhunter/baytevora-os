import QtQuick

/**
 * @brief BDL-styled tool button for the Image Viewer toolbar.
 */
Rectangle {
    id: root

    property string label: ""

    signal clicked()

    width: buttonLabel.width + 20
    height: parent ? parent.height : 28
    radius: DesignTokens.radiusSmall
    color: mouseArea.containsPress
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.surfaceSecondaryColor)
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
