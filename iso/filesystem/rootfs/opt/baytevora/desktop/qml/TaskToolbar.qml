import QtQuick

/**
 * @brief Task Manager toolbar with refresh and end-task actions.
 */
Rectangle {
    id: root

    property var taskManager: null
    property int selectedProcessId: -1

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        TaskToolButton {
            label: "Refresh"
            onClicked: {
                if (root.taskManager) {
                    root.taskManager.refresh();
                }
            }
        }

        TaskToolButton {
            label: "End Task"
            onClicked: {
                if (root.taskManager && root.selectedProcessId >= 0) {
                    root.taskManager.terminateTask(root.selectedProcessId);
                }
            }
        }
    }
}
