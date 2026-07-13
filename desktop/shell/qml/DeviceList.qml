import QtQuick

/**
 * @brief List of storage devices for the Storage Manager.
 */
Rectangle {
    id: root

    property var storageManager: null
    property string selectedDeviceName: ""

    width: 220
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal deviceSelected(string deviceName)

    Column {
        anchors.fill: parent
        spacing: 0

        // Header row.
        Rectangle {
            width: parent.width
            height: AdaptiveLayoutManager.listHeaderHeight
            color: ThemeManager.surfaceColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Text {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                text: "Devices"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
                verticalAlignment: Text.AlignVCenter
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - header.height
            model: root.storageManager ? root.storageManager.devices : []
            clip: true

            delegate: DeviceDelegate {
                width: listView.width
                device: modelData
                selected: modelData && modelData.deviceName === root.selectedDeviceName

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (modelData) {
                            root.selectedDeviceName = modelData.deviceName;
                            root.deviceSelected(modelData.deviceName);
                        }
                    }
                }
            }
        }
    }
}
