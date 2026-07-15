import QtQuick
import QtQuick.Controls

/**
 * @brief Note properties dialog.
 *
 * Displays read-only metadata about the active note.
 */
Dialog {
    id: root

    property var notesManager: null

    title: "Note Properties"
    modal: true
    standardButtons: Dialog.Ok

    width: 360
    height: 280
    anchors.centerIn: parent

    Column {
        width: parent.width
        spacing: SpacingManager.space12

        Repeater {
            model: [
                { label: "Title", value: root.notesManager ? root.notesManager.activeNoteTitle : "" },
                { label: "Folder", value: root.notesManager ? root.notesManager.activeNoteFolder : "" },
                { label: "Characters", value: root.notesManager ? String(root.notesManager.characterCount()) : "0" },
                { label: "Words", value: root.notesManager ? String(root.notesManager.wordCount()) : "0" },
                { label: "Last Saved", value: root.notesManager ? root.notesManager.activeNoteUpdatedAt : "" }
            ]

            Row {
                width: parent.width
                spacing: SpacingManager.space8

                Text {
                    width: 100
                    text: modelData.label
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                Text {
                    width: parent.width - 100 - parent.spacing
                    text: modelData.value
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    wrapMode: Text.Wrap
                }
            }
        }

        Row {
            width: parent.width
            spacing: SpacingManager.space16

            CheckBox {
                text: "Pinned"
                checked: root.notesManager ? root.notesManager.activeNotePinned : false
                onClicked: {
                    if (root.notesManager) {
                        root.notesManager.togglePinActiveNote();
                    }
                }
            }

            CheckBox {
                text: "Favorite"
                checked: root.notesManager ? root.notesManager.activeNoteFavorite : false
                onClicked: {
                    if (root.notesManager) {
                        root.notesManager.toggleFavoriteActiveNote();
                    }
                }
            }
        }
    }
}
