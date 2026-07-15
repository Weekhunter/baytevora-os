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
    color: ThemeManager.surfaceSecondaryColor
    radius: DesignTokens.radiusMedium
    border.color: ThemeManager.borderColor
    border.width: 1

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        spacing: SpacingManager.space6

        Text {
            text: root.updateData ? root.updateData.title : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: root.updateData ? root.updateData.version : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Row {
            spacing: SpacingManager.space12

            Text {
                text: root.updateData ? root.updateData.type : ""
                color: ThemeManager.accentColor
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            Text {
                text: root.updateData ? root.updateData.size : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            Text {
                text: root.updateData ? root.updateData.releaseDate : ""
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }

        Text {
            text: root.updateData ? root.updateData.description : ""
            width: parent.width
            wrapMode: Text.WordWrap
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
