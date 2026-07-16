import QtQuick
import BOS.Shell

/**
 * @brief Baytevora OS installer screen.
 *
 * InstallerScreen is a placeholder for the system installer flow. It presents the
 * official Baytevora OS branding and accepts a start signal from C++ while
 * preserving the existing architecture.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property bool installRequested: false

    Column {
        anchors.centerIn: parent
        spacing: 24

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
            text: BrandingManager.osName + " Installer"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Version " + BrandingManager.osVersion
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: installRequested
                  ? "Installing..."
                  : "Select an option to begin installation."
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            width: 320
        }
    }
}
