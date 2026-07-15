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
    property url itemIcon: ""
    property bool itemEnabled: true

    signal activated()

    width: parent ? parent.width : 200
    height: 36
    color: "transparent"
    opacity: itemEnabled ? 1.0 : 0.4

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 14
        spacing: 10

        Image {
            width: root.itemIcon.toString().length > 0 ? 18 : 0
            height: 18
            source: root.itemIcon
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 36
            sourceSize.height: 36
            visible: root.itemIcon.toString().length > 0
        }

        Text {
            text: root.itemTitle
            color: ThemeManager.textSecondary
            font.pixelSize: 14
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        enabled: root.itemEnabled
        onClicked: root.activated()
    }
}
