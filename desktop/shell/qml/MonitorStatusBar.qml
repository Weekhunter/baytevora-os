import QtQuick

/**
 * @brief Status bar for the System Monitor.
 */
Rectangle {
    id: root

    property var systemInfo: null
    property bool monitoring: true

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12 ? SpacingManager.space12 : 12
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.monitoring ? "Monitoring active" : "Monitoring paused"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.systemInfo
                  ? "CPU: " + Math.round(root.systemInfo.cpuUsage) + "%"
                  : "CPU: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
