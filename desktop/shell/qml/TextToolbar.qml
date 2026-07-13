import QtQuick
import QtQuick.Dialogs

/**
 * @brief Text Editor toolbar with document and editing actions.
 */
Rectangle {
    id: root

    property var editorManager: null
    property alias openDialog: openDialog
    property alias saveAsDialog: saveAsDialog

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    FileDialog {
        id: openDialog

        title: "Open Document"
        nameFilters: ["Text files (*.txt *.log *.md *.json *.xml *.ini *.cfg)"]
        onAccepted: {
            if (root.editorManager) {
                root.editorManager.openDocument(selectedFile.toString());
            }
        }
    }

    FileDialog {
        id: saveAsDialog

        title: "Save Document As"
        nameFilters: ["Text files (*.txt *.log *.md *.json *.xml *.ini *.cfg)"]
        fileMode: FileDialog.SaveFile
        onAccepted: {
            if (root.editorManager) {
                root.editorManager.saveDocumentAs(selectedFile.toString());
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        TextToolButton {
            label: "New"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.newDocument();
                }
            }
        }

        TextToolButton {
            label: "Open"
            onClicked: openDialog.open()
        }

        TextToolButton {
            label: "Save"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.saveDocument();
                }
            }
        }

        TextToolButton {
            label: "Save As"
            onClicked: saveAsDialog.open()
        }

        TextToolButton {
            label: "Undo"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.undo();
                }
            }
        }

        TextToolButton {
            label: "Redo"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.redo();
                }
            }
        }

        TextToolButton {
            label: "Cut"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.cut();
                }
            }
        }

        TextToolButton {
            label: "Copy"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.copy();
                }
            }
        }

        TextToolButton {
            label: "Paste"
            onClicked: {
                if (root.editorManager) {
                    root.editorManager.paste();
                }
            }
        }

        TextToolButton {
            label: "Find"
            onClicked: {
                // Placeholder for future find functionality.
            }
        }
    }
}
