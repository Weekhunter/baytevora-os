import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space16

    Text {
        text: "Choose an installation type"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    Text {
        text: "Select how Baytevora OS should be installed on your system."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WordWrap
    }

    ColumnLayout {
        spacing: SpacingManager.space12
        Layout.fillWidth: true

        Repeater {
            model: installerSession.installationTypes

            Rectangle {
                Layout.fillWidth: true
                height: 64
                radius: DesignTokens.radiusMedium
                color: installerSession.installationType === modelData
                    ? ThemeManager.highlightColor
                    : ThemeManager.surfaceSecondaryColor
                border.color: installerSession.installationType === modelData
                    ? ThemeManager.highlightColor
                    : ThemeManager.borderColor
                border.width: 1
                opacity: index === 0 ? 1.0 : 0.6

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: SpacingManager.space16
                    anchors.rightMargin: SpacingManager.space16

                    RadioButton {
                        checked: installerSession.installationType === modelData
                        enabled: index === 0
                        onClicked: if (index === 0) installerSession.installationType = modelData
                    }

                    ColumnLayout {
                        spacing: 4

                        Text {
                            text: modelData
                            color: installerSession.installationType === modelData
                                ? "#FFFFFF"
                                : ThemeManager.textPrimary
                            font.pixelSize: TypographyManager.body
                            font.weight: 600
                            font.family: TypographyManager.fontFamily
                        }

                        Text {
                            text: index === 0
                                ? "Install Baytevora OS on the selected disk."
                                : "Available in a future release."
                            color: installerSession.installationType === modelData
                                ? "#FFFFFF"
                                : ThemeManager.textSecondary
                            font.pixelSize: TypographyManager.caption
                            font.family: TypographyManager.fontFamily
                        }
                    }

                    Item { Layout.fillWidth: true }
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: index === 0
                    onClicked: installerSession.installationType = modelData
                }
            }
        }
    }
}
