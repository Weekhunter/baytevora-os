import QtQuick
import BOS.Shell

/**
 * @brief First-boot wizard finish page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 28
        width: Math.min(parent.width * 0.8, 480)

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 96
            height: 115
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 192
            sourceSize.height: 230
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "You're all set!"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Baytevora OS is ready to use. Click below to start your desktop session."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
        }

        WizardButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Start Using BOS"
            primary: true
            width: 180
            onClicked: firstBootManager.completeSetup()
        }
    }
}
