import QtQuick

/**
 * @brief Delegate for a storage device in the Storage Manager device list.
 */
Rectangle {
    id: root

    property var device: null
    property bool selected: false

    width: parent ? parent.width : 220
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
            text: root.device ? root.device.displayName : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            elide: Text.ElideRight
            width: parent.width
        }

        Text {
            text: root.device ? root.device.deviceType : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: parent.width
        }
    }
}
