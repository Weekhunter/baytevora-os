import QtQuick

/**
 * @brief List of network interfaces for the Network Manager.
 */
Rectangle {
    id: root

    property var networkManager: null
    property string selectedInterface: ""

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal interfaceSelected(string interfaceName)

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

            Row {
                anchors.fill: parent
                anchors.leftMargin: SpacingManager.space12
                anchors.rightMargin: SpacingManager.space12
                spacing: SpacingManager.space8

                Text {
                    width: parent.width * 0.22
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Name"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Type"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Status"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Enabled"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.24
                    anchors.verticalCenter: parent.verticalCenter
                    text: "IP Address"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - header.height
            model: root.networkManager ? root.networkManager.interfaces : []
            clip: true

            delegate: NetworkInterfaceDelegate {
                width: listView.width
                interfaceData: modelData
                selected: modelData && modelData.interfaceName === root.selectedInterface

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (modelData) {
                            root.selectedInterface = modelData.interfaceName;
                            root.interfaceSelected(modelData.interfaceName);
                        }
                    }
                }
            }
        }
    }
}
