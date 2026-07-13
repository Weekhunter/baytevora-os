import QtQuick

/**
 * @brief Delegate row for a running task in the Task Manager process table.
 */
Rectangle {
    id: root

    property var task: null
    property bool selected: false

    width: parent ? parent.width : 600
    height: AdaptiveLayoutManager.listItemHeight
    color: root.selected
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.backgroundColor)
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space8

        Text {
            width: parent.width * 0.28
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.applicationName : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.14
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.processId : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.14
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.cpuUsage + "%" : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.16
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.memoryUsageText : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.14
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.state : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.14
            anchors.verticalCenter: parent.verticalCenter
            text: root.task ? root.task.startTime : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }
    }
}
