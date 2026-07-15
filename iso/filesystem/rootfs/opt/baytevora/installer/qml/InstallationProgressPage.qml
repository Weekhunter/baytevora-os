import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space24

    Text {
        text: "Installing Baytevora OS"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    InstallerProgress {
        Layout.fillWidth: true
        progress: installerManager.installationProgress
        description: installerManager.currentStepDescription
        remaining: installerManager.estimatedTimeRemaining
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        color: ThemeManager.surfaceSecondaryColor
        radius: DesignTokens.radiusMedium
        border.color: ThemeManager.borderColor
        border.width: 1
        clip: true

        ScrollView {
            anchors.fill: parent
            anchors.margins: SpacingManager.space16
            contentWidth: width

            TextArea {
                readOnly: true
                wrapMode: Text.WordWrap
                text: installerManager.getInstallationLogs()
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
                background: null
            }
        }
    }
}
