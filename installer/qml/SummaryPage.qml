import QtQuick
import QtQuick.Layouts
import BOI.Installer

// Convenience alias used by PartitionSummaryPage.
RowLayout {
    id: root
    Layout.fillWidth: true
    spacing: SpacingManager.space12

    property string label: ""
    property string value: ""

    Text {
        text: root.label
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }

    Item { Layout.fillWidth: true }

    Text {
        text: root.value
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.weight: 600
        font.family: TypographyManager.fontFamily
        horizontalAlignment: Text.AlignRight
    }
}
