import QtQuick
import BOI.Installer

Item {
    Column {
        anchors.centerIn: parent
        spacing: SpacingManager.space24
        width: Math.min(parent.width - SpacingManager.space64, 560)

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            source: brandingManager.applicationLogoUrl("BOS")
            sourceSize.width: 96
            sourceSize.height: 96
            fillMode: Image.PreserveAspectFit
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Welcome to Baytevora OS"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.heading
            font.weight: 600
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Version 0.1 Alpha"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: "This installer will guide you through installing Baytevora OS on your computer. Make sure your device is plugged in and you have backed up any important data."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
