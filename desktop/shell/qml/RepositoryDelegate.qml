import QtQuick

/**
 * @brief Single repository delegate for RepositoryManager.
 */
Rectangle {
    id: root

    property var repoData: null

    signal enableRequested(string repositoryId)
    signal disableRequested(string repositoryId)
    signal priorityRequested(string repositoryId, int priority)

    width: parent ? parent.width : 600
    height: 64
    radius: DesignTokens.radiusSmall
    color: ThemeManager.surfaceSecondaryColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space12

        Column {
            width: parent.width * 0.5
            spacing: SpacingManager.space4

            Text {
                text: root.repoData ? root.repoData.name : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            Text {
                text: root.repoData
                      ? (root.repoData.enabled ? "Enabled" : "Disabled") + " • Priority " + root.repoData.priority
                      : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                text: root.repoData ? root.repoData.localPath : ""
                width: parent.width
                elide: Text.ElideRight
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }

        Item {
            height: parent.height
            width: parent.width - x - toggleButton.width - parent.spacing
        }

        Rectangle {
            id: toggleButton

            width: toggleLabel.width + 24
            height: 32
            radius: DesignTokens.radiusSmall
            color: root.repoData && root.repoData.enabled
                   ? (ThemeManager.surfaceSecondaryColor)
                   : (ThemeManager.accentColor)

            Text {
                id: toggleLabel

                anchors.centerIn: parent
                text: root.repoData && root.repoData.enabled ? "Disable" : "Enable"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.repoData) {
                        if (root.repoData.enabled) {
                            root.disableRequested(root.repoData.repositoryId);
                        } else {
                            root.enableRequested(root.repoData.repositoryId);
                        }
                    }
                }
            }
        }
    }
}
