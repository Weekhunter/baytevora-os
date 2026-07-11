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

    color: "#f1f5f9"

    Column {
        id: sidebarColumn

        anchors.fill: parent
        anchors.margins: 16
        spacing: 4

        Text {
            text: "Settings"
            color: "#0f172a"
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
                    return modelData.id === current ? "#e2e8f0" : "transparent";
                }
                radius: 8

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    text: modelData.title
                    color: "#334155"
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
