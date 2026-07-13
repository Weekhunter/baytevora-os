import QtQuick
import QtQuick.Controls

/**
 * @brief Metadata panel for the Image Viewer.
 *
 * Displays file name, path, dimensions, format, file size, and timestamps.
 */
Rectangle {
    id: root

    property var viewerManager: null

    width: 260
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    visible: false

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: parent.width
            height: 40
            color: ThemeManager.surfaceSecondaryColor

            Text {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                verticalAlignment: Text.AlignVCenter
                text: "Metadata"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.subheading
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }
        }

        Column {
            width: parent.width
            padding: SpacingManager.space12
            spacing: SpacingManager.space12

            Repeater {
                model: [
                    { label: "File", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.fileName : "" },
                    { label: "Path", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.filePath : "" },
                    { label: "Dimensions", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.resolution : "" },
                    { label: "Format", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.format : "" },
                    { label: "Size", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.fileSize + " bytes" : "" },
                    { label: "Created", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.createdAt : "" },
                    { label: "Modified", value: root.viewerManager && root.viewerManager.metadata ? root.viewerManager.metadata.modifiedAt : "" }
                ]

                Column {
                    width: parent.width
                    spacing: SpacingManager.space4

                    Text {
                        width: parent.width
                        text: modelData.label
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        width: parent.width
                        text: modelData.value
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        wrapMode: Text.WrapAnywhere
                    }
                }
            }
        }
    }
}
