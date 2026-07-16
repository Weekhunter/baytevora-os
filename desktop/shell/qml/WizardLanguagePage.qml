import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard language selection page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Language"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Select the language to use. Additional languages will be available in a future update."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        ListView {
            id: languageList

            width: parent.width
            height: 240
            clip: true
            model: ["English (US)"]

            delegate: Rectangle {
                width: languageList.width
                height: 48
                color: firstBootManager.language === modelData
                       ? ThemeManager.highlightColor
                       : (languageMouse.containsMouse ? ThemeManager.surfaceSecondaryColor : "transparent")
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: SpacingManager.space12
                    text: modelData
                    color: firstBootManager.language === modelData
                           ? ThemeManager.backgroundColor
                           : ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                MouseArea {
                    id: languageMouse

                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: firstBootManager.language = modelData
                }
            }
        }
    }
}
