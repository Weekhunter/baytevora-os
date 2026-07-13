import QtQuick

/**
 * @brief Displays the loaded image centered, scaled, rotated, and flipped.
 */
Rectangle {
    id: root

    property var viewerManager: null

    color: ThemeManager.backgroundColor

    Flickable {
        id: flickable

        anchors.fill: parent
        contentWidth: image.width
        contentHeight: image.height
        clip: true

        Image {
            id: image

            x: (flickable.width - width) / 2
            y: (flickable.height - height) / 2
            source: root.viewerManager && root.viewerManager.document
                    ? "file://" + root.viewerManager.document.imagePath
                    : ""
            width: sourceSize.width * zoomScale
            height: sourceSize.height * zoomScale
            fillMode: Image.PreserveAspectFit
            visible: root.viewerManager && root.viewerManager.document
                     && root.viewerManager.document.loaded
            smooth: true
            asynchronous: true
            transformOrigin: Item.Center

            transform: [
                Rotation {
                    angle: root.viewerManager && root.viewerManager.document
                           ? root.viewerManager.document.rotation : 0
                },
                Scale {
                    xScale: root.viewerManager && root.viewerManager.document
                            && root.viewerManager.document.flippedHorizontally ? -1 : 1
                    yScale: root.viewerManager && root.viewerManager.document
                            && root.viewerManager.document.flippedVertically ? -1 : 1
                }
            ]

            property double zoomScale: root.viewerManager && root.viewerManager.document
                                       ? root.viewerManager.document.zoomLevel
                                       : 1.0
        }
    }

    ImagePlaceholder {
        anchors.fill: parent
        visible: !image.visible
    }
}
