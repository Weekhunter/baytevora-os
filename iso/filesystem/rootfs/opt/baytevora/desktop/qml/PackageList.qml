import QtQuick

/**
 * @brief Reusable vertical list of PackageCard components.
 */
Column {
    id: root

    property var model: []
    property bool readOnly: false

    signal packageSelected(string packageId)

    spacing: SpacingManager.space12
    width: parent ? parent.width : 400

    Repeater {
        model: root.model

        delegate: PackageCard {
            packageData: modelData
            onPackageSelected: (packageId) => root.packageSelected(packageId)
        }
    }
}
