import QtQuick

/**
 * @brief Status bar for the Network Manager.
 */
Rectangle {
    id: root

    property var networkManager: null
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
            text: root.networkManager
                  ? "Total interfaces: " + root.networkManager.interfaces.length
                  : "Total interfaces: 0"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.networkManager
                  ? "Connected: " + root.networkManager.interfaces.filter(function (iface) { return iface.connected; }).length
                  : "Connected: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.lastRefresh.length > 0
                  ? "Last refresh: " + root.lastRefresh
                  : "Last refresh: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
