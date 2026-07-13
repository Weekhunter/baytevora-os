import QtQuick
import BOS.Shell 1.0

/**
 * @brief Main view of Baytevora PDF Studio.
 *
 * PdfStudioWindow fills the content area of a WindowFrame and arranges the
 * toolbar, thumbnail sidebar, page view with annotation overlay, document
 * panel, and status bar. Each PDF Studio window owns its own PdfStudioManager.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    PdfStudioManager {
        id: studioManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                studioManager.setNotificationManager(notificationManager);
            }

            if (typeof PdfStudioApplication !== "undefined") {
                const pendingPath = PdfStudioApplication.takePendingOpenFile();
                if (pendingPath.length > 0) {
                    studioManager.openDocument(pendingPath);
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        PdfStudioToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            studioManager: studioManager
            pageViewArea: pageViewArea
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height

            PdfSidebar {
                id: sidebar

                height: parent.height
                viewerManager: studioManager
            }

            Rectangle {
                id: pageViewArea

                width: parent.width - sidebar.width - documentPanel.panelWidth
                height: parent.height
                color: ThemeManager.backgroundColor

                PdfPageView {
                    anchors.fill: parent
                    viewerManager: studioManager
                }

                PdfAnnotationOverlay {
                    anchors.fill: parent
                    studioManager: studioManager
                }
            }

            PdfDocumentPanel {
                id: documentPanel

                height: parent.height
                studioManager: studioManager
            }
        }

        PdfStudioStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            studioManager: studioManager
        }
    }

    Shortcut {
        sequences: ["Ctrl+O"]
        onActivated: toolbar.openDialog.open()
    }

    Shortcut {
        sequences: ["PageUp"]
        onActivated: studioManager.previousPage()
    }

    Shortcut {
        sequences: ["PageDown"]
        onActivated: studioManager.nextPage()
    }

    Shortcut {
        sequences: ["Home"]
        onActivated: studioManager.firstPage()
    }

    Shortcut {
        sequences: ["End"]
        onActivated: studioManager.lastPage()
    }

    Shortcut {
        sequences: ["Ctrl++", "Ctrl+="]
        onActivated: studioManager.zoomIn()
    }

    Shortcut {
        sequences: ["Ctrl+-"]
        onActivated: studioManager.zoomOut()
    }

    Shortcut {
        sequences: ["Ctrl+0"]
        onActivated: studioManager.resetZoom()
    }

    Shortcut {
        sequences: ["Ctrl+Z"]
        onActivated: studioManager.undo()
    }

    Shortcut {
        sequences: ["Ctrl+Y", "Ctrl+Shift+Z"]
        onActivated: studioManager.redo()
    }

    Shortcut {
        sequences: ["Delete"]
        onActivated: {
            if (studioManager.annotationManager) {
                const selected = studioManager.annotationManager.annotations.find(
                    a => a.selected);
                if (selected) {
                    studioManager.annotationManager.deleteAnnotation(selected.id);
                }
            }
        }
    }

    Shortcut {
        sequences: ["Esc"]
        onActivated: {
            if (studioManager.annotationManager) {
                studioManager.annotationManager.deselectAllAnnotations();
            }
        }
    }
}
