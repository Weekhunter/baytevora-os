import QtQuick

/**
 * @brief Card representing a single application in the Baytevora Store.
 */
Rectangle {
    id: root

    property var itemData: null

    signal openDetails(var item)

    width: parent ? parent.width : 240
    height: 220
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space16 : 16
        spacing: SpacingManager ? SpacingManager.space8 : 8

        Rectangle {
            width: 48
            height: 48
            radius: DesignTokens ? DesignTokens.radiusSmall : 4
            color: ThemeManager ? ThemeManager.accentColor : "#38bdf8"

            Text {
                anchors.centerIn: parent
                text: root.itemData ? root.itemData.name.charAt(0).toUpperCase() : "?"
                color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                font.pixelSize: TypographyManager ? TypographyManager.headline : 24
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.Bold
            }
        }

        Text {
            text: root.itemData ? root.itemData.name : ""
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.title : 18
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.DemiBold
        }

        Text {
            text: root.itemData ? root.itemData.developer : ""
            color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
            font.pixelSize: TypographyManager ? TypographyManager.caption : 12
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Text {
            text: root.itemData ? root.itemData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Item {
            width: parent.width
            height: parent.height - y
        }

        InstallButton {
            installed: root.itemData ? root.itemData.installed : false
            onClicked: {
                if (storeManager && root.itemData) {
                    storeManager.requestInstall(root.itemData.packageId);
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.openDetails(root.itemData)
    }
}
