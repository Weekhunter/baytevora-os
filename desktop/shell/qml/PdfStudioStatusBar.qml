import QtQuick

/**
 * @brief Baytevora PDF Studio status bar.
 *
 * Shows document status, zoom, current/total page, and annotation count.
 */
Rectangle {
    id: root

    property var studioManager: null

    width: parent ? parent.width : 1000
    height: AdaptiveLayoutManager.titleBarHeight
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width * 0.4
            text: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.loaded
                    ? root.studioManager.document.fileName
                    : root.studioManager.document.error)
                : "No document"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideLeft
        }

        Item {
            width: parent.width * 0.2
            height: parent.height
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.studioManager
                ? root.studioManager.zoomPercentage + " | Page "
                  + (root.studioManager.currentPage + 1) + " / "
                  + root.studioManager.pageCount
                : "100% | Page 0 / 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.studioManager && root.studioManager.annotationManager
                ? root.studioManager.annotationManager.count + " annotations"
                : "0 annotations"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
