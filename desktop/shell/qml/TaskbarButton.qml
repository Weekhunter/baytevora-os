import QtQuick

/**
 * @brief A flat, reusable button for the taskbar.
 *
 * TaskbarButton displays simple text, emits clicked(), and highlights when
 * active. It has no motion effects, hover styling, gradients, or shadows.
 */
Rectangle {
    id: root

    property string text: ""
    property bool active: false

    signal clicked()

    color: active ? "#334155" : "transparent"
    implicitWidth: label.implicitWidth + 24
    height: parent ? parent.height : 40

    Text {
        id: label

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        text: root.text
        color: "#e2e8f0"
        font.pixelSize: 13
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
