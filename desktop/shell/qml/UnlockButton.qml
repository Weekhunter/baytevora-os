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
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    color: ThemeManager ? ThemeManager.primaryColor : "#2563EB"

    Text {
        anchors.centerIn: parent
        text: "Unlock"
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.body : 14
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
