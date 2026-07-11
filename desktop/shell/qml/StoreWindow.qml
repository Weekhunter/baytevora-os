import QtQuick

/**
 * @brief Main window content for the Baytevora Store.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager ? ThemeManager.surfaceColor : "#1e293b"

    property var selectedItem: null

    Row {
        anchors.fill: parent
        spacing: 0

        StoreSidebar {
            id: storeSidebar

            height: parent.height
            onCategorySelected: (category) => root.refreshGrid(category)
        }

        Rectangle {
            width: parent.width - storeSidebar.width
            height: parent.height
            color: ThemeManager ? ThemeManager.surfaceColor : "#1e293b"

            Column {
                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space24 : 24
                spacing: SpacingManager ? SpacingManager.space16 : 16

                SearchBar {
                    id: searchBar

                    onSearchAccepted: root.refreshGrid(storeSidebar.selectedCategory)
                }

                FeaturedSection {
                    id: featuredSection

                    visible: searchBar.text.length === 0 && storeSidebar.selectedCategory === 0
                    model: storeManager ? storeManager.featuredItems : []
                    onOpenDetails: (item) => root.selectedItem = item
                }

                Text {
                    visible: searchBar.text.length === 0 && storeSidebar.selectedCategory === 0
                    text: "All Applications"
                    color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                    font.pixelSize: TypographyManager ? TypographyManager.title : 18
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                    font.weight: Font.DemiBold
                }

                Flickable {
                    width: parent.width
                    height: parent.height - featuredSection.height - searchBar.height - 56
                    contentHeight: applicationGrid.height
                    clip: true
                    visible: root.selectedItem === null

                    ApplicationGrid {
                        id: applicationGrid

                        width: parent.width
                        model: []
                    }
                }

                ApplicationDetails {
                    visible: root.selectedItem !== null
                    itemData: root.selectedItem
                    onBackRequested: root.selectedItem = null
                }
            }
        }
    }

    Component.onCompleted: root.refreshGrid(0)

    function refreshGrid(category) {
        if (searchBar.text.length > 0) {
            applicationGrid.model = storeManager ? storeManager.search(searchBar.text) : [];
            return;
        }
        if (category === 0) {
            applicationGrid.model = storeManager ? storeManager.allItems : [];
        } else {
            applicationGrid.model = storeManager ? storeManager.categoryItems(category) : [];
        }
    }
}
