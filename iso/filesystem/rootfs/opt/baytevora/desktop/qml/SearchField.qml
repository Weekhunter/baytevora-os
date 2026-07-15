import QtQuick
import QtQuick.Controls

/**
 * @brief Search input field for the launcher.
 *
 * SearchField emits textEdited(text) while the user types. It uses the
 * Baytevora Design Language tokens when available and falls back to neutral
 * defaults otherwise.
 */
TextField {
    id: root

    placeholderText: "Search..."
    focus: launcher ? launcher.visible : false
    color: "ThemeManager.textSecondary"
    placeholderTextColor: "ThemeManager.textDisabled"
    font.pixelSize: 14

    background: Rectangle {
        color: "ThemeManager.backgroundColor"
        border.color: "ThemeManager.borderColor"
        border.width: 1
        radius: DesignTokens.radiusSmall
    }
}
