import QtQuick

/**
 * @brief BDL-styled install/remove action button for the Baytevora Store.
 */
Rectangle {
    id: root

    property bool installed: false

    signal clicked()

    width: label.width + 24
    height: 32
    radius: DesignTokens.radiusSmall
    color: root.installed
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.accentColor)

    Text {
        id: label

        anchors.centerIn: parent
        text: root.installed ? "Installed" : "Install"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
