import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    spacing: SpacingManager.space16

    Text {
        text: "License Agreement"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.weight: 600
        font.family: TypographyManager.fontFamily
    }

    Text {
        text: "Please read the following license agreement carefully. You must accept it to continue."
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
        clip: true

        ScrollView {
            anchors.fill: parent
            anchors.margins: SpacingManager.space16
            contentWidth: width

            TextArea {
                id: licenseText
                readOnly: true
                wrapMode: Text.WordWrap
                text: ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.body
                font.family: TypographyManager.fontFamily
                background: null

                Component.onCompleted: {
                    var req = new XMLHttpRequest();
                    req.onreadystatechange = function() {
                        if (req.readyState === XMLHttpRequest.DONE && req.status === 200) {
                            licenseText.text = req.responseText;
                        }
                    };
                    req.open("GET", "qrc:/data/license.txt");
                    req.send();
                }
            }
        }
    }

    RowLayout {
        spacing: SpacingManager.space12

        CheckBox {
            id: acceptBox
            checked: installerSession.licenseAccepted
            onCheckedChanged: installerSession.licenseAccepted = checked
        }

        Text {
            text: "I accept the license agreement"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Item { Layout.fillWidth: true }
    }
}
