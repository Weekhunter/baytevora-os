import QtQuick

/**
 * @brief Card displaying a single available update.
 *
 * UpdateCard consumes the BDL token managers and shows the update title,
 * version, type, size, release date, and description.
 */
Rectangle {
    id: root

    property var updateData: null

    width: parent ? parent.width : 200
    height: childrenRect.height + 32
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager ? SpacingManager.space16 : 16
        spacing: SpacingManager ? SpacingManager.space6 : 6

        Text {
            text: root.updateData ? root.updateData.title : ""
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.title : 18
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.DemiBold
        }

        Text {
            text: root.updateData ? root.updateData.version : ""
            color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Row {
            spacing: SpacingManager ? SpacingManager.space12 : 12

            Text {
                text: root.updateData ? root.updateData.type : ""
                color: ThemeManager ? ThemeManager.accentColor : "#38bdf8"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.DemiBold
            }

            Text {
                text: root.updateData ? root.updateData.size : ""
                color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }

            Text {
                text: root.updateData ? root.updateData.releaseDate : ""
                color: ThemeManager ? ThemeManager.textSecondary : "#CBD5E1"
                font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            }
        }

        Text {
            text: root.updateData ? root.updateData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.body : 14
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }
    }
}
