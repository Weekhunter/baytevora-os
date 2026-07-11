import QtQuick
import Qt.labs.platform
import BOS.Shell

/**
 * @brief Main view of the File Manager application.
 *
 * FileManagerWindow fills the content area of a WindowFrame and arranges the
 * toolbar, sidebar, file list, and status bar. The filesystem model is created
 * here so each File Manager window has independent navigation state.
 */
Rectangle {
    id: root

    property int __copyShortcutId: -1
    property int __selectAllShortcutId: -1

    color: "#0f172a"

    Component.onCompleted: {
        if (shortcutManager) {
            __copyShortcutId = shortcutManager.registerShortcut("File Manager Copy", "Ctrl+C",
                                                                   ShortcutContext.Global,
                                                                   "Copy selected filename");
            __selectAllShortcutId = shortcutManager.registerShortcut("File Manager Select All", "Ctrl+A",
                                                                      ShortcutContext.Global,
                                                                      "Select all visible entries");
        }
    }

    Component.onDestruction: {
        if (shortcutManager) {
            if (__copyShortcutId !== -1) shortcutManager.removeShortcut(__copyShortcutId);
            if (__selectAllShortcutId !== -1) shortcutManager.removeShortcut(__selectAllShortcutId);
        }
    }

    Connections {
        target: shortcutManager
        function onShortcutActivated(id) {
            if (id === __copyShortcutId) {
                if (clipboardManager && fileManagerFileList.selectedFileNames.length > 0) {
                    const name = fileManagerFileList.selectedFileNames[0];
                    clipboardManager.copyText(name);
                    console.log("[BDE] File name copied via shortcut: " + name);
                }
            } else if (id === __selectAllShortcutId) {
                fileManagerFileList.selectAllVisible();
            }
        }
    }

    FileSystemModel {
        id: fileSystemModel

        path: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
    }

    Row {
        anchors.fill: parent
        spacing: 0

        Sidebar {
            width: 180
            height: parent.height
            fileSystemModel: fileSystemModel
        }

        Column {
            width: parent.width - 180
            height: parent.height
            spacing: 0

            Toolbar {
                id: fileManagerToolbar

                width: parent.width
                height: 42
                fileSystemModel: fileSystemModel
                selectedFileNames: fileManagerFileList.selectedFileNames
            }

            FileList {
                id: fileManagerFileList

                width: parent.width
                height: parent.height - 42 - 28
                fileSystemModel: fileSystemModel
            }

            StatusBar {
                width: parent.width
                height: 28
                fileSystemModel: fileSystemModel
            }
        }
    }
}
