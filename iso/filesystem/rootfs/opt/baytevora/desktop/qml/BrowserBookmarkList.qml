import QtQuick

/**
 * @brief Bookmark list with folder selection and search.
 */
Rectangle {
    id: root

    property var bookmarkManager: null
    property var browserManager: null
    property string currentFolder: "Bookmarks"
    property string searchQuery: ""

    color: ThemeManager.backgroundColor

    signal bookmarkSelected(string url)

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: controls

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space8

                TextField {
                    id: searchField

                    width: parent.width * 0.5 - parent.spacing
                    height: parent.height
                    placeholderText: "Search bookmarks..."
                    text: root.searchQuery
                    onTextChanged: root.searchQuery = text
                }

                Text {
                    text: "Folder:"
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    anchors.verticalCenter: parent.verticalCenter
                }

                ComboBox {
                    id: folderCombo

                    width: parent.width * 0.3
                    height: parent.height
                    model: root.bookmarkManager ? root.bookmarkManager.folders : ["Bookmarks"]
                    currentIndex: {
                        const folders = root.bookmarkManager ? root.bookmarkManager.folders : ["Bookmarks"];
                        for (let i = 0; i < folders.length; ++i) {
                            if (folders[i] === root.currentFolder) {
                                return i;
                            }
                        }
                        return 0;
                    }
                    onCurrentTextChanged: root.currentFolder = currentText
                }
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - controls.height
            anchors.margins: 0
            spacing: SpacingManager.space8
            clip: true

            model: {
                if (!root.bookmarkManager) {
                    return [];
                }
                const source = root.searchQuery.length > 0
                    ? root.bookmarkManager.searchBookmarks(root.searchQuery)
                    : root.bookmarkManager.bookmarks;
                const result = [];
                for (let i = 0; i < source.length; ++i) {
                    const b = source[i];
                    if (!root.searchQuery && b.folder !== root.currentFolder) {
                        continue;
                    }
                    result.push(b);
                }
                return result;
            }

            delegate: BrowserBookmarkDelegate {
                width: listView.width - (SpacingManager.space24)
                anchors.horizontalCenter: parent.horizontalCenter
                bookmark: modelData
                bookmarkManager: root.bookmarkManager
                browserManager: root.browserManager
                onOpenBookmark: (url) => root.bookmarkSelected(url)
            }

            Text {
                anchors.centerIn: parent
                visible: listView.count === 0
                text: "No bookmarks"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
