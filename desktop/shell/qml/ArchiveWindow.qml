import QtQuick

/**
 * @brief Main view of the native Archive Manager application.
 *
 * ArchiveWindow fills the content area of a WindowFrame and arranges the
 * toolbar, sidebar, file list, and status bar. Each Archive Manager window
 * owns its own ArchiveManager so archive state stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    ArchiveManager {
        id: archiveManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                archiveManager.setNotificationManager(notificationManager);
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        ArchiveToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            archiveManager: archiveManager
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height

            ArchiveSidebar {
                id: sidebar

                height: parent.height
                archiveManager: archiveManager
            }

            ArchiveFileList {
                id: fileList

                width: parent.width - sidebar.width
                height: parent.height
                archiveManager: archiveManager
            }
        }

        ArchiveStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            archiveManager: archiveManager
        }
    }

    // Keyboard shortcuts.
    Shortcut {
        sequences: ["Ctrl+O"]
        onActivated: toolbar.openDialog.open()
    }

    Shortcut {
        sequences: ["F5"]
        onActivated: archiveManager.refresh()
    }

    Shortcut {
        sequences: ["Delete"]
        onActivated: archiveManager.clearSelection()
    }

    Shortcut {
        sequences: ["Ctrl+A"]
        onActivated: archiveManager.selectAllEntries()
    }

    Shortcut {
        sequences: ["Escape"]
        onActivated: archiveManager.clearSelection()
    }
}
