import QtQuick

/**
 * @brief Storage Manager toolbar with refresh action.
 */
Rectangle {
    id: root

    property var storageManager: null

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        StorageToolButton {
            label: "Refresh"
            onClicked: {
                if (root.storageManager) {
                    root.storageManager.refresh();
                }
            }
        }
    }
}
