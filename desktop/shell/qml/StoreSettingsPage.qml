import QtQuick

/**
 * @brief Read-only Settings page for the Baytevora Store catalog.
 */
Rectangle {
    id: root

    width: parent ? parent.width : 400
    height: parent ? parent.height : 300
    color: "transparent"

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
        radius: DesignTokens ? DesignTokens.radiusLarge : 16

        Column {
            anchors.fill: parent
            anchors.margins: SpacingManager ? SpacingManager.space24 : 24
            spacing: SpacingManager ? SpacingManager.space14 : 14

            Text {
                text: "Baytevora Store"
                color: "#0f172a"
                font.pixelSize: TypographyManager ? TypographyManager.title : 18
                font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                font.weight: Font.DemiBold
            }

            InfoRow {
                label: "Catalog size"
                value: storeManager ? storeManager.allItems.length.toString() : "—"
            }

            InfoRow {
                label: "Featured apps"
                value: storeManager ? storeManager.featuredItems.length.toString() : "—"
            }

            InfoRow {
                label: "Installed apps"
                value: {
                    if (!storeManager) return "—";
                    let count = 0;
                    const all = storeManager.allItems;
                    for (let i = 0; i < all.length; ++i) {
                        if (all[i].installed) ++count;
                    }
                    return count.toString();
                }
            }
        }
    }
}
