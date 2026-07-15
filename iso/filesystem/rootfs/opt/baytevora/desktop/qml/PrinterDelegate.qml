import QtQuick

/**
 * @brief Delegate for a printer in the Print Manager printer list.
 */
Rectangle {
    id: root

    property var printer: null
    property bool selected: false

    width: parent ? parent.width : 200
    height: AdaptiveLayoutManager.listItemHeight
    color: root.selected
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.backgroundColor)
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space4

        Text {
            text: root.printer ? root.printer.displayName : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            elide: Text.ElideRight
            width: parent.width
        }

        Text {
            text: root.printer ? (root.printer.defaultPrinter ? "Default" : root.printer.status) : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width
        }
    }
}
