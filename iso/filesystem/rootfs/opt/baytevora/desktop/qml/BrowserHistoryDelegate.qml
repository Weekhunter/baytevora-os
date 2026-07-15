import QtQuick

/**
 * @brief Delegate for a single history entry.
 */
Rectangle {
    id: root

    property var entry: null
    property var historyManager: null
    property var browserManager: null

    signal openEntry(string url)

    height: 56
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusSmall

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (root.entry && root.entry.url) {
                root.openEntry(root.entry.url);
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
                text: root.entry ? (root.entry.title || "Untitled") : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.Medium
                elide: Text.ElideRight
            }

            Row {
                width: parent.width
                spacing: SpacingManager.space8

                Text {
                    text: root.entry ? root.entry.url : ""
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    elide: Text.ElideRight
                    width: parent.width * 0.6
                }

                Text {
                    text: root.entry
                          ? "Visited: " + Qt.formatDateTime(root.entry.visitTime, "yyyy-MM-dd hh:mm")
                            + " | Count: " + root.entry.visitCount
                          : ""
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    elide: Text.ElideRight
                    width: parent.width * 0.4 - parent.spacing
                }
            }
        }

        Row {
            id: actionRow

            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space8

            BrowserToolButton {
                label: "Open"
                enabled: root.entry && root.entry.url.length > 0
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    if (root.entry && root.entry.url) {
                        root.openEntry(root.entry.url);
                    }
                }
            }

            BrowserToolButton {
                label: "Remove"
                onClicked: {
                    if (root.historyManager && root.entry) {
                        root.historyManager.removeHistoryEntry(root.entry.historyId);
                    }
                }
            }
        }
    }
}
