import QtQuick

/**
 * @brief Delegate for a network interface in the Network Manager list.
 */
Rectangle {
    id: root

    property var interfaceData: null
    property bool selected: false

    width: parent ? parent.width : 600
    height: AdaptiveLayoutManager.listItemHeight
    color: root.selected
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.backgroundColor)
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space8

        Text {
            width: parent.width * 0.22
            anchors.verticalCenter: parent.verticalCenter
            text: root.interfaceData ? root.interfaceData.displayName : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.interfaceData ? root.interfaceData.interfaceType : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.interfaceData ? (root.interfaceData.connected ? "Connected" : "Disconnected") : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.interfaceData ? (root.interfaceData.enabled ? "Enabled" : "Disabled") : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.24
            anchors.verticalCenter: parent.verticalCenter
            text: root.interfaceData ? root.interfaceData.ipAddress : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }
    }
}
