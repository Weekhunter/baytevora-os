import QtQuick

/**
 * @brief Disk usage card for the System Monitor.
 */
Rectangle {
    id: root

    property var systemInfo: null

    color: ThemeManager.surfaceColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    function formatBytes(bytes) {
        if (bytes <= 0) {
            return "0 B";
        }
        const units = ["B", "KB", "MB", "GB", "TB"];
        let index = 0;
        let value = bytes;
        while (value >= 1024 && index < units.length - 1) {
            value /= 1024;
            index++;
        }
        return value.toFixed(2) + " " + units[index];
    }

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space12

        Text {
            text: "Disk"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.systemInfo
                  ? "Used: " + root.formatBytes(root.systemInfo.diskUsed)
                  : "Used: -"
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
                width: root.systemInfo && root.systemInfo.diskTotal > 0
                       ? parent.width * (root.systemInfo.diskUsed / root.systemInfo.diskTotal)
                       : 0
                height: parent.height
                color: ThemeManager.primaryColor
                radius: parent.radius
            }
        }

        Text {
            text: root.systemInfo
                  ? "Free: " + root.formatBytes(root.systemInfo.diskFree) + " / " + root.formatBytes(root.systemInfo.diskTotal)
                  : "Free: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
