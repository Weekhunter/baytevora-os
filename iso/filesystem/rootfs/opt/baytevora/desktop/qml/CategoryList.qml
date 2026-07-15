import QtQuick

/**
 * @brief Sidebar category list for the Baytevora Store.
 */
Column {
    id: root

    property int selectedCategory: 0

    signal categorySelected(int category)

    spacing: SpacingManager.space8
    width: parent ? parent.width : 200

    Repeater {
        model: storeManager ? storeManager.categories : []

        Rectangle {
            width: root.width
            height: 36
            radius: DesignTokens.radiusSmall
            color: root.selectedCategory === index
                   ? (ThemeManager.accentColor)
                   : "transparent"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager.space12
                text: modelData
                color: root.selectedCategory === index
                       ? (ThemeManager.textPrimary)
                       : (ThemeManager.textSecondary)
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: root.selectedCategory === index ? Font.DemiBold : Font.Normal
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.selectedCategory = index;
                    root.categorySelected(index);
                }
            }
        }
    }
}
