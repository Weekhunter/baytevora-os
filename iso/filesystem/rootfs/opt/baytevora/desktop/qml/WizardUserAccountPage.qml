import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief First-boot wizard user account creation page.
 */
Item {
    id: root

    Column {
        anchors.centerIn: parent
        spacing: 20
        width: Math.min(parent.width * 0.8, 480)

        Text {
            text: "Create Your Account"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.headline
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Text {
            text: "This account will be the administrator of this computer."
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            wrapMode: Text.Wrap
            width: parent.width
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 80
            height: 80
            radius: 40
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
            border.width: 1

            Text {
                anchors.centerIn: parent
                text: "?"
                color: ThemeManager.textDisabled
                font.pixelSize: 32
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // Avatar upload is reserved for a future sprint.
                    console.log("Avatar upload not yet implemented.");
                }
            }
        }

        TextField {
            id: fullNameField

            width: parent.width
            height: 44
            placeholderText: "Full name"
            text: firstBootManager.userName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }
            onTextChanged: firstBootManager.userName = text
        }

        TextField {
            id: usernameField

            width: parent.width
            height: 44
            placeholderText: "Username"
            text: firstBootManager.userLogin
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }
            onTextChanged: firstBootManager.userLogin = text
        }

        TextField {
            id: passwordField

            width: parent.width
            height: 44
            placeholderText: "Password"
            text: firstBootManager.userPassword
            echoMode: TextInput.Password
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }
            onTextChanged: firstBootManager.userPassword = text
        }

        TextField {
            id: confirmPasswordField

            width: parent.width
            height: 44
            placeholderText: "Confirm password"
            text: firstBootManager.userConfirmPassword
            echoMode: TextInput.Password
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            onTextChanged: firstBootManager.userConfirmPassword = text
            background: Rectangle {
                color: ThemeManager.surfaceSecondaryColor
                radius: DesignTokens.radiusSmall
                border.color: passwordField.text !== text && text.length > 0
                       ? ThemeManager.errorColor
                       : ThemeManager.borderColor
                border.width: 1
            }
        }

        Row {
            spacing: 12
            width: parent.width

            Text {
                text: "Password strength:"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
            }

            Text {
                text: firstBootManager.passwordStrength(passwordField.text)
                color: {
                    const s = firstBootManager.passwordStrength(passwordField.text);
                    if (s === "Strong") return ThemeManager.successColor;
                    if (s === "Good") return ThemeManager.warningColor;
                    return ThemeManager.errorColor;
                }
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
            }
        }

        WizardToggle {
            label: "Make this user an administrator"
            checked: firstBootManager.isAdministrator
            onToggled: firstBootManager.isAdministrator = checked
        }
    }
}
