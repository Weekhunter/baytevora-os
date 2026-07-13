import QtQuick

/**
 * @brief Top toolbar for the Baytevora Package Manager Phase 2.
 */
Rectangle {
    id: root

    property int currentSection: 0

    signal sectionSelected(int section)

    width: parent ? parent.width : 600
    height: AdaptiveLayoutManager.toolbarHeight
    color: ThemeManager.surfaceColor

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "Package Manager"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.title
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }

        Item {
            width: SpacingManager.space16
            height: parent.height
        }

        Repeater {
            model: [
                { "label": "Packages", "icon": "📦" },
                { "label": "Repositories", "icon": "🗂" },
                { "label": "Transactions", "icon": "↻" },
                { "label": "Dependencies", "icon": "🔗" }
            ]

            delegate: Rectangle {
                width: sectionLabel.width + 24
                height: parent.height
                radius: DesignTokens.radiusSmall
                color: root.currentSection === index
                       ? (ThemeManager.accentColor)
                       : "transparent"

                Text {
                    id: sectionLabel

                    anchors.centerIn: parent
                    text: modelData.label
                    color: root.currentSection === index
                           ? (ThemeManager.textPrimary)
                           : (ThemeManager.textSecondary)
                    font.pixelSize: TypographyManager.body
                    font.family: TypographyManager.fontFamily
                    font.weight: root.currentSection === index ? Font.DemiBold : Font.Normal
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: root.sectionSelected(index)
                }
            }
        }
    }
}
