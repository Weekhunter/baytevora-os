import QtQuick

/**
 * @brief Metadata tab for the PDF Studio document panel.
 *
 * Displays PDF metadata when available; otherwise shows "Not available".
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

        LabelRow {
            label: "Title"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.title || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Author"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.author || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Subject"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.subject || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Keywords"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.keywords || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Creator"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.creator || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Producer"
            value: root.studioManager && root.studioManager.document
                ? (root.studioManager.document.producer || "Not available")
                : "Not available"
        }
        LabelRow {
            label: "Created"
            value: root.studioManager && root.studioManager.document && root.studioManager.document.creationDate
                ? root.studioManager.document.creationDate.toLocaleString()
                : "Not available"
        }
        LabelRow {
            label: "Modified"
            value: root.studioManager && root.studioManager.document && root.studioManager.document.modificationDate
                ? root.studioManager.document.modificationDate.toLocaleString()
                : "Not available"
        }
    }
}
