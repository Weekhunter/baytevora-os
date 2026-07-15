import QtQuick

/**
 * @brief Main view of the native Network Manager application.
 *
 * NetworkManagerWindow fills the content area of a WindowFrame and arranges
 * the toolbar, interface list, details panel, and status bar. Each Network
 * Manager window owns its own NetworkManager so interface state stays
 * isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property var selectedInterfaceData: null

    function formatTime(date) {
        return date.toLocaleTimeString(Qt.locale("en_US"), "hh:mm:ss");
    }

    NetworkManager {
        id: networkManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                networkManager.setNotificationManager(notificationManager);
            }
            networkManager.startMonitoring();
        }

        Component.onDestruction: {
            networkManager.stopMonitoring();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        NetworkToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            networkManager: networkManager
            selectedInterface: interfaceList.selectedInterface
        }

        NetworkInterfaceList {
            id: interfaceList

            width: parent.width
            height: parent.height - toolbar.height - detailsPanel.height - statusBar.height
            networkManager: networkManager

            onInterfaceSelected: function (interfaceName) {
                root.selectedInterfaceData = networkManager.interfaces.find(function (iface) {
                    return iface.interfaceName === interfaceName;
                });
            }
        }

        NetworkDetails {
            id: detailsPanel

            width: parent.width
            height: 160
            interfaceData: root.selectedInterfaceData
        }

        NetworkStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            networkManager: networkManager
            lastRefresh: root.formatTime(new Date())
        }
    }

    Connections {
        target: networkManager

        function onInterfacesChanged() {
            statusBar.lastRefresh = root.formatTime(new Date());
        }
    }
}
