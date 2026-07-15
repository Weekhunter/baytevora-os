import QtQuick

/**
 * @brief Main window content for the Baytevora Store Phase 2.
 *
 * StoreWindow arranges the toolbar, category sidebar, content area, and status
 * bar. Each store window shares the same singleton StoreManager so catalog state
 * is consistent across windows while the selected item and current section are
 * window-local.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.surfaceColor

    property var selectedItem: null
    property int currentSection: 0
    property int selectedCategory: 0
    property string searchText: ""

    Column {
        anchors.fill: parent
        spacing: 0

        StoreToolbar {
            id: toolbar

            currentSection: root.currentSection
            searchText: root.searchText
            onSectionSelected: (section) => {
                root.currentSection = section;
                root.selectedItem = null;
            }
            onSearchTextChangedSignal: (text) => {
                root.searchText = text;
                root.currentSection = 0;
                root.selectedItem = null;
            }
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - statusBar.height

            CategorySidebar {
                id: categorySidebar

                visible: root.currentSection === 0 || root.currentSection === 1
                height: parent.height
                selectedCategory: root.selectedCategory
                onCategorySelected: (categoryId) => {
                    root.selectedCategory = categoryId;
                    root.currentSection = 0;
                    root.selectedItem = null;
                }
            }

            Rectangle {
                id: contentArea

                width: parent.width - (categorySidebar.visible ? categorySidebar.width : 0)
                height: parent.height
                color: ThemeManager.surfaceColor

                Column {
                    anchors.fill: parent
                    anchors.margins: SpacingManager.space24
                    spacing: SpacingManager.space16

                    Loader {
                        id: pageLoader

                        width: parent.width
                        height: parent.height

                        sourceComponent: {
                            if (root.selectedItem !== null) {
                                return applicationDetailsComponent;
                            }
                            switch (root.currentSection) {
                            case 0:
                                return homePageComponent;
                            case 1:
                                return homePageComponent;
                            case 2:
                                return installedPageComponent;
                            case 3:
                                return updatesPageComponent;
                            default:
                                return homePageComponent;
                            }
                        }
                    }
                }
            }
        }

        StoreStatusBar {
            id: statusBar

            applicationCount: storeManager ? storeManager.allItems.length : 0
            statusText: ""
        }
    }

    Component {
        id: applicationDetailsComponent

        ApplicationDetails {
            itemData: root.selectedItem
            onBackRequested: root.selectedItem = null
            onOpenRequested: {
                if (typeof applicationManager !== "undefined" && root.selectedItem) {
                    applicationManager.launchApplication(root.selectedItem.name);
                }
            }
        }
    }

    Component {
        id: homePageComponent

        Flickable {
            width: parent.width
            height: parent.height
            contentHeight: homeColumn.height
            clip: true

            Column {
                id: homeColumn

                width: parent.width
                spacing: SpacingManager.space16

                FeaturedSection {
                    visible: root.searchText.length === 0 && root.selectedCategory === 0
                    width: parent.width
                    model: storeManager ? storeManager.featuredItems : []
                    onOpenDetails: (item) => root.selectedItem = item
                }

                Text {
                    visible: root.searchText.length === 0
                    text: root.selectedCategory === 0
                          ? "All Applications"
                          : (storeManager ? storeManager.categoryName(root.selectedCategory) : "Category")
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    visible: root.searchText.length > 0
                    text: "Search Results"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                StoreGrid {
                    width: parent.width
                    model: root.currentGridModel()
                    onOpenDetails: (item) => root.selectedItem = item
                }
            }
        }
    }

    Component {
        id: installedPageComponent

        InstalledApplicationsPage {
            width: parent.width
            height: parent.height
            onOpenDetails: (item) => root.selectedItem = item
        }
    }

    Component {
        id: updatesPageComponent

        UpdatesPage {
            width: parent.width
            height: parent.height
            onRefreshRequested: {
                if (storeManager) {
                    storeManager.refreshUpdates();
                }
            }
        }
    }

    function currentGridModel() {
        if (!storeManager) {
            return [];
        }
        if (root.searchText.length > 0) {
            return storeManager.search(root.searchText);
        }
        if (root.selectedCategory === 0) {
            return storeManager.allItems;
        }
        return storeManager.categoryItems(root.selectedCategory);
    }
}
