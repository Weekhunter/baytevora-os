import QtQuick
import QtQuick.Controls

/**
 * @brief Main view of the native Terminal application.
 *
 * TerminalWindow fills the content area of a WindowFrame and arranges the
 * toolbar, terminal output view, and status bar. Each Terminal window creates
 * its own TerminalManager so sessions stay isolated.
 */
Rectangle {
    id: root

    color: "ThemeManager.backgroundColor"

    TerminalManager {
        id: terminalManager
    }

    Column {
        anchors.fill: parent
        spacing: 0

        TerminalToolbar {
            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            terminalManager: terminalManager
        }

        TerminalView {
            width: parent.width
            height: parent.height - (AdaptiveLayoutManager.toolbarHeight) - 24
            terminalManager: terminalManager
        }

        TerminalStatusBar {
            width: parent.width
            height: 24
            terminalManager: terminalManager
        }
    }
}
