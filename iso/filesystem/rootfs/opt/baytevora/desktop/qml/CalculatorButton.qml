import QtQuick

/**
 * @brief Individual button for the Calculator keypad.
 *
 * CalculatorButton supports digit, operator, and function roles and uses
 * the Baytevora Design Language tokens for colors, typography, and radius.
 */
Rectangle {
    id: root

    property string label: ""
    property string role: "digit"

    signal clicked()

    color: {
        if (!ThemeManager) {
            return "ThemeManager.surfaceSecondaryColor";
        }
        if (role === "operator") {
            return ThemeManager.primaryColor;
        }
        if (role === "function") {
            return ThemeManager.surfaceSecondaryColor;
        }
        return ThemeManager.surfaceColor;
    }

    radius: DesignTokens.radiusMedium

    Text {
        anchors.centerIn: parent
        text: root.label
        color: {
            if (!ThemeManager) {
                return "ThemeManager.textPrimary";
            }
            if (root.role === "operator") {
                return ThemeManager.textPrimary;
            }
            return ThemeManager.textPrimary;
        }
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.Medium
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
