import QtQuick

/**
 * @brief Properties tab for the PDF Studio document panel.
 *
 * Displays the loaded file name, path, page count, current page, and zoom.
 */
Rectangle {
    id: root

    property var studioManager: null

    width: parent ? parent.width : 260
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space8

        LabelRow { label: "File"; value: root.studioManager && root.studioManager.document ? root.studioManager.document.fileName : "-" }
        LabelRow { label: "Path"; value: root.studioManager && root.studioManager.document ? root.studioManager.document.filePath : "-" }
        LabelRow { label: "Pages"; value: root.studioManager ? root.studioManager.pageCount : 0 }
        LabelRow { label: "Current"; value: root.studioManager ? (root.studioManager.currentPage + 1) : 0 }
        LabelRow { label: "Zoom"; value: root.studioManager ? root.studioManager.zoomPercentage : "100%" }
    }
}
