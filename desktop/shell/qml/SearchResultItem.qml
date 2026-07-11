import QtQuick

/**
 * @brief Single search result delegate for the launcher.
 *
 * Displays the title, subtitle, and provider name of a SearchItem. Selecting the
 * item triggers the activated() signal.
 */
Rectangle {
    id: root

    property string resultTitle: ""
    property string resultSubtitle: ""
    property string resultProvider: ""

    signal activated()

    width: parent ? parent.width : 320
    height: 44
    color: "transparent"

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 8

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - parent.spacing
            spacing: 2

            Text {
                text: root.resultTitle
                color: "#e2e8f0"
                font.pixelSize: 14
                font.weight: Font.DemiBold
                width: parent.width
                elide: Text.ElideRight
            }

            Text {
                text: root.resultSubtitle + (root.resultProvider.length > 0 ? "  • " + root.resultProvider : "")
                color: "#94a3b8"
                font.pixelSize: 12
                width: parent.width
                elide: Text.ElideRight
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.activated()
    }
}
