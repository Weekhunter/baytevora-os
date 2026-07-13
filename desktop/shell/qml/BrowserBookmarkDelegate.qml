import QtQuick

/**
 * @brief Delegate for a single bookmark item.
 */
Rectangle {
    id: root

    property var bookmark: null
    property var bookmarkManager: null
    property var browserManager: null

    signal openBookmark(string url)

    height: 56
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusSmall

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (root.bookmark && root.bookmark.url) {
                root.openBookmark(root.bookmark.url);
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space12

        Column {
            width: parent.width - actionRow.width - parent.spacing
            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space4

            Text {
                width: parent.width
                text: root.bookmark ? (root.bookmark.title || "Untitled") : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.Medium
                elide: Text.ElideRight
            }

            Text {
                width: parent.width
                text: root.bookmark ? root.bookmark.url : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                elide: Text.ElideRight
            }
        }

        Row {
            id: actionRow

            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space8

            BrowserToolButton {
                label: "Open"
                enabled: root.bookmark && root.bookmark.url.length > 0
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    if (root.bookmark && root.bookmark.url) {
                        root.openBookmark(root.bookmark.url);
                    }
                }
            }

            BrowserToolButton {
                label: "Remove"
                onClicked: {
                    if (root.bookmarkManager && root.bookmark) {
                        root.bookmarkManager.removeBookmark(root.bookmark.bookmarkId);
                    }
                }
            }
        }
    }
}
