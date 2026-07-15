import QtQuick

/**
 * @brief Main archive file list with headers and entry delegates.
 */
Rectangle {
    id: root

    property var archiveManager: null

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: header

            width: parent.width
            height: 32
            color: ThemeManager.surfaceColor

            Row {
                anchors.fill: parent
                anchors.leftMargin: SpacingManager.space12
                anchors.rightMargin: SpacingManager.space12
                spacing: SpacingManager.space12

                Text {
                    width: parent.width * 0.45
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Name"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Size"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Compressed"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.15
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Modified"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }
        }

        ListView {
            id: entryList

            width: parent.width
            height: parent.height - header.height
            clip: true
            model: root.archiveManager ? root.archiveManager.entries : []

            delegate: ArchiveEntryDelegate {
                entry: modelData
                archiveManager: root.archiveManager
                selected: root.archiveManager ? root.archiveManager.isSelected(index) : false
            }
        }
    }
}
