import QtQuick
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    id: root
    spacing: SpacingManager.space8

    property var devices: storageManager.devices
    property string selectedDiskId: installerSession.selectedDiskId

    Repeater {
        model: root.devices

        Rectangle {
            Layout.fillWidth: true
            height: 72
            radius: DesignTokens.radiusMedium
            color: root.selectedDiskId === modelData.deviceName
                ? ThemeManager.highlightColor
                : ThemeManager.surfaceSecondaryColor
            border.color: root.selectedDiskId === modelData.deviceName
                ? ThemeManager.highlightColor
                : ThemeManager.borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: SpacingManager.space16
                anchors.rightMargin: SpacingManager.space16
                spacing: SpacingManager.space16

                ColumnLayout {
                    spacing: 4
                    Layout.fillWidth: true

                    Text {
                        text: modelData.displayName || modelData.deviceName
                        color: root.selectedDiskId === modelData.deviceName
                            ? "#FFFFFF"
                            : ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.weight: 600
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        text: (modelData.model || "Unknown model") + " — " + Number(modelData.capacity / 1024 / 1024 / 1024).toFixed(2) + " GB"
                        color: root.selectedDiskId === modelData.deviceName
                            ? "#FFFFFF"
                            : ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.family: TypographyManager.fontFamily
                    }
                }

                Text {
                    text: modelData.removable ? "Removable" : "Fixed"
                    color: root.selectedDiskId === modelData.deviceName
                        ? "#FFFFFF"
                        : ThemeManager.textSecondary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: installerSession.selectedDiskId = modelData.deviceName
            }
        }
    }
}
