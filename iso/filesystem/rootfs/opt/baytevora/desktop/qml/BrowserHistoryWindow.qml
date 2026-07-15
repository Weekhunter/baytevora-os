import QtQuick

/**
 * @brief In-window browsing history manager overlay for the browser.
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
                    text: "History"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.Medium
                }

                Item {
                    width: parent.width - clearButton.width - closeButton.width - parent.spacing * 2
                    height: parent.height
                }

                BrowserToolButton {
                    id: clearButton

                    label: "Clear History"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if (root.browserManager) {
                            root.browserManager.historyManager.clearHistory();
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

        BrowserHistoryList {
            width: parent.width
            height: parent.height - header.height
            historyManager: root.browserManager ? root.browserManager.historyManager : null
            browserManager: root.browserManager
            onEntrySelected: (url) => {
                if (root.browserManager) {
                    root.browserManager.navigate(url);
                }
                root.visible = false;
            }
        }
    }
}
