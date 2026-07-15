import QtQuick

/**
 * @brief CPU metrics card for the System Monitor.
 */
Rectangle {
    id: root

    property var systemInfo: null

    color: ThemeManager.surfaceColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space12

        Text {
            text: "CPU"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.systemInfo
                  ? "Usage: " + Math.round(root.systemInfo.cpuUsage) + "%"
                  : "Usage: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Rectangle {
            width: parent.width
            height: SpacingManager.space8
            color: ThemeManager.surfaceSecondaryColor
            radius: height / 2

            Rectangle {
                width: root.systemInfo ? parent.width * (root.systemInfo.cpuUsage / 100.0) : 0
                height: parent.height
                color: ThemeManager.primaryColor
                radius: parent.radius
            }
        }

        Text {
            text: root.systemInfo
                  ? "Threads: " + root.systemInfo.cpuThreads
                  : "Threads: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.systemInfo
                  ? "Frequency: " + (root.systemInfo.cpuFrequency > 0 ? (root.systemInfo.cpuFrequency / 1000.0).toFixed(2) + " GHz" : "-")
                  : "Frequency: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
