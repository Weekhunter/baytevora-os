import QtQuick

/**
 * @brief Status bar for the File Manager.
 *
 * Shows the current item count and the current folder name. Both values are
 * bound to the FileSystemModel properties and update automatically.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    color: "#1e293b"

    Row {
        anchors.fill: parent
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        spacing: 16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.fileSystemModel ? root.fileSystemModel.itemCount + " items" : ""
            color: "#94a3b8"
            font.pixelSize: 12
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.fileSystemModel ? root.fileSystemModel.currentFolderName : ""
            color: "#94a3b8"
            font.pixelSize: 12
        }
    }
}
