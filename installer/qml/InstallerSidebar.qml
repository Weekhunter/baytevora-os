import QtQuick
import QtQuick.Layouts
import BOI.Installer

Rectangle {
    id: root
    width: AdaptiveLayoutManager.sidebarWidth
    color: ThemeManager.surfaceColor

    property int currentStep: installerSession.currentPage

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: SpacingManager.space32
        anchors.leftMargin: SpacingManager.space24
        anchors.rightMargin: SpacingManager.space24
        spacing: SpacingManager.space16

        Repeater {
            model: [
                "Welcome",
                "Language",
                "Keyboard",
                "License",
                "Type",
                "Disk",
                "Summary",
                "Install",
                "Complete"
            ]

            RowLayout {
                spacing: SpacingManager.space12
                opacity: index <= root.currentStep ? 1.0 : 0.5

                Rectangle {
                    width: 24
                    height: 24
                    radius: width / 2
                    color: index === root.currentStep
                        ? ThemeManager.highlightColor
                        : (index < root.currentStep ? ThemeManager.successColor : ThemeManager.surfaceSecondaryColor)
                    border.color: index === root.currentStep ? ThemeManager.highlightColor : ThemeManager.borderColor
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: index + 1
                        color: index <= root.currentStep ? "#FFFFFF" : ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.caption
                        font.weight: 600
                    }
                }

                Text {
                    text: modelData
                    color: index === root.currentStep
                        ? ThemeManager.highlightColor
                        : (index < root.currentStep ? ThemeManager.textPrimary : ThemeManager.textSecondary)
                    font.pixelSize: TypographyManager.body
                    font.weight: index === root.currentStep ? 600 : 400
                    font.family: TypographyManager.fontFamily
                }

                Item { Layout.fillWidth: true }
            }
        }

        Item { Layout.fillHeight: true }
    }

    Rectangle {
        anchors.right: parent.right
        width: 1
        height: parent.height
        color: ThemeManager.borderColor
    }
}
