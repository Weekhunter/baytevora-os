import QtQuick

/**
 * @brief Main view of the native Storage Manager application.
 *
 * StorageManagerWindow fills the content area of a WindowFrame and arranges
 * the toolbar, device list, partition table, details panel, and status bar.
 * Each Storage Manager window owns its own StorageManager so storage state
 * stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property var selectedDevice: null

    function formatTime(date) {
        return date.toLocaleTimeString(Qt.locale("en_US"), "hh:mm:ss");
    }

    function devicePartitions(deviceName) {
        if (!storageManager || !deviceName) {
            return [];
        }
        return storageManager.partitions.filter(function (partition) {
            return partition.partitionName.indexOf(deviceName) === 0;
        });
    }

    StorageManager {
        id: storageManager

        Component.onCompleted: {
            storageManager.startMonitoring();
        }

        Component.onDestruction: {
            storageManager.stopMonitoring();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        StorageToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            storageManager: storageManager
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - detailsPanel.height - statusBar.height
            spacing: 0

            DeviceList {
                id: deviceList

                width: 220
                height: parent.height
                storageManager: storageManager

                onDeviceSelected: function (deviceName) {
                    root.selectedDevice = storageManager.devices.find(function (device) {
                        return device.deviceName === deviceName;
                    });
                }
            }

            PartitionTable {
                id: partitionTable

                width: parent.width - deviceList.width
                height: parent.height
                partitions: root.devicePartitions(root.selectedDevice ? root.selectedDevice.deviceName : "")
            }
        }

        StorageDetails {
            id: detailsPanel

            width: parent.width
            height: 120
            device: root.selectedDevice
        }

        StorageStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            storageManager: storageManager
            lastRefresh: root.formatTime(new Date())
        }
    }

    Connections {
        target: storageManager

        function onDevicesChanged() {
            statusBar.lastRefresh = root.formatTime(new Date());
        }

        function onPartitionsChanged() {
            statusBar.lastRefresh = root.formatTime(new Date());
        }
    }
}
