import QtQuick

/**
 * @brief Static header for the launcher panel.
 *
 * LauncherHeader shows the system name and a short welcome line. It contains
 * no interactive elements or dynamic content.
 */
Column {
    id: root

    spacing: 4
    width: parent ? parent.width : 320

    Text {
        text: "Baytevora OS"
        color: "ThemeManager.textSecondary"
        font.pixelSize: 18
        font.weight: Font.Bold
    }

    Text {
        text: "Welcome"
        color: "ThemeManager.textDisabled"
        font.pixelSize: 14
    }
}
