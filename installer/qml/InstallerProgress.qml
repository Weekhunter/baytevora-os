import QtQuick
import QtQuick.Layouts
import BOI.Installer

ColumnLayout {
    id: root
    spacing: SpacingManager.space12

    property int progress: 0
    property string description: ""
    property string remaining: ""

    Text {
        text: root.description
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }

    Rectangle {
        Layout.fillWidth: true
        height: 8
        color: ThemeManager.surfaceSecondaryColor
        radius: height / 2

        Rectangle {
            width: parent.width * (root.progress / 100.0)
            height: parent.height
            color: ThemeManager.highlightColor
            radius: parent.radius
        }
    }

    RowLayout {
        Layout.fillWidth: true

        Text {
            text: root.progress + "%"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Item { Layout.fillWidth: true }

        Text {
            text: root.remaining
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
