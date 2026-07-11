import QtQuick

/**
 * @brief Reusable vertical list of PackageCard components.
 */
Column {
    id: root

    property var model: []
    property bool readOnly: false

    spacing: SpacingManager ? SpacingManager.space12 : 12
    width: parent ? parent.width : 400

    Repeater {
        model: root.model

        PackageCard {
            packageData: modelData
        }
    }
}
