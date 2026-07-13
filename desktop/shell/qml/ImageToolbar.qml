import QtQuick
import QtQuick.Dialogs
import QtQuick.Window

/**
 * @brief Image Viewer toolbar with Open, Zoom, Fit, Rotate, Flip, Fullscreen,
 * Slideshow, Metadata, and Print actions.
 */
Rectangle {
    id: root

    property var viewerManager: null
    property var canvasArea: null
    property var metadataPanel: null
    property var slideshowControls: null

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    FileDialog {
        id: openDialog

        title: "Open Image"
        nameFilters: ["Images (*.png *.jpg *.jpeg *.bmp *.gif *.webp)"]
        onAccepted: {
            if (root.viewerManager) {
                root.viewerManager.openImage(selectedFile.toString().replace("file:///", "/"));
            }
        }
    }

    Flickable {
        anchors.fill: parent
        contentWidth: toolRow.width
        clip: true

        Row {
            id: toolRow

            width: childrenRect.width + 2 * (SpacingManager.space8)
            spacing: SpacingManager.space8
            leftPadding: SpacingManager.space8

            ImageToolButton {
                label: "Open"
                onClicked: openDialog.open()
            }

            ImageToolButton {
                label: "Zoom In"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.zoomIn();
                    }
                }
            }

            ImageToolButton {
                label: "Zoom Out"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.zoomOut();
                    }
                }
            }

            ImageToolButton {
                label: "Actual Size"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.actualSize();
                    }
                }
            }

            ImageToolButton {
                label: "Fit Window"
                onClicked: {
                    if (root.viewerManager && root.canvasArea) {
                        root.viewerManager.fitToWindow(root.canvasArea.width, root.canvasArea.height);
                    }
                }
            }

            ImageToolButton {
                label: "Fit Width"
                onClicked: {
                    if (root.viewerManager && root.canvasArea) {
                        root.viewerManager.fitToWidth(root.canvasArea.width);
                    }
                }
            }

            ImageToolButton {
                label: "Fit Height"
                onClicked: {
                    if (root.viewerManager && root.canvasArea) {
                        root.viewerManager.fitToHeight(root.canvasArea.height);
                    }
                }
            }

            ImageToolButton {
                label: "Reset"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.resetZoom();
                        root.viewerManager.resetTransformations();
                    }
                }
            }

            ImageToolButton {
                label: "Rotate Left"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.rotateLeft();
                    }
                }
            }

            ImageToolButton {
                label: "Rotate Right"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.rotateRight();
                    }
                }
            }

            ImageToolButton {
                label: "Flip H"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.flipHorizontal();
                    }
                }
            }

            ImageToolButton {
                label: "Flip V"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.flipVertical();
                    }
                }
            }

            ImageToolButton {
                label: "Fullscreen"
                onClicked: {
                    if (root.Window && root.Window.window) {
                        root.Window.window.visibility = (root.Window.window.visibility === Window.FullScreen)
                                                         ? Window.Windowed : Window.FullScreen;
                    }
                }
            }

            ImageToolButton {
                label: "Slideshow"
                onClicked: {
                    if (root.slideshowControls) {
                        root.slideshowControls.visible = !root.slideshowControls.visible;
                    }
                }
            }

            ImageToolButton {
                label: "Metadata"
                onClicked: {
                    if (root.metadataPanel) {
                        root.metadataPanel.visible = !root.metadataPanel.visible;
                    }
                }
            }

            ImageToolButton {
                label: "Print"
                onClicked: {
                    if (root.viewerManager && root.viewerManager.document
                        && root.viewerManager.document.loaded && root.viewerManager.document.imagePath.length > 0) {
                        root.viewerManager.printImage();
                        if (typeof printManager !== "undefined" && printManager) {
                            printManager.printDocument(root.viewerManager.document.imagePath);
                        }
                    }
                }
            }

            ImageToolButton {
                label: "Previous"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.previousImage();
                    }
                }
            }

            ImageToolButton {
                label: "Next"
                onClicked: {
                    if (root.viewerManager) {
                        root.viewerManager.nextImage();
                    }
                }
            }
        }
    }
}
