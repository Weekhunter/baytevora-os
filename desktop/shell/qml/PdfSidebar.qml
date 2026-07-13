import QtQuick
import Qt.Pdf as QPdf

/**
 * @brief Thumbnail sidebar for Baytevora PDF Studio.
 *
 * PdfSidebar displays a scrollable list of page thumbnails. Selecting a
 * thumbnail navigates to that page.
 */
Rectangle {
    id: root

    property var viewerManager: null

    width: AdaptiveLayoutManager.sidebarWidth
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    QPdf.PdfDocument {
        id: thumbnailDocument

        source: root.viewerManager && root.viewerManager.document
                ? Qt.resolvedUrl(root.viewerManager.document.filePath)
                : ""
    }

    ListView {
        id: thumbnailList

        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8
        model: root.viewerManager ? root.viewerManager.pageCount : 0
        clip: true

        delegate: PdfThumbnailItem {
            width: thumbnailList.width - (SpacingManager.space16)
            document: thumbnailDocument
            pageNumber: index
            selected: root.viewerManager && root.viewerManager.currentPage === index
            onActivated: {
                if (root.viewerManager) {
                    root.viewerManager.goToPage(index);
                }
            }
        }
    }
}
