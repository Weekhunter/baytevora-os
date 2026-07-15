import QtQuick
import BOS.Shell

/**
 * @brief Card representing a single application in the Baytevora Store.
 */
Rectangle {
    id: root

    property var itemData: null

    signal openDetails(var item)

    width: parent ? parent.width : 240
    height: 220
    color: ThemeManager.surfaceSecondaryColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space8

        Rectangle {
            width: 48
            height: 48
            radius: DesignTokens.radiusSmall
            color: ThemeManager.surfaceSecondaryColor

            Image {
                id: appIcon

                anchors.fill: parent
                anchors.margins: 4
                source: root.itemData ? BrandingManager.applicationSymbolUrl(root.itemData.name) : ""
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 96
                sourceSize.height: 96
                visible: source.toString().length > 0
            }

            Text {
                anchors.centerIn: parent
                text: root.itemData ? root.itemData.name.charAt(0).toUpperCase() : "?"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.headline
                font.family: TypographyManager.fontFamily
                font.weight: Font.Bold
                visible: !appIcon.visible
            }
        }

        Text {
            text: root.itemData ? root.itemData.name : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.itemData ? root.itemData.developer : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.itemData ? root.itemData.shortDescription : ""
            width: parent.width
            wrapMode: Text.WordWrap
            maximumLineCount: 2
            elide: Text.ElideRight
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Item {
            width: parent.width
            height: parent.height - y
        }

        InstallButton {
            installed: root.itemData ? root.itemData.installed : false
            onClicked: {
                if (storeManager && root.itemData) {
                    storeManager.requestInstall(root.itemData.applicationId);
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.openDetails(root.itemData)
    }
}
