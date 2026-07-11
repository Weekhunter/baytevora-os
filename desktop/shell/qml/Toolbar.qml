import QtQuick
import Qt.labs.platform

/**
 * @brief Toolbar for the File Manager.
 *
 * Provides back/forward (disabled for Sprint 12), up, refresh, home, and a
 * read-only current path display. Navigation actions delegate to the
 * FileSystemModel.
 */
Rectangle {
    id: root

    property var fileSystemModel: null
    property var selectedFileNames: []

    color: "#1e293b"

    Row {
        anchors.fill: parent
        anchors.margins: 4
        spacing: 4

        ToolButton {
            symbol: "\u2190"
            enabled: false
        }

        ToolButton {
            symbol: "\u2192"
            enabled: false
        }

        ToolButton {
            symbol: "\u2191"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.cdUp();
                }
            }
        }

        ToolButton {
            symbol: "\u27F3"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.refresh();
                }
            }
        }

        ToolButton {
            symbol: "\u2302"
            onClicked: {
                if (root.fileSystemModel) {
                    const homePath = StandardPaths.standardLocations(StandardPaths.HomeLocation);
                    if (homePath.length > 0) {
                        root.fileSystemModel.path = homePath[0];
                    }
                }
                console.log("[BDE] Home directory opened");
            }
        }

        ToolButton {
            symbol: "\u25A2"
            enabled: root.selectedFileNames.length > 0
            onClicked: {
                if (clipboardManager && root.selectedFileNames.length > 0) {
                    const name = root.selectedFileNames[0];
                    clipboardManager.copyText(name);
                    console.log("[BDE] File name copied: " + name);
                }
            }
        }

        Rectangle {
            // Fill remaining toolbar width after six 32px buttons and spacing.
            width: parent.width - 6 * 32 - 5 * 4
            height: parent.height
            color: "#0f172a"
            radius: 4

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.right: parent.right
                anchors.rightMargin: 8
                text: root.fileSystemModel ? root.fileSystemModel.path : ""
                color: "#e2e8f0"
                font.pixelSize: 13
                elide: Text.ElideLeft
            }
        }
    }
}
