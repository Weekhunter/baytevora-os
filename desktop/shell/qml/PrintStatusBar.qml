import QtQuick

/**
 * @brief Status bar for the Print Manager.
 */
Rectangle {
    id: root

    property var printManager: null
    property string lastRefresh: ""

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.printManager
                  ? "Printers: " + root.printManager.printers.length
                  : "Printers: 0"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.printManager
                  ? "Jobs: " + root.printManager.jobs.length
                  : "Jobs: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.printManager
                  ? "Default: " + (root.printManager.printers.find(function (printer) { return printer.defaultPrinter; }) || { displayName: "-" }).displayName
                  : "Default: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
