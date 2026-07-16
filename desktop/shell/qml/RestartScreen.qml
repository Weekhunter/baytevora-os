import QtQuick
import BOS.Shell

/**
 * @brief Baytevora OS restart screen.
 *
 * RestartScreen is shown while the system is rebooting. Like ShutdownScreen, it
 * is a full-screen branded overlay with no animations.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    Column {
        anchors.centerIn: parent
        spacing: 24

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 100
            height: 120
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 200
            sourceSize.height: 240
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Restarting"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.poweredBy
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
