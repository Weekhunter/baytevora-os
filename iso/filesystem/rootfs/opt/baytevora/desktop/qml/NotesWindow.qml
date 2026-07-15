import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief Main view of the native Notes application.
 *
 * NotesWindow fills the content area of a WindowFrame and arranges the
 * toolbar, folder sidebar, note list, editor, and status bar. Each Notes
 * window creates its own NotesManager so note collections stay isolated unless
 * a .bnote file is opened from the File Manager.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property bool searchVisible: false
    property string folderFilter: "All"

    NotesManager {
        id: notesManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                notesManager.setNotificationManager(notificationManager);
            }

            if (typeof NotesApplication !== "undefined") {
                const pendingPath = NotesApplication.takePendingOpenFile();
                if (pendingPath.length > 0) {
                    notesManager.importNote(pendingPath);
                }
            }
        }
    }

    function noteFilter() {
        if (!root.notesManager) {
            return [];
        }

        if (root.folderFilter === "Favorites") {
            return root.notesManager.searchNotes("", "", true);
        }
        if (root.folderFilter === "All" || root.folderFilter === "") {
            return root.notesManager.notes;
        }
        return root.notesManager.searchNotes("", root.folderFilter, false);
    }

    Column {
        anchors.fill: parent
        spacing: 0

        NotesToolbar {
            id: toolbar

            width: parent.width
            height: 44
            notesManager: notesManager

            onSearchToggled: root.searchVisible = !root.searchVisible
            onPropertiesRequested: propertiesDialog.open()
        }

        NotesSearchBar {
            id: searchBar

            width: parent.width
            visible: root.searchVisible
            notesManager: notesManager

            onResultSelected: function (noteId) {
                notesManager.selectNoteById(noteId);
                root.searchVisible = false;
            }
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height - (searchBar.visible ? searchBar.height : 0)

            FolderSidebar {
                id: folderSidebar

                height: parent.height
                notesManager: notesManager
                selectedFolder: root.folderFilter

                onFolderSelected: function (folderName) {
                    root.folderFilter = folderName;
                }
                onFavoritesSelected: {
                    root.folderFilter = "Favorites";
                }
            }

            NotesSidebar {
                id: sidebar

                height: parent.height
                notesManager: notesManager
                displayedNotes: root.noteFilter()
            }

            NotesEditor {
                id: editor

                width: parent.width - folderSidebar.width - sidebar.width
                height: parent.height
                notesManager: notesManager
            }
        }

        NotesStatusBar {
            id: statusBar

            width: parent.width
            height: 24
            notesManager: notesManager
        }
    }

    NoteProperties {
        id: propertiesDialog

        notesManager: notesManager
    }
}
