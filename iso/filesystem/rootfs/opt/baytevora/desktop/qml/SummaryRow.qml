import QtQuick
import BOS.Shell

/**
 * @brief Editable summary row used by the first-boot summary page.
 */
Row {
    id: root

    property string label: ""
    property string value: ""
    property int page: 0

    spacing: SpacingManager.space16
    width: parent ? parent.width : 400

    Text {
        width: 140
        text: root.label
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Text {
        width: parent.width - 230
        text: root.value
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        elide: Text.ElideRight
    }

    Rectangle {
        width: 50
        height: 28
        radius: DesignTokens.radiusSmall
        color: editMouse.containsMouse ? ThemeManager.surfaceSecondaryColor : "transparent"

        Text {
            anchors.centerIn: parent
            text: "Edit"
            color: ThemeManager.highlightColor
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        MouseArea {
            id: editMouse

            anchors.fill: parent
            hoverEnabled: true
            onClicked: firstBootManager.goToPage(root.page)
        }
    }
}
