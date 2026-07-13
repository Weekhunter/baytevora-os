import QtQuick
import BOS.Shell

/**
 * @brief Flat BDL-styled login button.
 *
 * Clicking the button requests login through the LoginManager. The button is
 * disabled while the login manager is in the LoggingIn state.
 */
Rectangle {
    id: root

    width: 160
    height: 40
    radius: DesignTokens.radiusMedium
    color: ThemeManager.primaryColor

    Text {
        anchors.centerIn: parent
        text: "Login"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    MouseArea {
        anchors.fill: parent
        enabled: loginManager && loginManager.state !== LoginState.LoggingIn
        onClicked: {
            if (loginManager) {
                loginManager.login();
            }
        }
    }
}
