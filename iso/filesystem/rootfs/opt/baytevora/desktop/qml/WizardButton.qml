import QtQuick
import BOS.Shell

/**
 * @brief Reusable button for the first-boot wizard.
 *
 * WizardButton follows BDL v2 with a primary accent style and a secondary
 * outline style. It is a simple Rectangle + Text + MouseArea to avoid
 * dependency on external control styles.
 */
Rectangle {
    id: root

    property string text: ""
    property bool primary: false
    property bool enabled: true

    signal clicked()

    width: 120
    height: 40
    radius: DesignTokens.radiusSmall
    color: primary
              ? (enabled ? ThemeManager.highlightColor : ThemeManager.surfaceSecondaryColor)
              : ThemeManager.surfaceSecondaryColor
    border.color: primary
                  ? "transparent"
                  : ThemeManager.borderColor
    border.width: primary ? 0 : 1
    opacity: enabled ? 1.0 : 0.5

    Text {
        anchors.centerIn: parent
        text: root.text
        color: primary ? ThemeManager.backgroundColor : ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        font.weight: Font.Medium
    }

    MouseArea {
        anchors.fill: parent
        enabled: root.enabled
        onClicked: root.clicked()
    }
}
