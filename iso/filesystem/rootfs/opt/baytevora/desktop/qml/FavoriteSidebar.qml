import QtQuick

/**
 * @brief Sidebar for the File Manager showing Favorites, Recent Files, and
 *        standard locations.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        id: sidebarColumn

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space16

        // Favorites section
        Text {
            text: "Favorites"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            font.weight: Font.Medium
        }

        ListView {
            width: parent.width
            height: Math.min(contentHeight, 160)
            spacing: SpacingManager.space4
            clip: true
            model: root.fileSystemModel
                   ? root.fileSystemModel.favoriteManager.favorites
                   : []

            delegate: Rectangle {
                width: ListView.view.width
                height: 28
                color: "transparent"
                radius: DesignTokens.radiusSmall

                Row {
                    anchors.fill: parent
                    spacing: SpacingManager.space8

                    Text {
                        width: parent.width - pinButton.width - parent.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.displayName
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }

                    Text {
                        id: pinButton

                        width: 20
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.pinned ? "★" : "☆"
                        color: ThemeManager.accentColor
                        font.pixelSize: TypographyManager.body

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (root.fileSystemModel) {
                                    root.fileSystemModel.favoriteManager.togglePin(modelData.favoriteId);
                                }
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.fileSystemModel) {
                            root.fileSystemModel.path = modelData.path;
                        }
                    }
                }
            }
        }

        BrowserToolButton {
            label: "Add Current Folder"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.favoriteManager.addFavorite(
                        root.fileSystemModel.path,
                        root.fileSystemModel.currentFolderName);
                }
            }
        }

        // Recent Files section
        Text {
            text: "Recent Files"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            font.weight: Font.Medium
        }

        RecentFilesPanel {
            width: parent.width
            height: 160
            fileSystemModel: root.fileSystemModel
        }

        // Standard Locations section
        Text {
            text: "Locations"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            font.weight: Font.Medium
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
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.fill: parent
                    anchors.leftMargin: SpacingManager.space8
                    verticalAlignment: Text.AlignVCenter
                    text: modelData.name
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    elide: Text.ElideRight
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

        // Mounted Devices section (placeholder)
        Text {
            text: "Mounted Devices"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            font.weight: Font.Medium
        }

        Text {
            width: parent.width
            text: "Device enumeration is reserved for a future sprint."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
        }
    }
}
