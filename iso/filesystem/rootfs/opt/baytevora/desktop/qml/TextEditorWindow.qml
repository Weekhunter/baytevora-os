import QtQuick

/**
 * @brief Main view of the native Text Editor application.
 *
 * TextEditorWindow fills the content area of a WindowFrame and arranges the
 * toolbar, find bar, editor area, and status bar. Each Text Editor window owns
 * its own TextEditorManager so document state stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    TextEditorManager {
        id: editorManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                editorManager.setNotificationManager(notificationManager);
            }
            editorManager.newDocument();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        TextToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            editorManager: editorManager
        }

        FindBar {
            id: findBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
        }

        TextEditorArea {
            id: editorArea

            width: parent.width
            height: parent.height - toolbar.height - findBar.height - statusBar.height
            editorManager: editorManager
        }

        TextStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            editorManager: editorManager
        }
    }

    // Keyboard shortcuts.
    Shortcut {
        sequences: ["Ctrl+N"]
        onActivated: editorManager.newDocument()
    }

    Shortcut {
        sequences: ["Ctrl+O"]
        onActivated: toolbar.openDialog.open()
    }

    Shortcut {
        sequences: ["Ctrl+S"]
        onActivated: editorManager.saveDocument()
    }

    Shortcut {
        sequences: ["Ctrl+Shift+S"]
        onActivated: toolbar.saveAsDialog.open()
    }

    Shortcut {
        sequences: ["Ctrl+Z"]
        onActivated: editorManager.undo()
    }

    Shortcut {
        sequences: ["Ctrl+Y"]
        onActivated: editorManager.redo()
    }

    Shortcut {
        sequences: ["Ctrl+X"]
        onActivated: editorManager.cut()
    }

    Shortcut {
        sequences: ["Ctrl+C"]
        onActivated: editorManager.copy()
    }

    Shortcut {
        sequences: ["Ctrl+V"]
        onActivated: editorManager.paste()
    }

    Shortcut {
        sequences: ["Ctrl+A"]
        onActivated: editorManager.selectAll()
    }

    Shortcut {
        sequences: ["Ctrl+F"]
        onActivated: {
            // Placeholder for future find functionality.
        }
    }
}
