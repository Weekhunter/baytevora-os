import QtQuick

/**
 * @brief Transaction list and progress viewer for the Package Manager Phase 2.
 */
Column {
    id: root

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Text {
        text: "Transactions"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Repeater {
        model: packageManager ? packageManager.transactions : []

        delegate: Rectangle {
            width: parent.width
            height: 80
            radius: DesignTokens.radiusSmall
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                spacing: SpacingManager.space8

                Row {
                    spacing: SpacingManager.space12

                    Text {
                        text: modelData.operationName
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.DemiBold
                    }

                    Text {
                        text: modelData.stateName
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }

                Text {
                    text: modelData.packageList.join(", ")
                    color: ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }

                Rectangle {
                    width: parent.width
                    height: 8
                    radius: DesignTokens.radiusSmall
                    color: ThemeManager.surfaceColor

                    Rectangle {
                        width: parent.width * Math.min(1, Math.max(0, modelData.progress / 100))
                        height: parent.height
                        radius: parent.radius
                        color: modelData.state === 3
                               ? (ThemeManager.errorColor)
                               : (ThemeManager.accentColor)
                    }
                }

                Text {
                    visible: modelData.errorMessage.length > 0
                    text: modelData.errorMessage
                    color: ThemeManager.errorColor
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }
        }
    }

    Text {
        visible: packageManager && packageManager.transactions.length === 0
        text: "No transactions yet."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
