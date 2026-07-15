import QtQuick
import QtQuick.Dialogs
import BOS.Shell 1.0

/**
 * @brief Baytevora PDF Studio toolbar with File, View, Annotate, Shapes,
 * Review, and Export groups.
 */
Rectangle {
    id: root

    property var studioManager: null
    property var pageViewArea: null
    property alias openDialog: openDialog

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 1000
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    FileDialog {
        id: openDialog

        title: "Open PDF"
        nameFilters: ["PDF documents (*.pdf)"]
        onAccepted: {
            if (root.studioManager) {
                root.studioManager.openDocument(selectedFile.toString());
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space12

        // File group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "Open"
                onClicked: openDialog.open()
            }
        }

        // View group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "First"
                onClicked: root.studioManager.firstPage()
            }
            PdfToolButton {
                label: "Prev"
                onClicked: root.studioManager.previousPage()
            }
            PdfToolButton {
                label: "Next"
                onClicked: root.studioManager.nextPage()
            }
            PdfToolButton {
                label: "Last"
                onClicked: root.studioManager.lastPage()
            }
            PdfToolButton {
                label: "Zoom In"
                onClicked: root.studioManager.zoomIn()
            }
            PdfToolButton {
                label: "Zoom Out"
                onClicked: root.studioManager.zoomOut()
            }
            PdfToolButton {
                label: "Fit Width"
                onClicked: {
                    if (root.studioManager && root.pageViewArea) {
                        root.studioManager.fitToWidth(root.pageViewArea.width);
                    }
                }
            }
            PdfToolButton {
                label: "Fit Page"
                onClicked: {
                    if (root.studioManager && root.pageViewArea) {
                        root.studioManager.fitToPage(root.pageViewArea.width,
                                                     root.pageViewArea.height);
                    }
                }
            }
        }

        // Annotate group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "Select"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.SelectionTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.SelectionTool
            }
            PdfToolButton {
                label: "Hand"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.HandTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.HandTool
            }
            PdfToolButton {
                label: "Text"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.TextTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.TextTool
            }
            PdfToolButton {
                label: "Highlight"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.HighlightTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.HighlightTool
            }
            PdfToolButton {
                label: "Underline"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.UnderlineTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.UnderlineTool
            }
            PdfToolButton {
                label: "Strikeout"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.StrikeoutTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.StrikeoutTool
            }
            PdfToolButton {
                label: "Note"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.StickyNote
                onClicked: root.studioManager.currentTool = PdfEditorTools.StickyNote
            }
        }

        // Shapes group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "Rect"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.RectangleTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.RectangleTool
            }
            PdfToolButton {
                label: "Ellipse"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.EllipseTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.EllipseTool
            }
            PdfToolButton {
                label: "Arrow"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.ArrowTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.ArrowTool
            }
            PdfToolButton {
                label: "Line"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.LineTool
                onClicked: root.studioManager.currentTool = PdfEditorTools.LineTool
            }
            PdfToolButton {
                label: "Pen"
                highlighted: root.studioManager && root.studioManager.currentTool === PdfEditorTools.FreehandPen
                onClicked: root.studioManager.currentTool = PdfEditorTools.FreehandPen
            }
        }

        // Review group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "Undo"
                enabled: root.studioManager && root.studioManager.canUndo
                onClicked: root.studioManager.undo()
            }
            PdfToolButton {
                label: "Redo"
                enabled: root.studioManager && root.studioManager.canRedo
                onClicked: root.studioManager.redo()
            }
            PdfToolButton {
                label: "Delete"
                onClicked: {
                    if (!root.studioManager || !root.studioManager.annotationManager) {
                        return;
                    }
                    const selected = root.studioManager.annotationManager.annotations.find(
                        a => a.selected);
                    if (selected) {
                        root.studioManager.annotationManager.deleteAnnotation(selected.id);
                    }
                }
            }
        }

        // Export group
        Row {
            spacing: SpacingManager.space4
            PdfToolButton {
                label: "Print"
                onClicked: {
                    if (root.studioManager && root.studioManager.document
                        && root.studioManager.document.loaded
                        && typeof printManager !== "undefined") {
                        printManager.printDocument(root.studioManager.document.filePath);
                    }
                }
            }
        }
    }
}
