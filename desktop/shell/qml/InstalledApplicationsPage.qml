import QtQuick

/**
 * @brief Installed applications page for the Baytevora Store Phase 2.
 */
Column {
    id: root

    signal openDetails(var item)

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Text {
        text: "Installed Applications"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Repeater {
        model: storeManager ? storeManager.installedApplications : []

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
                        text: "Version " + modelData.version
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        text: "Installed: " + modelData.installDate
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    const item = storeManager ? storeManager.item(modelData.applicationId) : null;
                    if (item) {
                        root.openDetails(item);
                    }
                }
            }
        }
    }
}
