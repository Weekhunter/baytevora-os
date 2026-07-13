import QtQuick
import QtQuick.Dialogs

/**
 * @brief Archive Manager toolbar with Open, Extract All, Extract Selected, and Refresh actions.
 */
Rectangle {
    id: root

    property var archiveManager: null
    property alias openDialog: openDialog

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    FileDialog {
        id: openDialog

        title: "Open Archive"
        nameFilters: ["Archives (*.zip *.tar *.tar.gz *.tgz)"]
        onAccepted: {
            if (root.archiveManager) {
                root.archiveManager.openArchive(selectedFile.toString());
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        ArchiveToolButton {
            label: "Open Archive"
            onClicked: openDialog.open()
        }

        ArchiveToolButton {
            label: "Extract All"
            onClicked: {
                if (root.archiveManager) {
                    root.archiveManager.extractAll();
                }
            }
        }

        ArchiveToolButton {
            label: "Extract Selected"
            onClicked: {
                if (root.archiveManager) {
                    root.archiveManager.extractSelection();
                }
            }
        }

        ArchiveToolButton {
            label: "Refresh"
            onClicked: {
                if (root.archiveManager) {
                    root.archiveManager.refresh();
                }
            }
        }
    }
}
