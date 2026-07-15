import QtQuick
import Qt.labs.platform
import BOS.Shell

/**
 * @brief Main view of the File Manager application.
 *
 * FileManagerWindow fills the content area of a WindowFrame and arranges the
 * sidebar, toolbar, breadcrumb bar, search bar, file list, and status bar.
 * The filesystem model is created here so each File Manager window has
 * independent navigation state, history, favorites, recent files, and search.
 */
Rectangle {
    id: root

    property int __copyShortcutId: -1
    property int __selectAllShortcutId: -1

    color: ThemeManager.backgroundColor

    Component.onCompleted: {
        if (root.fileSystemModel && typeof notificationManager !== "undefined") {
            root.fileSystemModel.setNotificationManager(notificationManager);
        }
        if (shortcutManager) {
            __copyShortcutId = shortcutManager.registerShortcut("File Manager Copy", "Ctrl+C",
                                                                   ShortcutContext.Global,
                                                                   "Copy selected filename");
            __selectAllShortcutId = shortcutManager.registerShortcut("File Manager Select All", "Ctrl+A",
                                                                      ShortcutContext.Global,
                                                                      "Select all visible entries");
        }
    }

    Component.onDestruction: {
        if (shortcutManager) {
            if (__copyShortcutId !== -1) shortcutManager.removeShortcut(__copyShortcutId);
            if (__selectAllShortcutId !== -1) shortcutManager.removeShortcut(__selectAllShortcutId);
        }
    }

    Connections {
        target: shortcutManager
        function onShortcutActivated(id) {
            if (id === __copyShortcutId) {
                if (clipboardManager && fileManagerFileList.selectedFileNames.length > 0) {
                    const name = fileManagerFileList.selectedFileNames[0];
                    clipboardManager.copyText(name);
                    console.log("[BDE] File name copied via shortcut: " + name);
                }
            } else if (id === __selectAllShortcutId) {
                fileManagerFileList.selectAllVisible();
            }
        }
    }

    FileSystemModel {
        id: fileSystemModel

        path: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
    }

    Row {
        anchors.fill: parent
        spacing: 0

        FavoriteSidebar {
            width: AdaptiveLayoutManager.sidebarWidth
            height: parent.height
            fileSystemModel: fileSystemModel
        }

        Column {
            width: parent.width - (AdaptiveLayoutManager.sidebarWidth)
            height: parent.height
            spacing: 0

            BreadcrumbBar {
                id: breadcrumbBar

                width: parent.width
                fileSystemModel: fileSystemModel
            }

            Toolbar {
                id: fileManagerToolbar

                width: parent.width
                height: AdaptiveLayoutManager.toolbarHeight
                fileSystemModel: fileSystemModel
                selectedFileNames: fileManagerFileList.selectedFileNames
                onShowSearch: searchBar.visible = !searchBar.visible
            }

            SearchBar {
                id: searchBar

                width: parent.width
                height: AdaptiveLayoutManager.toolbarHeight
                visible: false
                fileSystemModel: fileSystemModel
                onSearchRequested: (query, extensionFilter, recursive) => {
                    if (!query) {
                        searchResultsOverlay.visible = false;
                        return;
                    }
                    const results = fileSystemModel.searchManager.search(
                        fileSystemModel.path, query, extensionFilter, recursive);
                    searchResultsModel.clear();
                    for (let i = 0; i < results.length; ++i) {
                        searchResultsModel.append(results[i]);
                    }
                    searchResultsOverlay.visible = true;
                }
            }

            Rectangle {
                width: parent.width
                height: parent.height - fileManagerToolbar.height - statusBar.height - breadcrumbBar.height - (searchBar.visible ? searchBar.height : 0)
                color: ThemeManager.backgroundColor

                FileList {
                    id: fileManagerFileList

                    anchors.fill: parent
                    fileSystemModel: fileSystemModel
                }

                Rectangle {
                    id: searchResultsOverlay

                    anchors.fill: parent
                    color: ThemeManager.backgroundColor
                    visible: false

                    Column {
                        anchors.fill: parent
                        spacing: 0

                        Text {
                            width: parent.width
                            height: 28
                            text: "Search Results"
                            color: ThemeManager.textPrimary
                            font.pixelSize: TypographyManager.body
                            font.family: TypographyManager.fontFamily
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        ListView {
                            width: parent.width
                            height: parent.height - 28
                            clip: true
                            model: ListModel {
                                id: searchResultsModel
                            }

                            delegate: Rectangle {
                                width: ListView.view.width
                                height: 28
                                color: index % 2 === 0
                                    ? (ThemeManager.backgroundColor)
                                    : (ThemeManager.surfaceColor)

                                Row {
                                    anchors.fill: parent
                                    anchors.leftMargin: SpacingManager.space12
                                    spacing: SpacingManager.space8

                                    Text {
                                        width: parent.width * 0.5
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: name
                                        color: ThemeManager.textPrimary
                                        font.pixelSize: TypographyManager.caption
                                        font.family: TypographyManager.fontFamily
                                        elide: Text.ElideRight
                                    }

                                    Text {
                                        width: parent.width * 0.2
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: type
                                        color: ThemeManager.textSecondary
                                        font.pixelSize: TypographyManager.caption
                                        font.family: TypographyManager.fontFamily
                                    }

                                    Text {
                                        width: parent.width * 0.2
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: size
                                        color: ThemeManager.textSecondary
                                        font.pixelSize: TypographyManager.caption
                                        font.family: TypographyManager.fontFamily
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onDoubleClicked: {
                                        if (isFolder) {
                                            fileSystemModel.path = path;
                                        } else {
                                            fileSystemModel.addRecentFile(path);
                                            console.log("[BDE] Open search result: " + name);
                                        }
                                        searchResultsOverlay.visible = false;
                                        searchBar.visible = false;
                                    }
                                }
                            }

                            Text {
                                anchors.centerIn: parent
                                visible: searchResultsModel.count === 0
                                text: "No results"
                                color: ThemeManager.textSecondary
                                font.pixelSize: TypographyManager.caption
                                font.family: TypographyManager.fontFamily
                            }
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            searchResultsOverlay.visible = false;
                            searchBar.visible = false;
                        }
                    }
                }
            }

            StatusBar {
                id: statusBar

                width: parent.width
                fileSystemModel: fileSystemModel
            }
        }
    }
}
