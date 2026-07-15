import QtQuick
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space16

    Text {
        text: "Installation Summary"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    Text {
        text: "Review your choices before starting the installation."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WordWrap
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: ThemeManager.surfaceSecondaryColor
        radius: DesignTokens.radiusMedium
        border.color: ThemeManager.borderColor
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: SpacingManager.space24
            spacing: SpacingManager.space16

            SummaryRow { label: "Language"; value: installerSession.selectedLanguage }
            SummaryRow { label: "Keyboard"; value: installerSession.selectedKeyboard }
            SummaryRow { label: "Installation Type"; value: installerSession.installationType }
            SummaryRow { label: "Target Disk"; value: installerSession.selectedDiskId }
            SummaryRow { label: "Estimated Space Required"; value: "20 GB" }

            Item { Layout.fillHeight: true }
        }
    }
}
