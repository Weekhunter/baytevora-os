import QtQuick

/**
 * @brief Main view of the native System Monitor application.
 *
 * SystemMonitorWindow fills the content area of a WindowFrame and arranges the
 * overview page and status bar. Each System Monitor window owns its own
 * SystemMonitorManager so metrics stay isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    SystemMonitorManager {
        id: monitorManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                monitorManager.setNotificationManager(notificationManager);
            }
            monitorManager.startMonitoring();
        }

        Component.onDestruction: {
            monitorManager.stopMonitoring();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        OverviewPage {
            id: overview

            width: parent.width
            height: parent.height - statusBar.height
            monitorManager: monitorManager
        }

        MonitorStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            systemInfo: monitorManager.info
            monitoring: true
        }
    }
}
