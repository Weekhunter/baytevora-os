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
    color: ThemeManager.surfaceSecondaryColor
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
        spacing: SpacingManager.space16
        width: Math.min(parent.width * 0.8, 320)

        // Official Baytevora OS symbol
        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 64
            height: 77
            source: BrandingManager.applicationSymbolUrl("Baytevora OS")
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 128
            sourceSize.height: 154
        }

        Clock {
            anchors.horizontalCenter: parent.horizontalCenter
            height: 48
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: Qt.formatDate(new Date(), "dddd, MMMM d")
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.subtitle
            font.family: TypographyManager.fontFamily
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 72
            height: 72
            radius: width / 2
            color: ThemeManager.surfaceSecondaryColor
            border.color: ThemeManager.borderColor
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
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.displaySize
                font.family: TypographyManager.fontFamily
                font.weight: Font.Bold
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: loginManager && loginManager.selectedUser
                  ? loginManager.selectedUser.displayName
                  : "Baytevora User"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        UnlockButton {
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
