import QtQuick
import QtQuick.Controls

/**
 * @brief Folder sidebar for the Notes application.
 *
 * Lists default and user folders, shows note counts, and lets the user select
 * a folder or filter favorites.
 */
Rectangle {
    id: root

    property var notesManager: null
    property string selectedFolder: "All"

    width: 200
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal folderSelected(string folderName)
    signal favoritesSelected()

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
                text: "Folders"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.subheading
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }
        }

        ListView {
            width: parent.width
            height: parent.height - 40 - 36
            clip: true
            model: root.notesManager ? root.notesManager.folders : []

            delegate: Rectangle {
                width: parent.width
                height: 36
                color: (root.selectedFolder === modelData.name)
                       ? (ThemeManager.highlightColor)
                       : "transparent"
                radius: DesignTokens.radiusSmall

                Row {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space12
                    spacing: SpacingManager.space8

                    Text {
                        width: parent.width - folderCountLabel.width - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.name
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }

                    Text {
                        id: folderCountLabel

                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.noteCount
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedFolder = modelData.name;
                        root.folderSelected(modelData.name);
                    }
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 36
            color: (root.selectedFolder === "Favorites")
                   ? (ThemeManager.highlightColor)
                   : "transparent"

            Text {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                verticalAlignment: Text.AlignVCenter
                text: "Favorites"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.selectedFolder = "Favorites";
                    root.favoritesSelected();
                }
            }
        }
    }
}
