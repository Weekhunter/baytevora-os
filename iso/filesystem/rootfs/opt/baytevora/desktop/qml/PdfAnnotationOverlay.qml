import QtQuick
import BOS.Shell 1.0

/**
 * @brief Annotation rendering and interaction layer for Baytevora PDF Studio.
 *
 * PdfAnnotationOverlay draws local annotations on top of the current PDF
 * page and handles creation, selection, and movement gestures. Annotation
 * coordinates are expressed in overlay-local pixels.
 */
Rectangle {
    id: root

    property var studioManager: null
    property bool drawing: false
    property real startX: 0
    property real startY: 0
    property real currentX: 0
    property real currentY: 0

    color: "transparent"
    anchors.fill: parent

    function defaultColor(toolType) {
        switch (toolType) {
        case PdfEditorTools.HighlightTool:
        case PdfEditorTools.StickyNote:
            return ThemeManager.warningColor;
        case PdfEditorTools.UnderlineTool:
        case PdfEditorTools.StrikeoutTool:
        case PdfEditorTools.LineTool:
        case PdfEditorTools.ArrowTool:
            return ThemeManager.errorColor;
        case PdfEditorTools.RectangleTool:
        case PdfEditorTools.EllipseTool:
            return ThemeManager.primaryColor;
        case PdfEditorTools.TextTool:
            return ThemeManager.highlightColor;
        case PdfEditorTools.FreehandPen:
            return ThemeManager.accentColor;
        case PdfEditorTools.StampPlaceholder:
            return ThemeManager.successColor;
        case PdfEditorTools.SignaturePlaceholder:
            return ThemeManager.warningColor;
        default:
            return ThemeManager.primaryColor;
        }
    }

    function toolIsClick(toolType) {
        return toolType === PdfEditorTools.TextTool
            || toolType === PdfEditorTools.StickyNote
            || toolType === PdfEditorTools.StampPlaceholder
            || toolType === PdfEditorTools.SignaturePlaceholder;
    }

    function toolIsDrag(toolType) {
        return toolType === PdfEditorTools.HighlightTool
            || toolType === PdfEditorTools.UnderlineTool
            || toolType === PdfEditorTools.StrikeoutTool
            || toolType === PdfEditorTools.RectangleTool
            || toolType === PdfEditorTools.EllipseTool
            || toolType === PdfEditorTools.ArrowTool
            || toolType === PdfEditorTools.LineTool
            || toolType === PdfEditorTools.FreehandPen;
    }

    Repeater {
        model: root.studioManager && root.studioManager.annotationManager
            ? root.studioManager.annotationManager.annotations.filter(a => a.pageNumber === root.studioManager.currentPage)
            : []

        delegate: Item {
            x: modelData.x
            y: modelData.y
            width: Math.max(modelData.width, 4)
            height: Math.max(modelData.height, 4)

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.RectangleTool
                color: "transparent"
                border.color: modelData.color
                border.width: 2
                radius: DesignTokens.radiusSmall
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.EllipseTool
                color: "transparent"
                border.color: modelData.color
                border.width: 2
                radius: width / 2
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.HighlightTool
                color: Qt.rgba(modelData.color.r, modelData.color.g, modelData.color.b, 0.35)
                radius: DesignTokens.radiusSmall
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.StickyNote
                color: modelData.color
                radius: DesignTokens.radiusSmall
                opacity: 0.9

                Text {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space4
                    text: "Note"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.small
                    font.family: TypographyManager.fontFamily
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.TextTool
                color: "transparent"
                border.color: modelData.color
                border.width: 1
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space4
                    text: modelData.contents || "Text"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    wrapMode: Text.WordWrap
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.StampPlaceholder
                color: "transparent"
                border.color: ThemeManager.successColor
                border.width: 2
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.centerIn: parent
                    text: "Stamp"
                    color: ThemeManager.successColor
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.SignaturePlaceholder
                color: "transparent"
                border.color: ThemeManager.warningColor
                border.width: 2
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.centerIn: parent
                    text: "Signature"
                    color: ThemeManager.warningColor
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.UnderlineTool
                color: "transparent"

                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 2
                    color: modelData.color
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.StrikeoutTool
                color: "transparent"

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    height: 2
                    color: modelData.color
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: modelData.type === PdfEditorTools.LineTool
                       || modelData.type === PdfEditorTools.ArrowTool
                       || modelData.type === PdfEditorTools.FreehandPen
                color: "transparent"

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    height: 2
                    color: modelData.color
                }
            }

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: modelData.selected ? ThemeManager.primaryColor : "transparent"
                border.width: modelData.selected ? 2 : 0
            }

            MouseArea {
                anchors.fill: parent
                visible: root.studioManager && root.studioManager.currentTool === PdfEditorTools.SelectionTool
                drag.target: root.studioManager && root.studioManager.currentTool === PdfEditorTools.SelectionTool ? parent : undefined
                drag.axis: Drag.XAndYAxis
                onPressed: {
                    if (root.studioManager && root.studioManager.annotationManager) {
                        root.studioManager.annotationManager.selectAnnotation(modelData.id);
                    }
                }
                onReleased: {
                    if (root.studioManager && root.studioManager.annotationManager) {
                        root.studioManager.annotationManager.moveAnnotation(
                            modelData.id, Qt.rect(parent.x, parent.y, parent.width, parent.height));
                    }
                }
            }
        }
    }

    // Rubber-band preview for drag tools
    Rectangle {
        id: preview

        visible: root.drawing && root.studioManager && root.toolIsDrag(root.studioManager.currentTool)
        x: Math.min(root.startX, root.currentX)
        y: Math.min(root.startY, root.currentY)
        width: Math.abs(root.currentX - root.startX)
        height: Math.abs(root.currentY - root.startY)
        color: "transparent"
        border.color: root.studioManager ? root.defaultColor(root.studioManager.currentTool) : ThemeManager.primaryColor
        border.width: 2
        radius: DesignTokens.radiusSmall
    }

    MouseArea {
        id: canvasMouse

        anchors.fill: parent
        enabled: root.studioManager && root.studioManager.document && root.studioManager.document.loaded

        onPressed: mouse => {
            if (!root.studioManager) {
                return;
            }

            if (root.studioManager.currentTool === PdfEditorTools.SelectionTool) {
                if (root.studioManager.annotationManager) {
                    root.studioManager.annotationManager.deselectAllAnnotations();
                }
                return;
            }

            if (root.toolIsClick(root.studioManager.currentTool)) {
                const color = root.defaultColor(root.studioManager.currentTool);
                root.studioManager.annotationManager.addAnnotation(
                    root.studioManager.currentPage,
                    root.studioManager.currentTool,
                    Qt.rect(mouse.x - 40, mouse.y - 20, 80, 40),
                    color,
                    "",
                    "");
                return;
            }

            if (root.toolIsDrag(root.studioManager.currentTool)) {
                root.drawing = true;
                root.startX = mouse.x;
                root.startY = mouse.y;
                root.currentX = mouse.x;
                root.currentY = mouse.y;
            }
        }

        onPositionChanged: mouse => {
            if (root.drawing) {
                root.currentX = mouse.x;
                root.currentY = mouse.y;
            }
        }

        onReleased: mouse => {
            if (!root.studioManager || !root.drawing) {
                return;
            }

            root.drawing = false;
            const x = Math.min(root.startX, root.currentX);
            const y = Math.min(root.startY, root.currentY);
            const w = Math.max(Math.abs(root.currentX - root.startX), 4);
            const h = Math.max(Math.abs(root.currentY - root.startY), 4);
            if (w < 4 || h < 4) {
                return;
            }

            const color = root.defaultColor(root.studioManager.currentTool);
            let rect = Qt.rect(x, y, w, h);
            if (root.studioManager.currentTool === PdfEditorTools.UnderlineTool
                || root.studioManager.currentTool === PdfEditorTools.StrikeoutTool
                || root.studioManager.currentTool === PdfEditorTools.LineTool
                || root.studioManager.currentTool === PdfEditorTools.ArrowTool) {
                rect = Qt.rect(x, y, w, 4);
            }

            root.studioManager.annotationManager.addAnnotation(
                root.studioManager.currentPage,
                root.studioManager.currentTool,
                rect,
                color,
                "",
                "");
        }
    }
}
