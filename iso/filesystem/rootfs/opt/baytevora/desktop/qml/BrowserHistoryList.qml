import QtQuick

/**
 * @brief Browsing history list with search and date sorting.
 */
Rectangle {
    id: root

    property var historyManager: null
    property var browserManager: null
    property string searchQuery: ""
    property bool sortByDateAscending: false

    color: ThemeManager.backgroundColor

    signal entrySelected(string url)

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

                    width: parent.width * 0.6 - parent.spacing * 2
                    height: parent.height
                    placeholderText: "Search history..."
                    text: root.searchQuery
                    onTextChanged: root.searchQuery = text
                }

                BrowserToolButton {
                    label: root.sortByDateAscending ? "Sort: Oldest first" : "Sort: Newest first"
                    onClicked: root.sortByDateAscending = !root.sortByDateAscending
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
                if (!root.historyManager) {
                    return [];
                }
                const source = root.searchQuery.length > 0
                    ? root.historyManager.searchHistory(root.searchQuery)
                    : root.historyManager.history;
                const sorted = source.slice();
                sorted.sort(function(a, b) {
                    const ta = a.visitTime.getTime ? a.visitTime.getTime() : 0;
                    const tb = b.visitTime.getTime ? b.visitTime.getTime() : 0;
                    return root.sortByDateAscending ? ta - tb : tb - ta;
                });
                return sorted;
            }

            delegate: BrowserHistoryDelegate {
                width: listView.width - (SpacingManager.space24)
                anchors.horizontalCenter: parent.horizontalCenter
                entry: modelData
                historyManager: root.historyManager
                browserManager: root.browserManager
                onOpenEntry: (url) => root.entrySelected(url)
            }

            Text {
                anchors.centerIn: parent
                visible: listView.count === 0
                text: "No history"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }
        }
    }
}
