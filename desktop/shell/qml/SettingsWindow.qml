import QtQuick

/**
 * @brief Main view of the native Settings application.
 *
 * SettingsWindow fills the content area of a WindowFrame, creates an
 * independent SettingsManager instance, and arranges the navigation sidebar
 * and content area. Each Settings window has its own manager so multiple
 * instances stay isolated.
 */
Rectangle {
    id: root

    color: "ThemeManager.surfaceSecondaryColor"

    SettingsManager {
        id: settingsManager
    }

    Component.onCompleted: {
        if (settingsApplication) {
            const requestedPage = settingsApplication.pendingPage;
            if (requestedPage.length > 0) {
                settingsManager.currentPage = requestedPage;
                settingsApplication.pendingPage = "";
            }
        }
    }

    Row {
        anchors.fill: parent
        spacing: 0

        NavigationSidebar {
            width: 220
            height: parent.height
            settingsManager: settingsManager
        }

        SettingsContent {
            width: parent.width - 220
            height: parent.height
            settingsManager: settingsManager
        }
    }
}
