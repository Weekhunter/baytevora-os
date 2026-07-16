import QtQuick
import BOS.Shell

/**
 * @brief Standalone About Baytevora OS screen.
 *
 * AboutBosScreen displays the official system symbol, full version label,
 * company name, and "Powered by Baytevora" line. It can be used as a system
 * dialog or settings page.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    Column {
        anchors.centerIn: parent
        spacing: 20

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 128
            height: 154
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 256
            sourceSize.height: 308
        }

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 62
            source: BrandingManager.applicationLogoUrl("Baytevora OS", "dark")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 400
            sourceSize.height: 124
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.osName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.displaySize
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.fullVersionLabel
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.poweredBy
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "\u00A9 2026 " + BrandingManager.companyName
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
