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
    color: "#e2e8f0"
    placeholderTextColor: "#94a3b8"
    font.pixelSize: 14

    background: Rectangle {
        color: "#0f172a"
        border.color: "#475569"
        border.width: 1
        radius: DesignTokens ? DesignTokens.radiusSmall : 6
    }
}
