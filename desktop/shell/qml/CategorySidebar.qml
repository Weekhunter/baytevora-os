import QtQuick

/**
 * @brief Category sidebar for the Baytevora Store Phase 2.
 */
Rectangle {
    id: root

    property int selectedCategory: 0

    signal categorySelected(int categoryId)

    width: 220
    height: parent ? parent.height : 400
    color: ThemeManager.backgroundColor
    radius: DesignTokens.radiusMedium

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space24

        Text {
            text: "Baytevora Store"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.Bold
        }

        Text {
            text: "Categories"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Repeater {
            model: storeManager ? storeManager.categories : []

            delegate: Rectangle {
                width: parent.width
                height: 36
                radius: DesignTokens.radiusSmall
                color: root.selectedCategory === modelData.categoryId
                       ? (ThemeManager.accentColor)
                       : "transparent"

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: SpacingManager.space12
                    text: modelData.name + " (" + modelData.applicationCount + ")"
                    color: root.selectedCategory === modelData.categoryId
                           ? (ThemeManager.textPrimary)
                           : (ThemeManager.textSecondary)
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: root.selectedCategory === modelData.categoryId ? Font.DemiBold : Font.Normal
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedCategory = modelData.categoryId;
                        root.categorySelected(modelData.categoryId);
                    }
                }
            }
        }
    }
}
