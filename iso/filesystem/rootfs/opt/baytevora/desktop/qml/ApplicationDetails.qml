import QtQuick

/**
 * @brief Full application details panel for the Baytevora Store Phase 2.
 */
Rectangle {
    id: root

    property var itemData: null

    signal backRequested()
    signal openRequested()

    width: parent ? parent.width : 600
    height: parent ? parent.height : 400
    color: ThemeManager.surfaceSecondaryColor
    radius: DesignTokens.radiusMedium

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space24
        spacing: SpacingManager.space16

        Text {
            text: root.itemData ? root.itemData.name : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.Bold
        }

        Text {
            text: root.itemData ? root.itemData.longDescription : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        InfoRow {
            label: "Developer"
            value: root.itemData ? root.itemData.developer : ""
        }

        InfoRow {
            label: "Version"
            value: root.itemData ? root.itemData.latestVersion : ""
        }

        InfoRow {
            label: "Installed Version"
            value: root.itemData && root.itemData.installed
                   ? root.itemData.installedVersion
                   : "Not installed"
        }

        InfoRow {
            label: "Category"
            value: root.itemData && storeManager
                   ? storeManager.categoryName(root.itemData.category)
                   : ""
        }

        InfoRow {
            label: "Size"
            value: root.itemData ? root.itemData.size : ""
        }

        InfoRow {
            label: "Rating"
            value: root.itemData ? root.itemData.rating.toString() : ""
        }

        Text {
            text: "Screenshots"
            visible: root.itemData && root.itemData.screenshots.length > 0
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Flickable {
            visible: root.itemData && root.itemData.screenshots.length > 0
            width: parent.width
            height: 120
            contentWidth: screenshotRow.width
            clip: true

            Row {
                id: screenshotRow

                spacing: SpacingManager.space12

                Repeater {
                    model: root.itemData ? root.itemData.screenshots : []

                    Rectangle {
                        width: 160
                        height: 120
                        radius: DesignTokens.radiusSmall
                        color: ThemeManager.surfaceColor
                        border.color: ThemeManager.borderColor
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "Screenshot"
                            color: ThemeManager.textSecondary
                            font.pixelSize: TypographyManager.caption
                            font.family: TypographyManager.fontFamily
                        }
                    }
                }
            }
        }

        Text {
            text: "Changelog"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.itemData ? root.itemData.changelog : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Row {
            spacing: SpacingManager.space12

            InstallButton {
                installed: root.itemData ? root.itemData.installed : false
                onClicked: {
                    if (storeManager && root.itemData) {
                        storeManager.requestInstall(root.itemData.applicationId);
                    }
                }
            }

            Rectangle {
                visible: root.itemData ? root.itemData.installed : false
                width: openLabel.width + 24
                height: 32
                radius: DesignTokens.radiusSmall
                color: ThemeManager.accentColor

                Text {
                    id: openLabel

                    anchors.centerIn: parent
                    text: "Open"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.openRequested()
                }
            }

            Rectangle {
                visible: root.itemData ? root.itemData.installed : false
                width: removeLabel.width + 24
                height: 32
                radius: DesignTokens.radiusSmall
                color: ThemeManager.surfaceSecondaryColor
                border.color: ThemeManager.borderColor
                border.width: 1

                Text {
                    id: removeLabel

                    anchors.centerIn: parent
                    text: "Remove"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (storeManager && root.itemData) {
                            storeManager.requestRemove(root.itemData.applicationId);
                        }
                    }
                }
            }

            Rectangle {
                width: backLabel.width + 24
                height: 32
                radius: DesignTokens.radiusSmall
                color: ThemeManager.surfaceSecondaryColor
                border.color: ThemeManager.borderColor
                border.width: 1

                Text {
                    id: backLabel

                    anchors.centerIn: parent
                    text: "Back"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.backRequested()
                }
            }
        }
    }
}
