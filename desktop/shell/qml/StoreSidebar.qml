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
    color: ThemeManager ? ThemeManager.backgroundColor : "#0f172a"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space16 : 16
        spacing: SpacingManager ? SpacingManager.space24 : 24

        Text {
            text: "Baytevora Store"
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.headline : 24
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.Bold
        }

        CategoryList {
            selectedCategory: root.selectedCategory
            onCategorySelected: (category) => root.categorySelected(category)
        }
    }
}
