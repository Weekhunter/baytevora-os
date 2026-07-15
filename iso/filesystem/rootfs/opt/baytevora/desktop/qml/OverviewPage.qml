import QtQuick

/**
 * @brief Overview page for the System Monitor.
 *
 * Displays CPU, memory, disk, and system cards in a responsive grid, plus a
 * manual refresh button. Auto-refresh is handled by the SystemMonitorManager.
 */
Rectangle {
    id: root

    property var monitorManager: null
    property var systemInfo: root.monitorManager ? root.monitorManager.info : null

    color: "transparent"

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space16

        Row {
            width: parent.width
            spacing: SpacingManager.space12

            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "System Monitor"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.heading
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: refreshLabel.width + (SpacingManager.space20)
                height: SpacingManager.space32
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1

                Text {
                    id: refreshLabel

                    anchors.centerIn: parent
                    text: "Refresh"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (root.monitorManager) {
                            root.monitorManager.refresh();
                        }
                    }
                }
            }
        }

        Grid {
            id: grid

            width: parent.width
            columns: root.width >= 720 ? 2 : 1
            columnSpacing: SpacingManager.space16
            rowSpacing: SpacingManager.space16

            CpuCard {
                width: (grid.width - (grid.columns - 1) * grid.columnSpacing) / grid.columns
                height: 200
                systemInfo: root.systemInfo
            }

            MemoryCard {
                width: (grid.width - (grid.columns - 1) * grid.columnSpacing) / grid.columns
                height: 200
                systemInfo: root.systemInfo
            }

            DiskCard {
                width: (grid.width - (grid.columns - 1) * grid.columnSpacing) / grid.columns
                height: 200
                systemInfo: root.systemInfo
            }

            SystemCard {
                width: (grid.width - (grid.columns - 1) * grid.columnSpacing) / grid.columns
                height: 200
                systemInfo: root.systemInfo
            }
        }
    }
}
