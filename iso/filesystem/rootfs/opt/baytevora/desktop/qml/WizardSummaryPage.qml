import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard summary page.
 *
 * SummaryPage lists all selected settings and lets the user jump back to any
 * section to edit it.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 20
        width: Math.min(parent.width * 0.8, 640)

        Text {
            text: "Summary"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Review your settings before starting the setup."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Rectangle {
            width: parent.width
            height: summaryList.height + 32
            radius: DesignTokens.radiusMedium
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                id: summaryList

                anchors.centerIn: parent
                spacing: 12
                width: parent.width - 32

                SummaryRow { label: "Region"; value: firstBootManager.region; page: 1 }
                SummaryRow { label: "Language"; value: firstBootManager.language; page: 2 }
                SummaryRow { label: "Keyboard"; value: firstBootManager.keyboardLayout; page: 3 }
                SummaryRow { label: "Time Zone"; value: firstBootManager.timeZone; page: 4 }
                SummaryRow {
                    label: "Date & Time"
                    value: firstBootManager.autoDateTime ? "Automatic" : "Manual"
                    page: 5
                }
                SummaryRow { label: "Privacy"; value: "Local by default"; page: 6 }
                SummaryRow { label: "User"; value: firstBootManager.userName + " (" + firstBootManager.userLogin + ")"; page: 7 }
                SummaryRow { label: "Computer Name"; value: firstBootManager.computerName; page: 8 }
            }
        }
    }
}
