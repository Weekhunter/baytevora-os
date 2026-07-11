import QtQuick

/**
 * @brief Sidebar category list for the Baytevora Store.
 */
Column {
    id: root

    property int selectedCategory: 0

    signal categorySelected(int category)

    spacing: SpacingManager ? SpacingManager.space8 : 8
    width: parent ? parent.width : 200

    Repeater {
        model: storeManager ? storeManager.categories : []

        Rectangle {
            width: root.width
            height: 36
            radius: DesignTokens ? DesignTokens.radiusSmall : 4
            color: root.selectedCategory === index
                   ? (ThemeManager ? ThemeManager.accentColor : "#38bdf8")
                   : "transparent"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: SpacingManager ? SpacingManager.space12 : 12
                text: modelData
                color: root.selectedCategory === index
                       ? (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                       : (ThemeManager ? ThemeManager.textSecondary : "#CBD5E1")
                font.pixelSize: TypographyManager ? TypographyManager.body : 14
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
