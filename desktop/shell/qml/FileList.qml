import QtQuick
import QtQuick.Controls

/**
 * @brief File list view for the File Manager.
 *
 * Displays name, type, size, and last modified time for each entry in the
 * current directory. Folders are listed before files by the model. Double-clicking
 * a folder navigates into it; double-clicking a file logs a request without
 * launching the file.
 */
Rectangle {
    id: root

    property var fileSystemModel: null
    property int nameColumnWidth: Math.floor(parent.width * 0.45)
    property int typeColumnWidth: Math.floor(parent.width * 0.22)
    property int sizeColumnWidth: Math.floor(parent.width * 0.13)
    property int modifiedColumnWidth: parent.width - nameColumnWidth - typeColumnWidth - sizeColumnWidth - 1
    property var selectedFileNames: []

    color: "#0f172a"

    function selectAllVisible() {
        const names = root.fileSystemModel ? root.fileSystemModel.fileNames() : [];
        root.selectedFileNames = names;
        console.log("[BDE] Select all visible entries: " + names.length);
    }

    function isSelected(name) {
        return root.selectedFileNames.indexOf(name) !== -1;
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Header
        Rectangle {
            width: parent.width
            height: 28
            color: "#1e293b"

            Row {
                anchors.fill: parent
                anchors.leftMargin: 12
                spacing: 0

                HeaderLabel {
                    width: root.nameColumnWidth
                    text: "Name"
                }

                HeaderLabel {
                    width: root.typeColumnWidth
                    text: "Type"
                }

                HeaderLabel {
                    width: root.sizeColumnWidth
                    text: "Size"
                }

                HeaderLabel {
                    width: root.modifiedColumnWidth
                    text: "Last Modified"
                }
            }
        }

        ListView {
            id: fileListView

            width: parent.width
            height: parent.height - 28
            clip: true
            model: root.fileSystemModel

            delegate: Rectangle {
                width: ListView.view.width
                height: 28
                color: {
                    if (root.isSelected(model.name)) {
                        return "#2563EB";
                    }
                    return index % 2 === 0 ? "#0f172a" : "#162032";
                }

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: 12
                    spacing: 0

                    CellLabel {
                        width: root.nameColumnWidth
                        text: model.name
                    }

                    CellLabel {
                        width: root.typeColumnWidth
                        text: model.type
                    }

                    CellLabel {
                        width: root.sizeColumnWidth
                        text: model.size
                    }

                    CellLabel {
                        width: root.modifiedColumnWidth
                        text: Qt.formatDateTime(model.lastModified, "yyyy-MM-dd hh:mm")
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedFileNames = [model.name];
                    }
                    onDoubleClicked: {
                        if (model.isFolder) {
                            const currentPath = root.fileSystemModel.path;
                            const separator = currentPath.endsWith("/") ? "" : "/";
                            root.fileSystemModel.path = currentPath + separator + model.name;
                            console.log("[BDE] Folder entered");
                        } else {
                            console.log("[BDE] File open request: " + model.name);
                        }
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }
    }
}
