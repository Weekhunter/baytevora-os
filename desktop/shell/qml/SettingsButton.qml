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
    color: mouseArea.containsMouse ? "#cbd5e1" : "#e2e8f0"
    radius: 8

    Text {
        id: label

        anchors.centerIn: parent
        text: root.text
        color: "#334155"
        font.pixelSize: 14
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}
