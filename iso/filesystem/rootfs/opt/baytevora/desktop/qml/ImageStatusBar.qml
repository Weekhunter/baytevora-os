import QtQuick

/**
 * @brief Image Viewer status bar showing zoom level, resolution, and folder index.
 */
Rectangle {
    id: root

    property var viewerManager: null

    height: 24
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space16

        Text {
            text: root.viewerManager && root.viewerManager.document
                  ? root.viewerManager.document.imageName
                  : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.viewerManager && root.viewerManager.document && root.viewerManager.document.loaded
                  ? root.viewerManager.metadata.resolution
                  : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.viewerManager && root.viewerManager.document
                  ? root.viewerManager.document.zoomPercentage
                  : "100%"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.viewerManager && root.viewerManager.document && root.viewerManager.document.loaded
                  && root.viewerManager.slideshow
                  ? String(root.viewerManager.slideshow.currentIndex + 1) + " / " + String(root.viewerManager.slideshow.imageCount)
                  : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
