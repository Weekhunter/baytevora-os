import QtQuick

/**
 * @brief BDL-styled install button for the Baytevora Store.
 */
Rectangle {
    id: root

    property bool installed: false

    signal clicked()

    width: label.width + 24
    height: 32
    radius: DesignTokens ? DesignTokens.radiusSmall : 4
    color: root.installed
           ? (ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155")
           : (ThemeManager ? ThemeManager.successColor : "#22c55e")

    Text {
        id: label

        anchors.centerIn: parent
        text: root.installed ? "Installed" : "Install"
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.caption : 12
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        font.weight: Font.DemiBold
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
