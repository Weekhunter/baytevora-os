import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief First-boot wizard time zone selection page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 560)

        Text {
            text: "Time Zone"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Select your time zone."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        TextField {
            id: tzSearch

            width: parent.width
            height: 44
            placeholderText: "Search time zones..."
            text: ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }
        }

        ListView {
            id: tzList

            width: parent.width
            height: 260
            clip: true
            model: {
                const all = [
                    "Africa/Cairo", "Africa/Johannesburg", "Africa/Lagos", "America/Argentina/Buenos_Aires",
                    "America/Chicago", "America/Denver", "America/Los_Angeles", "America/Mexico_City",
                    "America/New_York", "America/Sao_Paulo", "America/Toronto", "Asia/Bangkok",
                    "Asia/Dubai", "Asia/Hong_Kong", "Asia/Kolkata", "Asia/Shanghai", "Asia/Singapore",
                    "Asia/Tokyo", "Australia/Melbourne", "Australia/Sydney", "Europe/Berlin",
                    "Europe/London", "Europe/Madrid", "Europe/Moscow", "Europe/Paris", "Europe/Rome",
                    "Pacific/Auckland", "Pacific/Honolulu"
                ];
                const term = tzSearch.text.toLowerCase();
                return term.length === 0 ? all : all.filter(t => t.toLowerCase().includes(term));
            }

            delegate: Rectangle {
                width: tzList.width
                height: 40
                color: firstBootManager.timeZone === modelData
                       ? ThemeManager.highlightColor
                       : (tzMouse.containsMouse ? ThemeManager.surfaceSecondaryColor : "transparent")
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: SpacingManager.space12
                    text: modelData
                    color: firstBootManager.timeZone === modelData
                           ? ThemeManager.backgroundColor
                           : ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                MouseArea {
                    id: tzMouse

                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: firstBootManager.timeZone = modelData
                }
            }
        }

        Text {
            text: "Automatic time zone detection: not yet implemented."
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
