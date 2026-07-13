import QtQuick

/**
 * @brief Small status badge that shows a package state using BDL tokens.
 */
Rectangle {
    id: root

    property int packageState: 0

    height: 22
    width: statusText.width + 16
    radius: DesignTokens.radiusSmall
    color: {
        if (!packageManager) {
            return ThemeManager.surfaceSecondaryColor;
        }
        const stateName = packageManager.stateName(root.packageState);
        if (stateName === "Installed") return ThemeManager.successColor;
        if (stateName === "Update Available") return ThemeManager.warningColor;
        if (stateName === "Disabled") return ThemeManager.errorColor;
        return ThemeManager.surfaceSecondaryColor;
    }

    Text {
        id: statusText

        anchors.centerIn: parent
        text: packageManager ? packageManager.stateName(root.packageState) : ""
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }
}
