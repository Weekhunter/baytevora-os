import QtQuick
import QtQuick.Controls

/**
 * @brief Search bar for Notes Phase 2.
 *
 * Provides live title/content search and optional folder/favorite filters.
 */
Rectangle {
    id: root

    property var notesManager: null
    property bool showResults: false

    width: parent ? parent.width : 400
    height: showResults ? 160 : 40
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal resultSelected(int noteId)

    Column {
        anchors.fill: parent
        spacing: 0

        Row {
            width: parent.width
            height: 40
            anchors.margins: SpacingManager.space8

            TextField {
                id: queryField

                width: parent.width - filterButton.width - favoriteButton.width - parent.anchors.margins * 2
                height: parent.height
                placeholderText: "Search notes..."
                color: ThemeManager.textPrimary
                placeholderTextColor: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                background: Rectangle {
                    color: ThemeManager.backgroundColor
                    border.color: ThemeManager.borderColor
                    border.width: 1
                }

                onTextChanged: {
                    root.showResults = queryField.text.length > 0;
                }
            }

            Button {
                id: filterButton

                width: 40
                height: 40
                flat: true
                text: "F"
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                ToolTip.visible: hovered
                ToolTip.text: "Filter by current folder"
            }

            Button {
                id: favoriteButton

                width: 40
                height: 40
                flat: true
                text: "\u2605"
                contentItem: Text {
                    text: parent.text
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                ToolTip.visible: hovered
                ToolTip.text: "Favorites only"
            }
        }

        ListView {
            id: resultsList

            width: parent.width
            height: parent.height - 40
            clip: true
            visible: root.showResults
            model: root.notesManager
                   ? root.notesManager.searchNotes(queryField.text, "", false)
                   : []

            delegate: Rectangle {
                width: parent.width
                height: 36
                color: "transparent"

                Text {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space8
                    verticalAlignment: Text.AlignVCenter
                    text: modelData.title
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    elide: Text.ElideRight
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.resultSelected(modelData.noteId)
                }
            }

            Text {
                anchors.centerIn: parent
                visible: resultsList.model.length === 0
                text: "No results"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
