import QtQuick
import Qt.labs.platform

/**
 * @brief Sidebar showing common locations for the File Manager.
 *
 * Clicking an entry navigates the supplied FileSystemModel to the selected
 * directory. Missing locations are ignored.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    color: "#1e293b"

    Column {
        id: sidebarColumn

        anchors.fill: parent
        anchors.margins: 8
        spacing: 2

        Text {
            text: "Locations"
            color: "#94a3b8"
            font.pixelSize: 12
            font.weight: Font.DemiBold
        }

        Repeater {
            model: [
                { name: "Home", location: StandardPaths.HomeLocation },
                { name: "Desktop", location: StandardPaths.DesktopLocation },
                { name: "Documents", location: StandardPaths.DocumentsLocation },
                { name: "Downloads", location: StandardPaths.DownloadLocation },
                { name: "Pictures", location: StandardPaths.PicturesLocation },
                { name: "Music", location: StandardPaths.MusicLocation },
                { name: "Videos", location: StandardPaths.MoviesLocation }
            ]

            delegate: Rectangle {
                width: sidebarColumn.width
                height: 28
                color: "transparent"
                radius: 4

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    text: modelData.name
                    color: "#e2e8f0"
                    font.pixelSize: 13
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        const paths = StandardPaths.standardLocations(modelData.location);
                        if (paths.length > 0 && root.fileSystemModel) {
                            root.fileSystemModel.path = paths[0];
                        }
                    }
                }
            }
        }
    }
}
