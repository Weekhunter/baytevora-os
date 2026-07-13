import QtQuick

/**
 * @brief Delegate for a single download item in the Browser Download Manager.
 */
Rectangle {
    id: root

    property var download: null
    property var downloadManager: null

    height: 64
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusSmall

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
                text: root.download ? (root.download.fileName || "Unknown") : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.Medium
                elide: Text.ElideRight
            }

            Text {
                width: parent.width
                text: root.download
                      ? "Size: " + (root.download.totalBytes > 0 ? root.download.totalBytes : "?") + " bytes | State: " + root.download.state
                      : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                elide: Text.ElideRight
            }

            Rectangle {
                width: parent.width
                height: 6
                color: ThemeManager.surfaceSecondaryColor
                radius: 3

                Rectangle {
                    width: parent.width * (root.download ? root.download.progress / 100 : 0)
                    height: parent.height
                    color: ThemeManager.primaryColor
                    radius: 3
                }
            }
        }

        Row {
            id: actionRow

            anchors.verticalCenter: parent.verticalCenter
            spacing: SpacingManager.space8

            BrowserToolButton {
                label: "Open Folder"
                enabled: root.download && root.download.state === "completed"
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    // Placeholder-safe: open folder is reserved for a future sprint.
                }
            }

            BrowserToolButton {
                label: "Pause"
                enabled: root.download && root.download.state === "downloading"
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    if (root.downloadManager && root.download) {
                        root.downloadManager.pauseDownload(root.download.downloadId);
                    }
                }
            }

            BrowserToolButton {
                label: "Resume"
                enabled: root.download && root.download.state === "paused"
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    if (root.downloadManager && root.download) {
                        root.downloadManager.resumeDownload(root.download.downloadId);
                    }
                }
            }

            BrowserToolButton {
                label: "Cancel"
                enabled: root.download && root.download.state !== "completed"
                         && root.download.state !== "cancelled"
                         && root.download.state !== "failed"
                opacity: enabled ? 1.0 : 0.4
                onClicked: {
                    if (root.downloadManager && root.download) {
                        root.downloadManager.cancelDownload(root.download.downloadId);
                    }
                }
            }
        }
    }
}
