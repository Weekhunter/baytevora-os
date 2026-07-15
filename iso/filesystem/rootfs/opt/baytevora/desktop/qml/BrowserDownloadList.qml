import QtQuick

/**
 * @brief Scrollable list of active and completed browser downloads.
 */
Rectangle {
    id: root

    property var downloadManager: null

    color: ThemeManager.backgroundColor

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space8
        clip: true
        model: root.downloadManager ? root.downloadManager.downloads : []

        delegate: BrowserDownloadDelegate {
            width: listView.width
            download: modelData
            downloadManager: root.downloadManager
        }

        Text {
            anchors.centerIn: parent
            visible: listView.count === 0
            text: "No downloads"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
