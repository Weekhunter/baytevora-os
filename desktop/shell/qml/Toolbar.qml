import QtQuick
import Qt.labs.platform

/**
 * @brief File Manager toolbar with Back, Forward, Up, Refresh, Home, and Search.
 */
Rectangle {
    id: root

    property var fileSystemModel: null
    property var selectedFileNames: []

    signal showSearch()

    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        BrowserToolButton {
            id: backButton

            label: "Back"
            enabled: root.fileSystemModel ? root.fileSystemModel.canGoBack : false
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.goBack();
                }
            }
        }

        BrowserToolButton {
            id: forwardButton

            label: "Forward"
            enabled: root.fileSystemModel ? root.fileSystemModel.canGoForward : false
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.goForward();
                }
            }
        }

        BrowserToolButton {
            id: upButton

            label: "Up"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.cdUp();
                }
            }
        }

        BrowserToolButton {
            id: refreshButton

            label: "Refresh"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.refresh();
                }
            }
        }

        BrowserToolButton {
            id: homeButton

            label: "Home"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.goHome();
                }
            }
        }

        BrowserToolButton {
            id: searchButton

            label: "Search"
            onClicked: root.showSearch()
        }

        BrowserToolButton {
            id: copyButton

            label: "Copy"
            enabled: root.selectedFileNames.length > 0
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (clipboardManager && root.selectedFileNames.length > 0) {
                    const name = root.selectedFileNames[0];
                    clipboardManager.copyText(name);
                    console.log("[BDE] File name copied: " + name);
                }
            }
        }
    }
}
