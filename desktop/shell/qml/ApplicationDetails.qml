import QtQuick

/**
 * @brief Full application details panel for the Baytevora Store.
 */
Rectangle {
    id: root

    property var itemData: null

    signal backRequested()

    width: parent ? parent.width : 600
    height: parent ? parent.height : 400
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space24 : 24
        spacing: SpacingManager ? SpacingManager.space16 : 16

        Text {
            text: root.itemData ? root.itemData.name : ""
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.headline : 24
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.Bold
        }

        Text {
            text: root.itemData ? root.itemData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        InfoRow {
            label: "Developer"
            value: root.itemData ? root.itemData.developer : ""
        }

        InfoRow {
            label: "Version"
            value: root.itemData ? root.itemData.version : ""
        }

        InfoRow {
            label: "Rating"
            value: root.itemData ? root.itemData.rating.toString() : ""
        }

        InfoRow {
            label: "Downloads"
            value: root.itemData ? root.itemData.downloads.toString() : ""
        }

        InfoRow {
            label: "Category"
            value: root.itemData && storeManager
                   ? storeManager.categoryName(root.itemData.category)
                   : ""
        }

        Row {
            spacing: SpacingManager ? SpacingManager.space12 : 12

            InstallButton {
                installed: root.itemData ? root.itemData.installed : false
                onClicked: {
                    if (storeManager && root.itemData) {
                        storeManager.requestInstall(root.itemData.packageId);
                    }
                }
            }

            Rectangle {
                width: backLabel.width + 24
                height: 32
                radius: DesignTokens ? DesignTokens.radiusSmall : 4
                color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
                border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
                border.width: 1

                Text {
                    id: backLabel

                    anchors.centerIn: parent
                    text: "Back"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
