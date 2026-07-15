import QtQuick
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space16

    Text {
        text: "Select your language"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    Text {
        text: "This will be the default language for the installed system."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: Text.WordWrap
    }

    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        clip: true
        model: installerSession.languages
        spacing: SpacingManager.space8

        delegate: Rectangle {
            width: listView.width
            height: 48
            radius: DesignTokens.radiusMedium
            color: installerSession.selectedLanguage === modelData
                ? ThemeManager.highlightColor
                : ThemeManager.surfaceSecondaryColor
            border.color: installerSession.selectedLanguage === modelData
                ? ThemeManager.highlightColor
                : ThemeManager.borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: SpacingManager.space16
                anchors.rightMargin: SpacingManager.space16

                Text {
                    text: modelData
                    color: installerSession.selectedLanguage === modelData
                        ? "#FFFFFF"
                        : ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                }

                Item { Layout.fillWidth: true }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: installerSession.selectedLanguage = modelData
            }
        }
    }
}
