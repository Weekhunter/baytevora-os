import QtQuick

/**
 * @brief Minimal light-themed button used inside Settings pages.
 */
Rectangle {
    id: root

    property string text: ""

    signal clicked()

    width: Math.max(100, label.implicitWidth + 32)
    height: 36
    color: mouseArea.containsMouse ? "ThemeManager.textSecondary" : "ThemeManager.textSecondary"
    radius: DesignTokens.radiusMedium

    Text {
        id: label

        anchors.centerIn: parent
        text: root.text
        color: "ThemeManager.surfaceSecondaryColor"
        font.pixelSize: 14
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
