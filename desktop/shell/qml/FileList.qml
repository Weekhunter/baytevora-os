import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief File list view for the File Manager.
 *
 * Displays name, type, size, and last modified time for each entry in the
 * current directory. Folders are listed before files by the model. Double-clicking
 * a folder navigates into it; double-clicking a file adds it to recent files and
 * requests to open it. A context menu provides common file actions.
 */
Rectangle {
    id: root

    property var fileSystemModel: null
    property int nameColumnWidth: Math.floor(parent.width * 0.45)
    property int typeColumnWidth: Math.floor(parent.width * 0.22)
    property int sizeColumnWidth: Math.floor(parent.width * 0.13)
    property int modifiedColumnWidth: parent.width - nameColumnWidth - typeColumnWidth - sizeColumnWidth - 1
    property var selectedFileNames: []

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    function selectAllVisible() {
        const names = root.fileSystemModel ? root.fileSystemModel.fileNames() : [];
        root.selectedFileNames = names;
        console.log("[BDE] Select all visible entries: " + names.length);
    }

    function isSelected(name) {
        return root.selectedFileNames.indexOf(name) !== -1;
    }

    function selectedFilePath(name) {
        if (!root.fileSystemModel || !root.fileSystemModel.path) {
            return "";
        }
        const separator = root.fileSystemModel.path.endsWith("/") ? "" : "/";
        return root.fileSystemModel.path + separator + name;
    }

    function openFileByExtension(path, name) {
        if (typeof applicationManager === "undefined" || !applicationManager) {
            return;
        }
        const lower = name.toLowerCase();
        if (lower.endsWith(".bnote")) {
            applicationManager.openFileWithApplication("Notes", path);
        } else if (lower.endsWith(".png") || lower.endsWith(".jpg")
                   || lower.endsWith(".jpeg") || lower.endsWith(".bmp")
                   || lower.endsWith(".gif") || lower.endsWith(".webp")) {
            applicationManager.openFileWithApplication("Image Viewer", path);
        } else if (lower.endsWith(".pdf")) {
            applicationManager.openFileWithApplication("Baytevora PDF Studio", path);
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Header
        Rectangle {
            width: parent.width
            height: 28
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.leftMargin: SpacingManager.space12
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

            delegate: DropTarget {
                id: fileDropTarget

                width: ListView.view.width
                height: 28
                targetId: model.name
                acceptedTypes: [DragType.DesktopItem, DragType.Application]
                color: {
                    if (root.isSelected(model.name)) {
                        return ThemeManager.primaryColor;
                    }
                    if (dragManager && dragManager.currentTarget === model.name && isAccepted) {
                        return ThemeManager.primaryColor;
                    }
                    return index % 2 === 0
                        ? (ThemeManager.backgroundColor)
                        : (ThemeManager.surfaceColor);
                }

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: SpacingManager.space12
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
                    id: fileMouse

                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    propagateComposedEvents: true

                    property point pressPos: Qt.point(0, 0)
                    property bool dragHappened: false

                    onPressed: {
                        pressPos = Qt.point(mouse.x, mouse.y);
                        dragHappened = false;
                    }
                    onPositionChanged: {
                        const dx = mouse.x - pressPos.x;
                        const dy = mouse.y - pressPos.y;
                        if (!dragHappened && Math.sqrt(dx * dx + dy * dy) > 8) {
                            dragHappened = true;
                            if (dragManager) {
                                dragManager.beginDrag(DragType.FilePath,
                                                      "filemanager-" + model.name,
                                                      model.name);
                            }
                        }
                        if (dragHappened && dragManager) {
                            const globalPos = fileDropTarget.mapToGlobal(mouse.x, mouse.y);
                            dragManager.updatePosition(globalPos.x, globalPos.y);
                        }
                    }
                    onReleased: {
                        if (dragHappened && dragManager && dragManager.active) {
                            dragManager.completeDrop(dragManager.currentTarget);
                        }
                    }
                    onClicked: {
                        if (!dragHappened) {
                            root.selectedFileNames = [model.name];
                        }
                    }
                    onDoubleClicked: {
                        if (model.isFolder) {
                            const currentPath = root.fileSystemModel.path;
                            const separator = currentPath.endsWith("/") ? "" : "/";
                            root.fileSystemModel.path = currentPath + separator + model.name;
                            console.log("[BDE] Folder entered");
                        } else {
                            const filePath = root.selectedFilePath(model.name);
                            root.fileSystemModel.addRecentFile(filePath);
                            root.openFileByExtension(filePath, model.name);
                            console.log("[BDE] File open request: " + model.name);
                        }
                    }
                }

                onDragDropped: {
                    console.log("[BDE] File manager drop accepted on: " + model.name);
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }
    }

    Menu {
        id: contextMenu

        MenuItem {
            text: "Open"
            onTriggered: {
                const name = root.selectedFileNames[0] || "";
                if (!name || !root.fileSystemModel) {
                    return;
                }
                const path = root.selectedFilePath(name);
                const index = root.fileSystemModel.fileNames().indexOf(name);
                const isFolder = index >= 0 ? (root.fileSystemModel.data(root.fileSystemModel.index(index, 0), FileSystemModel.IsFolderRole) || false) : false;
                if (isFolder) {
                    root.fileSystemModel.path = path;
                } else {
                    root.fileSystemModel.addRecentFile(path);
                    root.openFileByExtension(path, name);
                    console.log("[BDE] Open: " + name);
                }
            }
        }

        MenuItem {
            text: "Open With"
            onTriggered: {
                console.log("[BDE] Open With placeholder");
            }
        }

        MenuSeparator {}

        MenuItem {
            text: "Rename"
            onTriggered: {
                console.log("[BDE] Rename placeholder: " + (root.selectedFileNames[0] || ""));
            }
        }

        MenuItem {
            text: "Copy"
            onTriggered: {
                if (clipboardManager && root.selectedFileNames.length > 0) {
                    const name = root.selectedFileNames[0];
                    clipboardManager.copyText(name);
                    console.log("[BDE] Copy: " + name);
                }
            }
        }

        MenuItem {
            text: "Cut"
            onTriggered: {
                console.log("[BDE] Cut placeholder: " + (root.selectedFileNames[0] || ""));
            }
        }

        MenuItem {
            text: "Paste"
            onTriggered: {
                console.log("[BDE] Paste placeholder");
            }
        }

        MenuItem {
            text: "Delete"
            onTriggered: {
                console.log("[BDE] Delete placeholder: " + (root.selectedFileNames[0] || ""));
            }
        }

        MenuSeparator {}

        MenuItem {
            text: "Properties"
            onTriggered: {
                console.log("[BDE] Properties placeholder: " + (root.selectedFileNames[0] || ""));
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        z: 100
        onPressed: {
            if (mouse.button === Qt.RightButton) {
                contextMenu.x = mouse.x;
                contextMenu.y = mouse.y;
                contextMenu.open();
            }
        }
    }
}
