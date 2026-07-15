import QtQuick

/**
 * @brief Reusable label/value row for the PDF Studio document panel tabs.
 */
Row {
    id: root

    property string label: ""
    property var value: ""

    spacing: SpacingManager.space8
    width: parent ? parent.width : 200

    Text {
        width: parent.width * 0.35
        text: root.label
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Text {
        width: parent.width * 0.6
        text: root.value
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WrapAnywhere
        maximumLineCount: 3
        elide: Text.ElideRight
    }
}
