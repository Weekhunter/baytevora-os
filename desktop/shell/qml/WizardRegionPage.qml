import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief First-boot wizard region selection page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 24
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Region"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "Choose your country or region."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        TextField {
            id: searchField

            width: parent.width
            height: 44
            placeholderText: "Search countries..."
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
            id: countryList

            width: parent.width
            height: 220
            clip: true
            model: {
                const all = [
                    "Australia", "Austria", "Belgium", "Brazil", "Canada", "China",
                    "Denmark", "Finland", "France", "Germany", "India", "Ireland",
                    "Italy", "Japan", "Mexico", "Netherlands", "New Zealand", "Norway",
                    "Spain", "Sweden", "Switzerland", "United Kingdom", "United States"
                ];
                const term = searchField.text.toLowerCase();
                return term.length === 0 ? all : all.filter(c => c.toLowerCase().includes(term));
            }

            delegate: Rectangle {
                width: countryList.width
                height: 44
                color: firstBootManager.region === modelData
                       ? ThemeManager.highlightColor
                       : (countryMouse.containsMouse ? ThemeManager.surfaceSecondaryColor : "transparent")
                radius: DesignTokens.radiusSmall

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: SpacingManager.space12
                    text: modelData
                    color: firstBootManager.region === modelData
                           ? ThemeManager.backgroundColor
                           : ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                MouseArea {
                    id: countryMouse

                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: firstBootManager.region = modelData
                }
            }
        }

        Text {
            text: "Auto-detect region: not yet implemented."
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
