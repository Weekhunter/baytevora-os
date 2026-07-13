import QtQuick

/**
 * @brief Dedicated Recent Files panel for the File Manager.
 *
 * Shows the recent files list maintained by RecentFileManager and provides
 * a Clear Recent Files action.
 */
Rectangle {
    id: root

    property var fileSystemModel: null

    color: "transparent"

    Column {
        anchors.fill: parent
        spacing: SpacingManager.space8

        ListView {
            id: recentList

            width: parent.width
            height: Math.min(contentHeight, root.height - clearButton.height - parent.spacing)
            spacing: SpacingManager.space4
            clip: true
            model: root.fileSystemModel
                   ? root.fileSystemModel.recentFileManager.recentFiles
                   : []

            delegate: Rectangle {
                width: recentList.width
                height: 28
                color: "transparent"
                radius: DesignTokens.radiusSmall

                Row {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space8
                    spacing: SpacingManager.space8

                    Text {
                        width: parent.width * 0.5
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData.fileName
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }

                    Text {
                        width: parent.width * 0.4
                        anchors.verticalCenter: parent.verticalCenter
                        text: Qt.formatDateTime(modelData.lastOpened, "yyyy-MM-dd hh:mm")
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.fileSystemModel) {
                            const filePath = modelData.path;
                            const lastSlash = filePath.lastIndexOf("/");
                            const dirPath = lastSlash >= 0 ? filePath.substring(0, lastSlash) : "/";
                            root.fileSystemModel.path = dirPath;
                        }
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                visible: recentList.count === 0
                text: "No recent files"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }

        BrowserToolButton {
            id: clearButton

            label: "Clear Recent Files"
            onClicked: {
                if (root.fileSystemModel) {
                    root.fileSystemModel.recentFileManager.clearRecentFiles();
                }
            }
        }
    }
}
