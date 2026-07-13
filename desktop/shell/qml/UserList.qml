import QtQuick

/**
 * @brief List of available users on the login screen.
 *
 * UserList displays users vertically and supports selecting a user. The current
 * sprint provides a single default user.
 */
Column {
    id: root

    spacing: SpacingManager.space8
    width: 200

    Repeater {
        model: loginManager ? loginManager.users : []

        delegate: Rectangle {
            id: userItem

            property bool isSelected: loginManager && loginManager.selectedUser
                                      && loginManager.selectedUser.username === modelData.username

            width: root.width
            height: 56
            radius: DesignTokens.radiusMedium
            color: isSelected
                   ? (ThemeManager.primaryColor)
                   : (ThemeManager.surfaceSecondaryColor)
            border.color: isSelected
                          ? (ThemeManager.accentColor)
                          : (ThemeManager.borderColor)
            border.width: isSelected ? 2 : 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                spacing: SpacingManager.space12

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 36
                    height: 36
                    radius: width / 2
                    color: ThemeManager.surfaceSecondaryColor

                    Text {
                        anchors.centerIn: parent
                        text: modelData.displayName.length > 0
                              ? modelData.displayName.charAt(0).toUpperCase()
                              : "?"
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.DemiBold
                    }
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: SpacingManager.space2

                    Text {
                        text: modelData.displayName
                        color: isSelected
                               ? (ThemeManager.textPrimary)
                               : (ThemeManager.textPrimary)
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        font.weight: Font.DemiBold
                    }

                    Text {
                        text: modelData.administrator ? "Administrator" : "User"
                        color: isSelected
                               ? (ThemeManager.textPrimary)
                               : (ThemeManager.textPrimary)
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (loginManager) {
                        loginManager.selectUser(modelData.username);
                    }
                }
            }
        }
    }
}
