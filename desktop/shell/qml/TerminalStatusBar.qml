import QtQuick

/**
 * @brief Status bar for the Terminal application.
 *
 * Shows the manager status and the current output line count.
 */
Rectangle {
    id: root

    property var terminalManager: null

    color: "#1e1e1e"

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.terminalManager ? root.terminalManager.status : ""
            color: "#94a3b8"
            font.pixelSize: 12
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.terminalManager ? root.terminalManager.lineCount + " lines" : ""
            color: "#64748b"
            font.pixelSize: 12
        }
    }
}
