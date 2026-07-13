import QtQuick

/**
 * @brief Status bar for the Terminal application.
 *
 * Shows the manager status and the current output line count.
 */
Rectangle {
    id: root

    property var terminalManager: null

    color: "ThemeManager.surfaceColor"

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.terminalManager ? root.terminalManager.status : ""
            color: "ThemeManager.textDisabled"
            font.pixelSize: 12
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.terminalManager ? root.terminalManager.lineCount + " lines" : ""
            color: "ThemeManager.textDisabled"
            font.pixelSize: 12
        }
    }
}
