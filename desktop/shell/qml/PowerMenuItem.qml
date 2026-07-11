import QtQuick

/**
 * @brief A single power action item in the PowerMenu.
 *
 * Displays the action title and emits activated() when clicked. Disabled items
 * are shown but cannot be activated.
 */
Rectangle {
    id: root

    property string itemTitle: ""
    property string itemDescription: ""
    property bool itemEnabled: true

    signal activated()

    width: parent ? parent.width : 200
    height: 36
    color: "transparent"
    opacity: itemEnabled ? 1.0 : 0.4

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 14
        text: root.itemTitle
        color: "#e2e8f0"
        font.pixelSize: 14
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        enabled: root.itemEnabled
        onClicked: root.activated()
    }
}
