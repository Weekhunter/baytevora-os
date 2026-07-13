import QtQuick

/**
 * @brief Notes toolbar with New Note, Save, Search, Favorite, and Pin actions.
 */
Rectangle {
    id: root

    property var notesManager: null

    signal searchToggled()
    signal propertiesRequested()

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        NotesToolButton {
            label: "New"
            onClicked: {
                if (root.notesManager) {
                    root.notesManager.createNote();
                }
            }
        }

        NotesToolButton {
            label: "Save"
            onClicked: {
                if (root.notesManager) {
                    root.notesManager.save();
                }
            }
        }

        NotesToolButton {
            label: "Search"
            onClicked: root.searchToggled()
        }

        NotesToolButton {
            label: root.notesManager && root.notesManager.activeNoteFavorite ? "Unfavorite" : "Favorite"
            onClicked: {
                if (root.notesManager) {
                    root.notesManager.toggleFavoriteActiveNote();
                }
            }
        }

        NotesToolButton {
            label: root.notesManager && root.notesManager.activeNotePinned ? "Unpin" : "Pin"
            onClicked: {
                if (root.notesManager) {
                    root.notesManager.togglePinActiveNote();
                }
            }
        }

        NotesToolButton {
            label: "Properties"
            onClicked: root.propertiesRequested()
        }
    }
}
