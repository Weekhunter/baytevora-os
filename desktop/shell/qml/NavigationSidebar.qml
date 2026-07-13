import QtQuick

/**
 * @brief Navigation sidebar for the Settings application.
 *
 * Lists the available settings pages from SettingsManager and highlights the
 * currently selected page. Selecting a page updates SettingsManager::currentPage.
 */
Rectangle {
    id: root

    property var settingsManager: null

    color: "ThemeManager.surfaceSecondaryColor"

    Column {
        id: sidebarColumn

        anchors.fill: parent
        anchors.margins: AdaptiveLayoutManager.windowPadding
        spacing: 4

        Text {
            text: "Settings"
            color: "ThemeManager.backgroundColor"
            font.pixelSize: 20
            font.weight: Font.DemiBold
        }

        Item {
            width: parent.width
            height: 16
        }

        Repeater {
            model: root.settingsManager ? root.settingsManager.pages : []

            delegate: Rectangle {
                width: sidebarColumn.width
                height: 40
                color: {
                    const current = root.settingsManager ? root.settingsManager.currentPage : "";
                    return modelData.id === current ? "ThemeManager.textSecondary" : "transparent";
                }
                radius: DesignTokens.radiusMedium

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    text: modelData.title
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 15
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.settingsManager) {
                            root.settingsManager.currentPage = modelData.id;
                            console.log("[BDE] Settings page selected: " + modelData.id);
                        }
                    }
                }
            }
        }
    }
}
