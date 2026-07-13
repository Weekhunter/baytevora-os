import QtQuick

/**
 * @brief Sidebar listing notes and highlighting the active note.
 */
Rectangle {
    id: root

    property var notesManager: null
    property var displayedNotes: root.notesManager ? root.notesManager.notes : []

    width: 220
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            width: parent.width
            height: 40
            color: ThemeManager.surfaceSecondaryColor

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                spacing: SpacingManager.space8

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Notes"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.subheading
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: root.notesManager ? root.notesManager.noteCount : 0
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }
        }

        ListView {
            width: parent.width
            height: parent.height - 40
            clip: true
            model: root.displayedNotes

            delegate: NoteItem {
                width: parent.width
                noteTitle: {
                    let t = modelData.title || "Untitled";
                    if (modelData.pinned) t = "\u2605 " + t;
                    if (modelData.favorite) t = "\u2665 " + t;
                    return t;
                }
                selected: root.notesManager && root.notesManager.activeNoteId === modelData.noteId

                onClicked: {
                    if (root.notesManager) {
                        root.notesManager.selectNote(modelData.index);
                    }
                }
            }
        }
    }
}
