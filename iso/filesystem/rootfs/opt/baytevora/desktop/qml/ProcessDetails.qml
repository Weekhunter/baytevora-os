import QtQuick

/**
 * @brief Details panel for the selected task in the Task Manager.
 */
Rectangle {
    id: root

    property var task: null

    height: 140
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Grid {
        anchors.fill: parent
        anchors.margins: SpacingManager.space16
        columns: 2
        columnSpacing: SpacingManager.space32
        rowSpacing: SpacingManager.space8

        Text {
            text: root.task ? "Application: " + root.task.applicationName : "Application: -"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.task ? "Executable: " + root.task.executableName : "Executable: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.task ? "PID: " + root.task.processId : "PID: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.task ? "Windows: " + root.task.windowCount : "Windows: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.task ? "CPU: " + root.task.cpuUsage + "%" : "CPU: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.task ? "Memory: " + root.task.memoryUsageText : "Memory: -"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
