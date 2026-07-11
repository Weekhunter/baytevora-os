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
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1
    radius: DesignTokens ? DesignTokens.radiusMedium : 8

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager ? SpacingManager.space4 : 4

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: IconManager ? IconManager.large : 32
            height: width
            color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
            radius: DesignTokens ? DesignTokens.radiusSmall : 6

            Text {
                anchors.centerIn: parent
                text: root.draggedIcon.length > 0 ? root.draggedIcon.substring(0, 2) : "Dr"
                color: ThemeManager ? ThemeManager.textPrimary : "#e2e8f0"
                font.pixelSize: TypographyManager ? TypographyManager.body : 14
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.draggedName
            color: ThemeManager ? ThemeManager.textPrimary : "#e2e8f0"
            font.pixelSize: TypographyManager ? TypographyManager.caption : 12
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            elide: Text.ElideRight
            width: root.width - 16
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
