import QtQuick

/**
 * @brief Read-only label/value row used by the Store details and settings pages.
 */
Row {
    id: root

    property string label: ""
    property string value: ""

    spacing: SpacingManager.space16

    Text {
        width: 140
        text: root.label
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Text {
        text: root.value
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
