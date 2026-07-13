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

    color: "ThemeManager.surfaceColor"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6
        spacing: 12

        Text {
            text: root.terminalManager ? root.terminalManager.currentDirectory : ""
            color: "ThemeManager.textDisabled"
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
            color: "ThemeManager.successColor"
            font.pixelSize: 13
        }
    }
}
