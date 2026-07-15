import QtQuick

/**
 * @brief Main view of the native Image Viewer application.
 *
 * ImageViewerWindow fills the content area of a WindowFrame and arranges the
 * toolbar, slideshow controls, metadata panel, image canvas, and status bar.
 * Each Image Viewer window owns its own ImageViewerManager so document state
 * stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    ImageViewerManager {
        id: viewerManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                viewerManager.setNotificationManager(notificationManager);
            }

            if (typeof ImageViewerApplication !== "undefined") {
                const pendingPath = ImageViewerApplication.takePendingOpenFile();
                if (pendingPath.length > 0) {
                    viewerManager.openImage(pendingPath);
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        ImageToolbar {
            id: toolbar

            width: parent.width
            height: 44
            viewerManager: viewerManager
            canvasArea: canvasArea
            metadataPanel: metadataPanel
            slideshowControls: slideshowControls
        }

        SlideshowControls {
            id: slideshowControls

            width: parent.width
            height: visible ? 44 : 0
            viewerManager: viewerManager
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height
                   - (slideshowControls.visible ? 44 : 0)

            Rectangle {
                id: canvasArea

                width: parent.width - (metadataPanel.visible ? metadataPanel.width : 0)
                height: parent.height

                ImageCanvas {
                    anchors.fill: parent
                    viewerManager: viewerManager
                }
            }

            MetadataPanel {
                id: metadataPanel

                height: parent.height
                viewerManager: viewerManager
            }
        }

        ImageStatusBar {
            id: statusBar

            width: parent.width
            height: 24
            viewerManager: viewerManager
        }
    }
}
