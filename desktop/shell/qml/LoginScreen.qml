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
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#0f172a"

    DesktopSurface {
        anchors.fill: parent
    }

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager ? SpacingManager.space32 : 32
        width: Math.min(parent.width * 0.8, 360)

        // Logo placeholder
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 80
            height: 80
            radius: DesignTokens ? DesignTokens.radiusLarge : 16
            color: ThemeManager ? ThemeManager.primaryColor : "#2563EB"

            Text {
                anchors.centerIn: parent
                text: "B"
                color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                font.pixelSize: TypographyManager ? TypographyManager.displaySize : 48
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.Bold
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Baytevora OS"
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.title : 18
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.DemiBold
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
