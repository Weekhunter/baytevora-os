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
    radius: DesignTokens ? DesignTokens.radiusMedium : 8
    color: ThemeManager ? ThemeManager.primaryColor : "#2563EB"

    Text {
        anchors.centerIn: parent
        text: "Check for Updates"
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.body : 14
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
