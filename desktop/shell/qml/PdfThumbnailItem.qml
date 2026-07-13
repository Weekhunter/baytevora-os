import QtQuick
import Qt.Pdf as QPdf

/**
 * @brief Single thumbnail item for the Baytevora PDF Studio sidebar.
 *
 * PdfThumbnailItem renders a small preview of one PDF page and highlights
 * itself when selected.
 */
Rectangle {
    id: root

    property var document: null
    property int pageNumber: 0
    property bool selected: false

    signal activated()

    color: root.selected
           ? (ThemeManager.primaryColor)
           : (ThemeManager.surfaceSecondaryColor)
    radius: DesignTokens.radiusSmall
    border.color: ThemeManager.borderColor
    border.width: 1
    height: width * pageAspectRatio

    property real pageAspectRatio: {
        if (!root.document || root.document.pageCount === 0) {
            return 1.414;
        }
        const size = root.document.pagePointSize(root.pageNumber);
        return size.height / size.width;
    }

    QPdf.PdfPageView {
        id: thumbnailPage

        anchors.fill: parent
        anchors.margins: SpacingManager.space4
        document: root.document
        currentPage: root.pageNumber
        renderScale: 0.2
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.activated()
    }
}
