import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard privacy preferences page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 20
        width: Math.min(parent.width * 0.8, 560)

        Text {
            text: "Privacy"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Baytevora keeps your data local by default. You can choose to share limited diagnostic information below."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        Rectangle {
            width: parent.width
            height: privacyColumn.height + 32
            radius: DesignTokens.radiusMedium
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                id: privacyColumn

                anchors.centerIn: parent
                spacing: 16
                width: parent.width - 32

                WizardToggle {
                    label: "Help improve Baytevora by sharing usage analytics"
                    checked: firstBootManager.usageAnalytics
                    onToggled: firstBootManager.usageAnalytics = checked
                }

                WizardToggle {
                    label: "Send automatic crash reports"
                    checked: firstBootManager.crashReports
                    onToggled: firstBootManager.crashReports = checked
                }

                WizardToggle {
                    label: "Allow personalization based on usage"
                    checked: firstBootManager.personalization
                    onToggled: firstBootManager.personalization = checked
                }

                WizardToggle {
                    label: "Enable location services"
                    checked: firstBootManager.locationServices
                    onToggled: firstBootManager.locationServices = checked
                }
            }
        }

        Text {
            text: "Cloud and enterprise privacy controls will be available in a future update."
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
