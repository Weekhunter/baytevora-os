import QtQuick

/**
 * @brief Top toolbar for the Baytevora Store Phase 2.
 */
Rectangle {
    id: root

    property int currentSection: 0
    property string searchText: ""

    signal sectionSelected(int section)
    signal searchTextChangedSignal(string text)

    width: parent ? parent.width : 600
    height: AdaptiveLayoutManager.toolbarHeight
    color: ThemeManager.surfaceColor

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "Store"
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
                { "label": "Home", "icon": "🏠" },
                { "label": "Categories", "icon": "📂" },
                { "label": "Installed", "icon": "✓" },
                { "label": "Updates", "icon": "↻" }
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

        Item {
            height: parent.height
            width: parent.width - x - searchField.width - parent.spacing
        }

        TextField {
            id: searchField

            anchors.verticalCenter: parent.verticalCenter
            width: 180
            height: parent.height
            placeholderText: "Search..."
            text: root.searchText
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            background: Rectangle {
                color: ThemeManager.backgroundColor
                radius: DesignTokens.radiusSmall
                border.color: ThemeManager.borderColor
                border.width: 1
            }

            onTextChanged: root.searchTextChangedSignal(text)
        }
    }
}
