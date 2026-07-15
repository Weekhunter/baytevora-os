import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief First-boot wizard date & time page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Date & Time"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        WizardToggle {
            label: "Set time automatically"
            checked: firstBootManager.autoDateTime
            onToggled: firstBootManager.autoDateTime = checked
        }

        Rectangle {
            width: parent.width
            height: manualDate.visible ? 180 : 0
            radius: DesignTokens.radiusMedium
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1
            visible: !firstBootManager.autoDateTime
            clip: true

            Column {
                anchors.centerIn: parent
                spacing: 16
                width: parent.width - 32

                Text {
                    text: "Manual date and time"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Row {
                    spacing: 16
                    width: parent.width

                    TextField {
                        id: manualDate

                        width: parent.width / 2 - 8
                        height: 44
                        placeholderText: "YYYY-MM-DD"
                        text: firstBootManager.manualDate.toLocaleString(Qt.locale(), "yyyy-MM-dd")
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        background: Rectangle {
                            color: ThemeManager.backgroundColor
                            radius: DesignTokens.radiusSmall
                            border.color: ThemeManager.borderColor
                            border.width: 1
                        }
                        onEditingFinished: {
                            const d = Date.fromLocaleString(Qt.locale(), text, "yyyy-MM-dd");
                            if (!isNaN(d.getTime())) {
                                firstBootManager.manualDate = d;
                            }
                        }
                    }

                    TextField {
                        id: manualTimeField

                        width: parent.width / 2 - 8
                        height: 44
                        placeholderText: firstBootManager.use24HourFormat ? "HH:MM" : "HH:MM AM/PM"
                        text: firstBootManager.manualTime.toString(firstBootManager.use24HourFormat ? "hh:mm" : "hh:mm AP")
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        background: Rectangle {
                            color: ThemeManager.backgroundColor
                            radius: DesignTokens.radiusSmall
                            border.color: ThemeManager.borderColor
                            border.width: 1
                        }
                    }
                }
            }
        }

        WizardToggle {
            label: "Use 24-hour format"
            checked: firstBootManager.use24HourFormat
            onToggled: firstBootManager.use24HourFormat = checked
        }
    }
}
