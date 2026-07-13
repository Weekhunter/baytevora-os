import QtQuick

/**
 * @brief Browser status bar showing page title, loading state, tab count, and active downloads.
 */
Rectangle {
    id: root

    property var browserManager: null

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        Text {
            id: statusLabel

            text: root.browserManager && root.browserManager.loading ? "Loading..." : "Ready"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.browserManager ? root.browserManager.pageTitle : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width - statusLabel.width - tabCountLabel.width - downloadCountLabel.width - parent.spacing * 3
        }

        Text {
            id: tabCountLabel

            text: root.browserManager ? "Tabs: " + root.browserManager.tabs.length : "Tabs: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            id: downloadCountLabel

            text: root.browserManager && root.browserManager.downloadManager
                  ? "Downloads: " + root.browserManager.downloadManager.activeCount
                  : "Downloads: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
