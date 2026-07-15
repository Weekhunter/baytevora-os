import QtQuick
import BOS.Shell

/**
 * @brief Minimal branded About dialog for any Baytevora application.
 *
 * AboutDialog shows the official application symbol, the application name,
 * the Baytevora OS version label, and the "Powered by Baytevora" line.
 * It is rendered as a centered card over a dim overlay and can be closed by
 * clicking anywhere outside the card.
 */
Rectangle {
    id: root

    property string applicationName: ""
    property bool open: false

    anchors.fill: parent
    color: "#CC000000"
    visible: open

    MouseArea {
        anchors.fill: parent
        onClicked: root.open = false
    }

    Rectangle {
        anchors.centerIn: parent
        width: 360
        height: 420
        radius: DesignTokens.radiusXLarge
        color: ThemeManager.surfaceColor
        border.color: ThemeManager.borderColor
        border.width: 1

        MouseArea {
            anchors.fill: parent
            onClicked: mouse.accepted = true
        }

        Column {
            anchors.centerIn: parent
            spacing: 18

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 96
                height: 115
                source: BrandingManager.applicationSymbolUrl(root.applicationName)
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 192
                sourceSize.height: 230
                visible: source.toString().length > 0
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: root.applicationName.length > 0 ? root.applicationName : BrandingManager.osName
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.title
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: BrandingManager.fullVersionLabel
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: BrandingManager.poweredBy
                color: ThemeManager.textDisabled
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "\u00A9 2026 " + BrandingManager.companyName
                color: ThemeManager.textDisabled
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80
                height: 32
                radius: DesignTokens.radiusSmall
                color: ThemeManager.surfaceSecondaryColor

                Text {
                    anchors.centerIn: parent
                    text: "Close"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.open = false
                }
            }
        }
    }
}
