import QtQuick

/**
 * @brief BDL-styled tool button for Baytevora PDF Studio toolbar.
 */
Rectangle {
    id: root

    property string label: ""
    property bool highlighted: false

    signal clicked()

    width: buttonLabel.width + (SpacingManager.space20)
    height: parent ? parent.height : 28
    radius: DesignTokens.radiusSmall
    color: !root.enabled
           ? (ThemeManager.surfaceSecondaryColor)
           : root.highlighted
               ? (ThemeManager.primaryColor)
               : mouseArea.containsPress
                   ? (ThemeManager.surfaceSecondaryColor)
                   : (ThemeManager.surfaceSecondaryColor)
    border.color: root.highlighted ? ThemeManager.primaryColor : ThemeManager.borderColor
    border.width: 1
    opacity: root.enabled ? 1.0 : 0.5

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
        enabled: root.enabled
        onClicked: {
            if (root.enabled) {
                root.clicked();
            }
        }
    }
}
