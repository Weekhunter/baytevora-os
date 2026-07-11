import QtQuick

/**
 * @brief Settings page for the Baytevora Package Manager (BPM).
 *
 * PackagesPage shows installed and available package counts and a scrollable
 * list of PackageCards.
 */
Rectangle {
    id: root

    width: parent ? parent.width : 400
    height: parent ? parent.height : 300
    color: "transparent"

    Column {
        anchors.fill: parent
        spacing: SpacingManager ? SpacingManager.space16 : 16

        Rectangle {
            width: parent.width
            height: summaryColumn.height + 48
            color: "#ffffff"
            radius: DesignTokens ? DesignTokens.radiusLarge : 16

            Column {
                id: summaryColumn

                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space24 : 24
                spacing: SpacingManager ? SpacingManager.space14 : 14

                Text {
                    text: "Packages"
                    color: "#0f172a"
                    font.pixelSize: TypographyManager ? TypographyManager.title : 18
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
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
            color: "#ffffff"
            radius: DesignTokens ? DesignTokens.radiusLarge : 16

            Flickable {
                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space16 : 16
                contentHeight: packageList.height
                clip: true

                PackageList {
                    id: packageList

                    width: parent.width
                    model: packageManager ? packageManager.packages : []
                }
            }
        }
    }
}
