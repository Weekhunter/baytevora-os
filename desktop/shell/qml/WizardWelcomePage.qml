import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard welcome page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 28
        width: Math.min(parent.width * 0.8, 480)

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 120
            height: 144
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 240
            sourceSize.height: 288
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Welcome to Baytevora OS"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.osVersion
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Let's get your system set up. This will only take a few moments."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
