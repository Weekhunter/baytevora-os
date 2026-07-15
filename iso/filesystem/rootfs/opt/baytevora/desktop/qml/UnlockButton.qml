import QtQuick

/**
 * @brief Flat BDL-styled unlock button.
 *
 * Clicking the button requests unlock through the LockManager. The button is
 * disabled while the lock manager is in the Unlocking state.
 */
Rectangle {
    id: root

    width: 160
    height: 40
    radius: DesignTokens.radiusMedium
    color: ThemeManager.primaryColor

    Text {
        anchors.centerIn: parent
        text: "Unlock"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    MouseArea {
        anchors.fill: parent
        enabled: lockManager && lockManager.lockState !== LockState.Unlocking
        onClicked: {
            if (lockManager) {
                lockManager.unlock();
            }
        }
    }
}
