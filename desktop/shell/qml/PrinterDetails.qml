import QtQuick

/**
 * @brief Details panel for the selected printer.
 */
Rectangle {
    id: root

    property var printer: null

    height: 180
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
            text: root.printer ? "Name: " + root.printer.displayName : "Name: -"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.printer ? "Model: " + root.printer.model : "Model: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.printer ? "Manufacturer: " + root.printer.manufacturer : "Manufacturer: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width / 2
        }

        Text {
            text: root.printer ? "Status: " + root.printer.status : "Status: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.printer ? "Online: " + (root.printer.online ? "Yes" : "No") : "Online: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.printer ? "Default: " + (root.printer.defaultPrinter ? "Yes" : "No") : "Default: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.printer ? "Color: " + (root.printer.colorSupported ? "Yes" : "No") : "Color: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.printer ? "Duplex: " + (root.printer.duplexSupported ? "Yes" : "No") : "Duplex: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
