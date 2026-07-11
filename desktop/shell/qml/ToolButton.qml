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
    color: root.enabled && mouseArea.containsMouse ? "#334155" : "transparent"
    radius: 4

    Text {
        anchors.centerIn: parent
        text: root.symbol
        color: root.enabled ? "#e2e8f0" : "#64748b"
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
