import QtQuick
import BOS.Shell

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

    /** Whether the in-window About dialog is visible. */
    property bool aboutOpen: false

    color: ThemeManager.windowBackground
    border.color: isActive
                  ? (ThemeManager.borderColor)
                  : (ThemeManager.surfaceSecondaryColor)
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
            height: AdaptiveLayoutManager.titleBarHeight
            color: isActive
                  ? (ThemeManager.surfaceColor)
                  : (ThemeManager.backgroundColor)

            Image {
                id: windowIcon

                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space8
                width: 18
                height: 18
                source: BrandingManager.applicationSymbolUrl(root.applicationName)
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 36
                sourceSize.height: 36
                visible: source.toString().length > 0
            }

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: windowIcon.visible ? windowIcon.right : parent.left
                anchors.leftMargin: windowIcon.visible ? SpacingManager.space8 : SpacingManager.space12
                anchors.right: buttonRow.left
                anchors.rightMargin: SpacingManager.space8
                text: root.title
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                elide: Text.ElideRight
            }

            Row {
                id: buttonRow

                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                spacing: 4

                // Milestone E: in-window About button for every application.
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 28
                    height: 28
                    radius: DesignTokens.radiusSmall
                    color: ThemeManager.surfaceSecondaryColor

                    Text {
                        anchors.centerIn: parent
                        text: "?"
                        color: ThemeManager.textSecondary
                        font.pixelSize: 14
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: root.aboutOpen = true
                    }
                }

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

        AboutDialog {
            applicationName: root.applicationName
            open: root.aboutOpen
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
                if (root.applicationName === "Baytevora Store") {
                    return "StoreWindow.qml";
                }
                if (root.applicationName === "Package Manager") {
                    return "PackageManagerWindow.qml";
                }
                if (root.applicationName === "Browser") {
                    return "BrowserWindow.qml";
                }
                if (root.applicationName === "Notes") {
                    return "NotesWindow.qml";
                }
                if (root.applicationName === "Image Viewer") {
                    return "ImageViewerWindow.qml";
                }
                if (root.applicationName === "Calculator") {
                    return "CalculatorWindow.qml";
                }
                if (root.applicationName === "Baytevora PDF Studio") {
                    return "PdfStudioWindow.qml";
                }
                if (root.applicationName === "Archive Manager") {
                    return "ArchiveWindow.qml";
                }
                if (root.applicationName === "Media Player") {
                    return "MediaPlayerWindow.qml";
                }
                if (root.applicationName === "Text Editor") {
                    return "TextEditorWindow.qml";
                }
                if (root.applicationName === "System Monitor") {
                    return "SystemMonitorWindow.qml";
                }
                if (root.applicationName === "Task Manager") {
                    return "TaskManagerWindow.qml";
                }
                if (root.applicationName === "Network Manager") {
                    return "NetworkManagerWindow.qml";
                }
                if (root.applicationName === "Storage Manager") {
                    return "StorageManagerWindow.qml";
                }
                if (root.applicationName === "Print Manager") {
                    return "PrintManagerWindow.qml";
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
