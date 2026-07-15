import QtQuick

/**
 * @brief Slideshow controls for the Image Viewer.
 */
Rectangle {
    id: root

    property var viewerManager: null

    height: 44
    width: parent ? parent.width : 400
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    visible: false

    Row {
        anchors.centerIn: parent
        spacing: SpacingManager.space16

        ImageToolButton {
            label: "Previous"
            onClicked: {
                if (root.viewerManager) {
                    root.viewerManager.previousImage();
                }
            }
        }

        ImageToolButton {
            label: root.viewerManager && root.viewerManager.slideshow && root.viewerManager.slideshow.running ? "Pause" : "Play"
            onClicked: {
                if (!root.viewerManager || !root.viewerManager.slideshow) {
                    return;
                }
                if (root.viewerManager.slideshow.running) {
                    root.viewerManager.slideshow.pause();
                } else {
                    root.viewerManager.slideshow.start();
                }
            }
        }

        ImageToolButton {
            label: "Stop"
            onClicked: {
                if (root.viewerManager && root.viewerManager.slideshow) {
                    root.viewerManager.slideshow.stop();
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
