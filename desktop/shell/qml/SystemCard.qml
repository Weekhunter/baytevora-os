import QtQuick

/**
 * @brief System identification and uptime card for the System Monitor.
 */
Rectangle {
    id: root

    property var systemInfo: null

    color: ThemeManager.surfaceColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    function formatUptime(seconds) {
        if (seconds <= 0) {
            return "0s";
        }
        const days = Math.floor(seconds / 86400);
        const hours = Math.floor((seconds % 86400) / 3600);
        const minutes = Math.floor((seconds % 3600) / 60);
        const secs = seconds % 60;
        let result = "";
        if (days > 0) {
            result += days + "d ";
        }
        if (hours > 0 || result.length > 0) {
            result += hours + "h ";
        }
        if (minutes > 0 || result.length > 0) {
            result += minutes + "m ";
        }
        result += secs + "s";
        return result;
    }

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space12

        Text {
            text: "System"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.systemInfo
                  ? "Uptime: " + root.formatUptime(root.systemInfo.uptime)
                  : "Uptime: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.systemInfo
                  ? "OS: " + root.systemInfo.operatingSystem
                  : "OS: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        Text {
            text: root.systemInfo
                  ? "Kernel: " + root.systemInfo.kernelVersion
                  : "Kernel: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        Text {
            text: root.systemInfo
                  ? "Architecture: " + root.systemInfo.architecture
                  : "Architecture: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
