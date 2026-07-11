import QtQuick

/**
 * @brief Content area for the Settings application.
 *
 * Shows the title of the currently selected page and delegates the actual page
 * content to SettingsPage.qml.
 */
Rectangle {
    id: root

    property var settingsManager: null

    color: "#f8fafc"

    Column {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 24

        Text {
            id: pageTitle

            text: {
                const pages = root.settingsManager ? root.settingsManager.pages : [];
                const current = root.settingsManager ? root.settingsManager.currentPage : "";
                for (let i = 0; i < pages.length; ++i) {
                    if (pages[i].id === current) {
                        return pages[i].title;
                    }
                }
                return "Settings";
            }
            color: "#0f172a"
            font.pixelSize: 28
            font.weight: Font.DemiBold
        }

        SettingsPage {
            width: parent.width
            height: parent.height - pageTitle.height - 24
            settingsManager: root.settingsManager
        }
    }
}
