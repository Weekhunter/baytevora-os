import QtQuick

/**
 * @brief Horizontal tab bar for the browser window.
 */
Rectangle {
    id: root

    property var browserManager: null

    height: AdaptiveLayoutManager.tabBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        id: tabsRow

        anchors.fill: parent
        anchors.margins: SpacingManager.space4
        spacing: SpacingManager.space4

        Repeater {
            model: root.browserManager ? root.browserManager.tabs : []

            BrowserTabButton {
                tab: modelData
                active: root.browserManager && modelData
                        ? modelData.tabId === root.browserManager.activeTabId
                        : false
                onTabSelected: {
                    if (modelData) {
                        root.browserManager.switchTab(modelData.tabId);
                    }
                }
                onTabClosed: {
                    if (modelData) {
                        root.browserManager.closeTab(modelData.tabId);
                    }
                }
                onTabMoved: function (newIndex) {
                    if (root.browserManager && modelData) {
                        const fromIndex = index;
                        if (fromIndex !== newIndex) {
                            root.browserManager.moveTab(fromIndex, newIndex);
                        }
                    }
                }
            }
        }

        BrowserToolButton {
            label: "+"
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.newTab();
                }
            }
        }
    }
}
