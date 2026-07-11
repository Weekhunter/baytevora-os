import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/**
 * @brief Toolbar for the Terminal application.
 *
 * Shows the current directory, session status, and a placeholder New Session
 * button. All actions delegate to TerminalManager.
 */
Rectangle {
    id: root

    property var terminalManager: null

    color: "#1e1e1e"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6
        spacing: 12

        Text {
            text: root.terminalManager ? root.terminalManager.currentDirectory : ""
            color: "#94a3b8"
            font.pixelSize: 13
        }

        Item {
            Layout.fillWidth: true
        }

        Button {
            text: "New Session"
            onClicked: {
                if (root.terminalManager) {
                    root.terminalManager.newSession();
                }
                console.log("[BDE] New session requested");
            }
        }

        Text {
            text: root.terminalManager ? root.terminalManager.status : ""
            color: "#22c55e"
            font.pixelSize: 13
        }
    }
}
