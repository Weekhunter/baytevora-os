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
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    color: ThemeManager ? ThemeManager.primaryColor : "#2563EB"

    Text {
        anchors.centerIn: parent
        text: "Login"
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.body : 14
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
