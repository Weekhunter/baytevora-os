import QtQuick

/**
 * @brief A minimal window frame for the BDE Window Manager framework.
 *
 * WindowFrame renders a simple title bar, background, and border. It is
 * intentionally static in Sprint 5 and avoids any interactive controls or
 * decorative effects.
 */
Rectangle {
    id: root

    /** Window title shown in the title bar. */
    property string title: ""

    /** The name of the application that owns this window. */
    property string applicationName: ""

    /** Whether this window is the active window. */
    property bool isActive: false

    /** Current window state: "normal", "minimized", "maximized", or "closed". */
    property string state: "normal"

    color: ThemeManager ? ThemeManager.windowBackground : "#1e293b"
    border.color: isActive
                  ? (ThemeManager ? ThemeManager.borderColor : "#475569")
                  : (ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155")
    border.width: isActive ? 2 : 1
    z: isActive ? 1 : 0

    MouseArea {
        anchors.fill: parent
        onClicked: {
            // Delegate focus handling to the WindowManager. The window ID is
            // provided by the surrounding Repeater delegate via modelData.id.
            if (windowManager) {
                windowManager.setActiveWindow(modelData.id)
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Title bar
        Rectangle {
            id: titleBar

            width: parent.width
            height: 32
            color: isActive
                  ? (ThemeManager ? ThemeManager.surfaceColor : "#1e293b")
                  : (ThemeManager ? ThemeManager.backgroundColor : "#0f172a")

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager ? SpacingManager.space12 : 12
                anchors.right: buttonRow.left
                anchors.rightMargin: SpacingManager ? SpacingManager.space8 : 8
                text: root.title
                color: ThemeManager ? ThemeManager.textPrimary : "#e2e8f0"
                font.pixelSize: TypographyManager ? TypographyManager.body : 14
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                elide: Text.ElideRight
            }

            Row {
                id: buttonRow

                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height

                WindowButton {
                    symbol: "−"
                    onClicked: windowManager.minimizeWindow(modelData.id)
                }

                WindowButton {
                    symbol: root.state === "maximized" ? "❐" : "□"
                    onClicked: {
                        if (root.state === "maximized") {
                            windowManager.restoreWindow(modelData.id)
                        } else {
                            windowManager.maximizeWindow(modelData.id)
                        }
                    }
                }

                WindowButton {
                    symbol: "×"
                    onClicked: windowManager.closeWindow(modelData.id)
                }
            }
        }

        // Content area. A Loader selects the application-specific UI based on
        // the owning application name; unknown applications get the placeholder.
        Loader {
            width: parent.width
            height: parent.height - titleBar.height
            source: {
                if (root.applicationName === "File Manager") {
                    return "FileManagerWindow.qml";
                }
                if (root.applicationName === "Settings") {
                    return "SettingsWindow.qml";
                }
                if (root.applicationName === "Terminal") {
                    return "TerminalWindow.qml";
                }
                return "";
            }

            Rectangle {
                anchors.fill: parent
                color: root.color
                visible: parent.status !== Loader.Ready
            }
        }
    }
}
