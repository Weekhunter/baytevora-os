import QtQuick
import BOS.Shell

/**
 * @brief Baytevora Lock Screen (BLS) overlay.
 *
 * LockScreen covers the entire desktop when locked, preventing interaction with
 * running applications. It displays the current time, date, the selected user
 * avatar, the display name, and an unlock button.
 */
Rectangle {
    id: root

    anchors.fill: parent
    visible: lockManager ? lockManager.isLocked : false
    color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#0f172a"
    z: 300

    // Capture all pointer events while locked so the desktop underneath cannot
    // be interacted with. UI elements placed after this MouseArea render above
    // it and still receive input.
    MouseArea {
        anchors.fill: parent
        enabled: lockManager ? lockManager.isLocked : false
    }

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager ? SpacingManager.space16 : 16
        width: Math.min(parent.width * 0.8, 320)

        Clock {
            anchors.horizontalCenter: parent.horizontalCenter
            height: 48
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: Qt.formatDate(new Date(), "dddd, MMMM d")
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.subtitle : 16
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 72
            height: 72
            radius: width / 2
            color: ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155"
            border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
            border.width: 2

            Text {
                anchors.centerIn: parent
                text: {
                    if (loginManager && loginManager.selectedUser
                        && loginManager.selectedUser.displayName.length > 0) {
                        return loginManager.selectedUser.displayName.charAt(0).toUpperCase();
                    }
                    return "?";
                }
                color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
                font.pixelSize: TypographyManager ? TypographyManager.displaySize : 48
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.Bold
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: loginManager && loginManager.selectedUser
                  ? loginManager.selectedUser.displayName
                  : "Baytevora User"
            color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
            font.pixelSize: TypographyManager ? TypographyManager.title : 18
            font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
            font.weight: Font.DemiBold
        }

        UnlockButton {
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
