import QtQuick

/**
 * @brief Settings page for Baytevora Update Manager (BUM).
 *
 * UpdatesPage shows the current version, latest version, update state,
 * available update count, a list of UpdateCards, and the Check for Updates
 * button.
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
            height: childrenRect.height + 48
            color: "#ffffff"
            radius: DesignTokens ? DesignTokens.radiusLarge : 16

            Column {
                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space24 : 24
                spacing: SpacingManager ? SpacingManager.space14 : 14

                Text {
                    text: "Updates"
                    color: ThemeManager ? ThemeManager.textPrimary : "#0f172a"
                    font.pixelSize: TypographyManager ? TypographyManager.title : 18
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                    font.weight: Font.DemiBold
                }

                InfoRow {
                    label: "Current Version"
                    value: updateManager ? updateManager.currentVersion : "—"
                }

                InfoRow {
                    label: "Latest Version"
                    value: updateManager ? updateManager.latestVersion : "—"
                }

                InfoRow {
                    label: "Update State"
                    value: updateManager ? updateManager.stateName() : "—"
                }

                InfoRow {
                    label: "Available Updates"
                    value: updateManager ? updateManager.updatesAvailable.toString() : "—"
                }

                CheckUpdatesButton {
                    anchors.left: parent.left
                }
            }
        }

        Rectangle {
            width: parent.width
            height: childrenRect.height + 32
            visible: updateManager && updateManager.updatesAvailable > 0
            color: "#ffffff"
            radius: DesignTokens ? DesignTokens.radiusLarge : 16

            Column {
                anchors.fill: parent
                anchors.margins: SpacingManager ? SpacingManager.space24 : 24
                spacing: SpacingManager ? SpacingManager.space12 : 12

                Text {
                    text: "Available Updates"
                    color: ThemeManager ? ThemeManager.textPrimary : "#0f172a"
                    font.pixelSize: TypographyManager ? TypographyManager.title : 18
                    font.family: TypographyManager ? TypographyManager.fontFamily : "Inter, sans-serif"
                    font.weight: Font.DemiBold
                }

                Repeater {
                    model: updateManager ? updateManager.availableUpdates : []

                    UpdateCard {
                        updateData: modelData
                    }
                }
            }
        }
    }
}
