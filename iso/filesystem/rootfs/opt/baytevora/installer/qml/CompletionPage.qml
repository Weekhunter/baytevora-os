import QtQuick
import BOI.Installer

Item {
    Column {
        anchors.centerIn: parent
        spacing: SpacingManager.space24
        width: Math.min(parent.width - SpacingManager.space64, 560)

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Installation Complete"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.heading
            font.weight: 600
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: "Baytevora OS has been installed successfully. Please restart your computer to start using it."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: SpacingManager.space12

            InstallerButton {
                text: "Restart Later"
                onClicked: Qt.quit()
            }

            InstallerButton {
                text: "Restart Now"
                primary: true
                onClicked: {
                    // Future: integrate with power manager to restart the system.
                    Qt.quit();
                }
            }
        }
    }
}
