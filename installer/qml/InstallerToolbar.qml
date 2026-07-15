import QtQuick
import QtQuick.Layouts
import BOI.Installer

Rectangle {
    id: root
    height: AdaptiveLayoutManager.toolbarHeight
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 0

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space24
        anchors.rightMargin: SpacingManager.space24
        spacing: SpacingManager.space12

        Image {
            source: brandingManager.applicationSymbolUrl("BOS")
            sourceSize.width: IconManager.medium
            sourceSize.height: IconManager.medium
            fillMode: Image.PreserveAspectFit
        }

        Text {
            text: brandingManager.osName
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.weight: 600
            font.family: TypographyManager.fontFamily
        }

        Item { Layout.fillWidth: true }

        Text {
            text: brandingManager.fullVersionLabel
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: ThemeManager.borderColor
    }
}
