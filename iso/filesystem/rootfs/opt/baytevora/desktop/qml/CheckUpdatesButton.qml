import QtQuick

/**
 * @brief BDL-styled button that requests an update check.
 *
 * The button is disabled while the UpdateManager is already checking for
 * updates.
 */
Rectangle {
    id: root

    width: 180
    height: 40
    radius: DesignTokens.radiusMedium
    color: ThemeManager.primaryColor

    Text {
        anchors.centerIn: parent
        text: "Check for Updates"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    MouseArea {
        anchors.fill: parent
        enabled: updateManager && updateManager.updateState !== UpdateState.Checking
        onClicked: {
            if (updateManager) {
                updateManager.checkForUpdates();
            }
        }
    }
}
