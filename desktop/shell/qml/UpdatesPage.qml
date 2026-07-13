import QtQuick

/**
 * @brief Updates page for the Baytevora Store Phase 2.
 */
Column {
    id: root

    signal refreshRequested()

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Row {
        width: parent.width
        spacing: SpacingManager.space12

        Text {
            text: "Available Updates"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Item {
            height: parent.height
            width: parent.width - x - refreshButton.width - parent.spacing
        }

        Rectangle {
            id: refreshButton

            width: refreshLabel.width + 24
            height: 32
            radius: DesignTokens.radiusSmall
            color: ThemeManager.accentColor

            Text {
                id: refreshLabel

                anchors.centerIn: parent
                text: "Refresh"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.refreshRequested()
            }
        }
    }

    Repeater {
        model: storeManager ? storeManager.updates : []

        delegate: Rectangle {
            width: parent.width
            height: 64
            radius: DesignTokens.radiusSmall
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                spacing: SpacingManager.space12

                Rectangle {
                    width: 40
                    height: 40
                    radius: DesignTokens.radiusSmall
                    color: ThemeManager.accentColor

                    Text {
                        anchors.centerIn: parent
                        text: modelData.applicationId.charAt(0).toUpperCase()
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.title
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.Bold
                    }
                }

                Column {
                    spacing: SpacingManager.space4

                    Text {
                        text: modelData.applicationId
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.DemiBold
                    }

                    Text {
                        text: modelData.installedVersion + " → " + modelData.availableVersion
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }
            }
        }
    }

    Text {
        visible: storeManager && storeManager.updates.length === 0
        text: "All applications are up to date."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
