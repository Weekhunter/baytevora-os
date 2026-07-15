#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Defines the editing tool palette for Baytevora PDF Studio.
 *
 * PdfEditorTools is a lightweight namespace-like class that exposes the
 * available annotation and shape tools to QML. It does not own state.
 */
class PdfEditorTools : public QObject {
    Q_OBJECT

public:
    explicit PdfEditorTools(QObject *parent = nullptr);

    enum class ToolType {
        SelectionTool,   /**< Select and manipulate existing annotations. */
        HandTool,        /**< Pan the document view. */
        TextTool,        /**< Add a text annotation. */
        HighlightTool,   /**< Add a highlight annotation. */
        UnderlineTool,   /**< Add an underline annotation. */
        StrikeoutTool,   /**< Add a strikeout annotation. */
        RectangleTool,   /**< Add a rectangle shape. */
        EllipseTool,     /**< Add an ellipse shape. */
        ArrowTool,       /**< Add an arrow shape. */
        LineTool,        /**< Add a straight line. */
        FreehandPen,     /**< Add a freehand ink stroke. */
        StickyNote,      /**< Add a sticky note annotation. */
        StampPlaceholder,    /**< Reserved for future stamp support. */
        SignaturePlaceholder /**< Reserved for future signature support. */
    };
    Q_ENUM(ToolType)
};

} // namespace bos::shell
