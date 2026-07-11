import QtQuick

/**
 * @brief List of available users on the login screen.
 *
 * UserList displays users vertically and supports selecting a user. The current
 * sprint provides a single default user.
 */
Column {
    id: root

    spacing: SpacingManager ? SpacingManager.space8 : 8
    width: 200

    Repeater {
        model: loginManager ? loginManager.users : []

        delegate: Rectangle {
            id: userItem

            property bool isSelected: loginManager && loginManager.selectedUser
                                      && loginManager.selectedUser.username === modelData.username

            width: root.width
            height: 56
            radius: DesignTokens ? DesignTokens.radiusMedium : 8
            color: isSelected
                   ? (ThemeManager ? ThemeManager.primaryColor : "#2563EB")
                   : (ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155")
            border.color: isSelected
                          ? (ThemeManager ? ThemeManager.accentColor : "#38bdf8")
                          : (ThemeManager ? ThemeManager.borderColor : "#475569")
            border.width: isSelected ? 2 : 1

            Row {
                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space12 : 12
                spacing: SpacingManager ? SpacingManager.space12 : 12

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    width: 36
                    height: 36
                    radius: width / 2
                    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"

                    Text {
                        anchors.centerIn: parent
                        text: modelData.displayName.length > 0
                              ? modelData.displayName.charAt(0).toUpperCase()
                              : "?"
                        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                        font.pixelSize: TypographyManager ? TypographyManager.body : 14
                        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                        font.weight: Font.DemiBold
                    }
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: SpacingManager ? SpacingManager.space2 : 2

                    Text {
                        text: modelData.displayName
                        color: isSelected
                               ? (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                               : (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                        font.pixelSize: TypographyManager ? TypographyManager.body : 14
                        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                        font.weight: Font.DemiBold
                    }

                    Text {
                        text: modelData.administrator ? "Administrator" : "User"
                        color: isSelected
                               ? (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                               : (ThemeManager ? ThemeManager.textPrimary : "#F8FAFC")
                        font.pixelSize: TypographyManager ? TypographyManager.caption : 12
                        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
