import QtQuick

/**
 * @brief In-window download manager overlay for the browser.
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
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Downloads"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.Medium
                }

                Item {
                    width: parent.width - titleLabel.width - clearButton.width - parent.spacing * 2
                    height: parent.height
                }

                BrowserToolButton {
                    id: clearButton

                    label: "Clear Completed"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if (root.browserManager) {
                            root.browserManager.clearCompletedDownloads();
                        }
                    }
                }

                BrowserToolButton {
                    label: "Close"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: root.visible = false
                }
            }
        }

        BrowserDownloadList {
            width: parent.width
            height: parent.height - header.height
            downloadManager: root.browserManager ? root.browserManager.downloadManager : null
        }
    }
}
