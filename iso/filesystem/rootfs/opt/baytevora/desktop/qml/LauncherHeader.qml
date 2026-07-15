import QtQuick
import BOS.Shell

/**
 * @brief Static header for the launcher panel.
 *
 * LauncherHeader shows the official system name and version line. It contains
 * no interactive elements or dynamic content.
 */
Column {
    id: root

    spacing: 4
    width: parent ? parent.width : 320

    Text {
        text: BrandingManager.osName
        color: ThemeManager.textSecondary
        font.pixelSize: 18
        font.weight: Font.Bold
    }

    Text {
        text: BrandingManager.osVersion
        color: ThemeManager.textDisabled
        font.pixelSize: 14
    }
}
