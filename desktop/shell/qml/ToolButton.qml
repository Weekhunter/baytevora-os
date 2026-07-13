import QtQuick

/**
 * @brief Minimal toolbar button used by the File Manager toolbar.
 */
Rectangle {
    id: root

    property string symbol: ""
    property bool enabled: true

    signal clicked()

    width: 32
    height: 32
    color: root.enabled && mouseArea.containsMouse ? "ThemeManager.surfaceSecondaryColor" : "transparent"
    radius: DesignTokens.radiusSmall

    Text {
        anchors.centerIn: parent
        text: root.symbol
        color: root.enabled ? "ThemeManager.textSecondary" : "ThemeManager.textDisabled"
        font.pixelSize: 16
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: root.enabled
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
