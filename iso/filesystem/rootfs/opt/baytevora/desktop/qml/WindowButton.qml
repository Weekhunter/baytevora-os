import QtQuick

/**
 * @brief A small, static title-bar button for window controls.
 *
 * WindowButton displays a simple text symbol and emits clicked(). It has no
 * motion effects, hover styling, or shadows.
 */
Rectangle {
    id: root

    property string symbol: ""

    signal clicked()

    width: 28
    height: 28
    color: "transparent"

    Text {
        anchors.centerIn: parent
        text: root.symbol
        color: "ThemeManager.textSecondary"
        font.pixelSize: 12
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
