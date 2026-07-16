import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard keyboard layout page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 560)

        Text {
            text: "Keyboard Layout"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Select the keyboard layout you will use."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Row {
            spacing: 24
            width: parent.width

            ListView {
                id: layoutList

                width: 220
                height: 240
                clip: true
                model: ["US", "UK", "German", "French", "Spanish", "Italian", "Nordic", "Dvorak"]

                delegate: Rectangle {
                    width: layoutList.width
                    height: 44
                    color: firstBootManager.keyboardLayout === modelData
                           ? ThemeManager.highlightColor
                           : (layoutMouse.containsMouse ? ThemeManager.surfaceSecondaryColor : "transparent")
                    radius: DesignTokens.radiusSmall

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: SpacingManager.space12
                        text: modelData
                        color: firstBootManager.keyboardLayout === modelData
                               ? ThemeManager.backgroundColor
                               : ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    MouseArea {
                        id: layoutMouse

                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: firstBootManager.keyboardLayout = modelData
                    }
                }
            }

            Rectangle {
                width: parent.width - 244
                height: 240
                radius: DesignTokens.radiusMedium
                color: ThemeManager.surfaceSecondaryColor
                border.color: ThemeManager.borderColor
                border.width: 1

                Column {
                    anchors.centerIn: parent
                    spacing: 12
                    width: parent.width - 32

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Preview"
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.title
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.DemiBold
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: firstBootManager.keyboardLayout
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Layout preview and testing will be available in a future update."
                        color: ThemeManager.textDisabled
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                        wrapMode: Text.Wrap
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}
