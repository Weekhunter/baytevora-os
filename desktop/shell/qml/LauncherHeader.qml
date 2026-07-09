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
        color: "#e2e8f0"
        font.pixelSize: 18
        font.weight: Font.Bold
    }

    Text {
        text: "Welcome"
        color: "#94a3b8"
        font.pixelSize: 14
    }
}
