import QtQuick

/**
 * @brief Details panel for the selected network interface.
 */
Rectangle {
    id: root

    property var interfaceData: null

    height: 160
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Grid {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        columns: 2
        columnSpacing: SpacingManager.space32
        rowSpacing: SpacingManager.space8

        Text {
            text: root.interfaceData ? "MAC: " + root.interfaceData.macAddress : "MAC: -"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.interfaceData ? "Subnet Mask: " + root.interfaceData.subnetMask : "Subnet Mask: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.interfaceData ? "Gateway: " + root.interfaceData.gateway : "Gateway: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.interfaceData ? "DNS Servers: " + root.interfaceData.dnsServersText : "DNS Servers: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.interfaceData ? "Speed: " + root.interfaceData.speed : "Speed: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
