import QtQuick
import BOS.Shell

/**
 * @brief Baytevora OS splash screen.
 *
 * SplashScreen is shown for transient system events (e.g., returning from lock
 * or launching the installer). It centers a compact branded card without
 * animations.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    Rectangle {
        anchors.centerIn: parent
        width: 320
        height: 360
        radius: DesignTokens.radiusXLarge
        color: ThemeManager.surfaceSecondaryColor
        border.color: ThemeManager.borderColor
        border.width: 1

        Column {
            anchors.centerIn: parent
            spacing: 20

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80
                height: 96
                source: BrandingManager.applicationSymbolUrl("Baytevora OS")
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 160
                sourceSize.height: 192
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: BrandingManager.osName
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.title
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: BrandingManager.osVersion
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: root.message !== undefined ? root.message : BrandingManager.poweredBy
                color: ThemeManager.textDisabled
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.Wrap
                width: parent.width - 48
            }
        }
    }
}
