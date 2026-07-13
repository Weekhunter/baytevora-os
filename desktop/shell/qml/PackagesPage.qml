import QtQuick

/**
 * @brief Package list page for the Baytevora Package Manager Phase 2.
 *
 * PackagesPage shows installed and available package counts and a scrollable
 * list of PackageCards. Selecting a package emits packageSelected so other
 * views can inspect its dependencies.
 */
Rectangle {
    id: root

    signal packageSelected(string packageId)

    width: parent ? parent.width : 400
    height: parent ? parent.height : 300
    color: "transparent"

    Column {
        anchors.fill: parent
        spacing: SpacingManager.space16

        Rectangle {
            width: parent.width
            height: summaryColumn.height + 48
            color: ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusLarge
            border.color: ThemeManager.borderColor
            border.width: 1

            Column {
                id: summaryColumn

                anchors.fill: parent
                anchors.margins: SpacingManager.space24
                spacing: SpacingManager.space14

                Text {
                    text: "Packages"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.title
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                InfoRow {
                    label: "Installed"
                    value: packageManager ? packageManager.installedPackages.length.toString() : "—"
                }

                InfoRow {
                    label: "Available"
                    value: packageManager ? packageManager.availablePackages.length.toString() : "—"
                }

                InfoRow {
                    label: "Total"
                    value: packageManager ? packageManager.packageCount.toString() : "—"
                }
            }
        }

        Rectangle {
            width: parent.width
            height: parent.height - summaryColumn.height - 64
            color: ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusLarge
            border.color: ThemeManager.borderColor
            border.width: 1

            Flickable {
                anchors.fill: parent
                anchors.margins: SpacingManager.space16
                contentHeight: packageList.height
                clip: true

                PackageList {
                    id: packageList

                    width: parent.width
                    model: packageManager ? packageManager.packages : []
                    onPackageSelected: (packageId) => root.packageSelected(packageId)
                }
            }
        }
    }
}
