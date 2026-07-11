import QtQuick

/**
 * @brief Horizontal featured apps section for the Baytevora Store.
 */
Column {
    id: root

    property var model: []

    signal openDetails(var item)

    spacing: SpacingManager ? SpacingManager.space12 : 12
    width: parent ? parent.width : 600

    Text {
        text: "Featured"
        color: ThemeManager ? ThemeManager.textPrimary : "#F8FAFC"
        font.pixelSize: TypographyManager ? TypographyManager.title : 18
        font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
        font.weight: Font.DemiBold
    }

    Flickable {
        width: parent.width
        height: 220
        contentWidth: featuredRow.width
        clip: true

        Row {
            id: featuredRow

            spacing: SpacingManager ? SpacingManager.space16 : 16

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
