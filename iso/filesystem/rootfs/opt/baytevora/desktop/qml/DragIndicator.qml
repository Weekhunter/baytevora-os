import QtQuick

/**
 * @brief Small reusable drag preview following a drag operation.
 *
 * DragIndicator consumes design tokens for colors, typography, and sizing. It
 * displays a placeholder square and the dragged item name.
 */
Rectangle {
    id: root

    property string draggedName: ""
    property string draggedIcon: ""

    width: 100
    height: 80
    color: ThemeManager.surfaceSecondaryColor
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusMedium

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager.space4

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: IconManager.large
            height: width
            color: ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusSmall

            Text {
                anchors.centerIn: parent
                text: root.draggedIcon.length > 0 ? root.draggedIcon.substring(0, 2) : "Dr"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.draggedName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
            width: root.width - 16
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
