import QtQuick

/**
 * @brief In-window bookmark manager overlay for the browser.
 */
Rectangle {
    id: root

    property var browserManager: null
    property bool visible: false

    anchors.fill: parent
    color: ThemeManager.backgroundColor
    visible: root.visible
    z: 100

    Column {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: header

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space8
                spacing: SpacingManager.space8

                Text {
                    id: titleLabel

                    anchors.verticalCenter: parent.verticalCenter
                    text: "Bookmarks"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.Medium
                }

                Item {
                    width: parent.width - titleLabel.width - addButton.width - closeButton.width - parent.spacing * 3
                    height: parent.height
                }

                BrowserToolButton {
                    id: addButton

                    label: "Add Current Page"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if (root.browserManager) {
                            root.browserManager.bookmarkManager.addBookmark(
                                root.browserManager.pageTitle || root.browserManager.currentUrl,
                                root.browserManager.currentUrl);
                        }
                    }
                }

                BrowserToolButton {
                    id: closeButton

                    label: "Close"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: root.visible = false
                }
            }
        }

        BrowserBookmarkList {
            width: parent.width
            height: parent.height - header.height
            bookmarkManager: root.browserManager ? root.browserManager.bookmarkManager : null
            browserManager: root.browserManager
            onBookmarkSelected: (url) => {
                if (root.browserManager) {
                    root.browserManager.navigate(url);
                }
                root.visible = false;
            }
        }
    }
}
