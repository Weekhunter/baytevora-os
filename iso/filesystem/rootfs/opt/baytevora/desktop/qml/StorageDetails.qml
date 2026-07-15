import QtQuick

/**
 * @brief Details panel for the selected storage device.
 */
Rectangle {
    id: root

    property var device: null

    height: 120
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
            text: root.device ? "Model: " + root.device.model : "Model: -"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.device ? "Serial: " + root.device.serialNumber : "Serial: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.device ? "Removable: " + (root.device.removable ? "Yes" : "No") : "Removable: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.device ? "Mounted: " + (root.device.mounted ? "Yes" : "No") : "Mounted: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.device ? "Capacity: " + root.device.capacityText : "Capacity: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
