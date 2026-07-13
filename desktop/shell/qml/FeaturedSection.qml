import QtQuick

/**
 * @brief Horizontal featured apps section for the Baytevora Store.
 */
Column {
    id: root

    property var model: []

    signal openDetails(var item)

    spacing: SpacingManager.space12
    width: parent ? parent.width : 600

    Text {
        text: "Featured"
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.title
        font.family: TypographyManager.fontFamily
        font.weight: Font.DemiBold
    }

    Flickable {
        width: parent.width
        height: 220
        contentWidth: featuredRow.width
        clip: true

        Row {
            id: featuredRow

            spacing: SpacingManager.space16

            Repeater {
                model: root.model

                ApplicationCard {
                    itemData: modelData
                    width: 240
                    onOpenDetails: (item) => root.openDetails(item)
                }
            }
        }
    }
}
