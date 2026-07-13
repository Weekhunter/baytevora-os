import QtQuick

/**
 * @brief Main view of the native Task Manager application.
 *
 * TaskManagerWindow fills the content area of a WindowFrame and arranges the
 * toolbar, process table, details panel, and status bar. Each Task Manager
 * window owns its own TaskManager so task state stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    property var selectedTask: null

    TaskManager {
        id: taskManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                taskManager.setNotificationManager(notificationManager);
            }
            if (typeof windowManager !== "undefined") {
                taskManager.setWindowManager(windowManager);
            }
            taskManager.startMonitoring();
        }

        Component.onDestruction: {
            taskManager.stopMonitoring();
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        TaskToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            taskManager: taskManager
            selectedProcessId: processTable.selectedProcessId
        }

        ProcessTable {
            id: processTable

            width: parent.width
            height: parent.height - toolbar.height - detailsPanel.height - statusBar.height
            taskManager: taskManager

            onProcessSelected: function (processId) {
                root.selectedTask = taskManager.tasks.find(function (task) {
                    return task.processId === processId;
                });
            }
        }

        ProcessDetails {
            id: detailsPanel

            width: parent.width
            height: 140
            task: root.selectedTask
        }

        TaskStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            taskManager: taskManager
            selectedApplication: root.selectedTask ? root.selectedTask.applicationName : ""
        }
    }
}
