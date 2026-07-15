import QtQuick

/**
 * @brief Status bar for the Task Manager.
 */
Rectangle {
    id: root

    property var taskManager: null
    property string selectedApplication: ""

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.taskManager
                  ? "Running applications: " + root.taskManager.tasks.length
                  : "Running applications: 0"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.selectedApplication.length > 0
                  ? "Selected: " + root.selectedApplication
                  : "Selected: none"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
