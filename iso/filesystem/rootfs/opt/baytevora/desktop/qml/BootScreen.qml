import QtQuick
import BOS.Shell

/**
 * @brief Baytevora OS boot screen.
 *
 * BootScreen is displayed while the system is starting. It shows the official
 * Baytevora OS symbol, system name, version, and a static progress indicator.
 * No animations are used; progress updates are driven from C++.
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
            width: 120
            height: 144
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 240
            sourceSize.height: 288
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: BrandingManager.osName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
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
            text: BrandingManager.companyName
            color: ThemeManager.textDisabled
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        // Static progress track. The filled portion is controlled by the
        // bootProgress property (0.0 - 1.0) so C++ can drive startup progress.
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 240
            height: 4
            radius: 2
            color: ThemeManager.surfaceSecondaryColor

            Rectangle {
                width: parent.width * Math.max(0.0, Math.min(1.0, root.bootProgress !== undefined ? root.bootProgress : 0.4))
                height: parent.height
                radius: parent.radius
                color: ThemeManager.primaryColor
            }
        }
    }
}
