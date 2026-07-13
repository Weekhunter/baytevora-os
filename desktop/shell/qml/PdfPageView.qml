import QtQuick
import Qt.Pdf as QPdf

/**
 * @brief Main page view for Baytevora PDF Studio.
 *
 * PdfPageView renders the current page using Qt PdfQuick, centers it, and
 * provides smooth scrolling through a Flickable wrapper.
 */
Rectangle {
    id: root

    property var viewerManager: null

    color: ThemeManager.backgroundColor

    QPdf.PdfDocument {
        id: pdfDocument

        source: root.viewerManager && root.viewerManager.document
                ? Qt.resolvedUrl(root.viewerManager.document.filePath)
                : ""

        onStatusChanged: {
            if (status === QPdf.PdfDocument.Ready && root.viewerManager) {
                root.viewerManager.updatePageCount(pageCount);
                root.viewerManager.setDocumentLoaded(true);
            } else if (status === QPdf.PdfDocument.Error && root.viewerManager) {
                root.viewerManager.setDocumentLoaded(false);
            }
        }
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        contentWidth: pageContainer.width
        contentHeight: pageContainer.height
        clip: true

        Item {
            id: pageContainer

            width: Math.max(pageView.width, flickable.width)
            height: Math.max(pageView.height, flickable.height)

            QPdf.PdfPageView {
                id: pageView

                anchors.centerIn: parent
                document: pdfDocument
                currentPage: root.viewerManager ? root.viewerManager.currentPage : 0
                renderScale: root.viewerManager ? root.viewerManager.zoomLevel : 1.0
            }
        }
    }
}
