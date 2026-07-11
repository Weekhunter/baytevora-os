import QtQuick

/**
 * @brief Small status badge that shows a package state using BDL tokens.
 */
Rectangle {
    id: root

    property int packageState: 0

    height: 22
    width: statusText.width + 16
    radius: DesignTokens ? DesignTokens.radiusSmall : 4
    color: {
        if (!packageManager) {
            return ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155";
        }
        const stateName = packageManager.stateName(root.packageState);
        if (stateName === "Installed") return ThemeManager ? ThemeManager.successColor : "#22c55e";
        if (stateName === "Update Available") return ThemeManager ? ThemeManager.warningColor : "#f59e0b";
        if (stateName === "Disabled") return ThemeManager ? ThemeManager.errorColor : "#ef4444";
        return ThemeManager ? ThemeManager.surfaceSecondaryColor : "#334155";
    }

    Text {
        id: statusText

        anchors.centerIn: parent
        text: packageManager ? packageManager.stateName(root.packageState) : ""
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.caption : 12
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        font.weight: Font.DemiBold
    }
}
