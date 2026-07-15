import QtQuick
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space16

    Text {
        text: "Select a target disk"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    Text {
        text: "Baytevora OS will be installed on the disk you choose. The disk must have at least 20 GB of free space."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WordWrap
    }

    DiskSelector {
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    Text {
        visible: installerSession.selectedDiskId.length > 0 && !installerManager.isDiskSuitable(installerSession.selectedDiskId)
        text: installerManager.validateDisk(installerSession.selectedDiskId)
        color: ThemeManager.errorColor
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WordWrap
    }
}
