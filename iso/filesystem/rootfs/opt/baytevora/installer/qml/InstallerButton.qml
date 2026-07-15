import QtQuick
import QtQuick.Controls
import BOI.Installer

Button {
    id: root

    property bool primary: false
    property bool destructive: false

    height: 40
    width: Math.max(96, implicitWidth + SpacingManager.space24)

    background: Rectangle {
        color: {
            if (!root.enabled) return ThemeManager.surfaceSecondaryColor
            if (root.destructive) return ThemeManager.errorColor
            if (root.primary) return ThemeManager.highlightColor
            return ThemeManager.surfaceSecondaryColor
        }
        radius: DesignTokens.radiusMedium
        border.color: {
            if (root.destructive) return ThemeManager.errorColor
            if (root.primary) return ThemeManager.highlightColor
            return ThemeManager.borderColor
        }
        border.width: 1
    }

    contentItem: Text {
        text: root.text
        color: {
            if (!root.enabled) return ThemeManager.textDisabled
            if (root.destructive || root.primary) return "#FFFFFF"
            return ThemeManager.textPrimary
        }
        font.pixelSize: TypographyManager.body
        font.weight: 600
        font.family: TypographyManager.fontFamily
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
