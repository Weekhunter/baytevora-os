import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief First-boot wizard computer name page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Computer Name"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "This name identifies your Baytevora device on the network."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        TextField {
            id: nameField

            width: parent.width
            height: 44
            placeholderText: "BAYTEVORA-PC"
            text: firstBootManager.computerName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }
            onTextChanged: firstBootManager.computerName = text
        }

        Text {
            text: "Use 1-15 characters. Letters, numbers, and hyphens only."
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
