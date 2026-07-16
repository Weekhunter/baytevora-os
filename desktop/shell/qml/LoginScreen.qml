import QtQuick
import QtQuick.Window
import BOS.Shell

/**
 * @brief Baytevora Login Manager (BLM) screen.
 *
 * LoginScreen is shown before the desktop session starts. It displays a shared
 * wallpaper background, a logo placeholder, a clock, the list of available users,
 * and a login button. Successful login transitions to the desktop session.
 */
Window {
    id: root

    visible: true
    flags: Qt.FramelessWindowHint
    visibility: Window.FullScreen
    color: ThemeManager.surfaceSecondaryColor

    DesktopSurface {
        anchors.fill: parent
    }

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager.space32
        width: Math.min(parent.width * 0.8, 360)

        // Official Baytevora OS symbol
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

        Clock {
            anchors.horizontalCenter: parent.horizontalCenter
            height: 40
        }

        UserList {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
        }

        LoginButton {
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
