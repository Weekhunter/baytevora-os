import QtQuick

/**
 * @brief Left sidebar of the Baytevora Store.
 *
 * Named StoreSidebar to avoid conflict with the existing file-manager Sidebar.
 */
Rectangle {
    id: root

    property int selectedCategory: 0

    signal categorySelected(int category)

    width: 220
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

        CategoryList {
            selectedCategory: root.selectedCategory
            onCategorySelected: (category) => root.categorySelected(category)
        }
    }
}
