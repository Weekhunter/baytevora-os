import QtQuick

/**
 * @brief Grid of ApplicationCard components for the Baytevora Store.
 */
Flow {
    id: root

    property var model: []

    signal openDetails(var item)

    width: parent ? parent.width : 600
    spacing: SpacingManager.space16

    Repeater {
        model: root.model

        ApplicationCard {
            itemData: modelData
            width: (root.width - root.spacing * 2) / 3
            onOpenDetails: (item) => root.openDetails(item)
        }
    }
}
