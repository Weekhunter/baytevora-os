import QtQuick

/**
 * @brief Table of running tasks for the Task Manager.
 */
Rectangle {
    id: root

    property var taskManager: null
    property int selectedProcessId: -1

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal processSelected(int processId)

    Column {
        anchors.fill: parent
        spacing: 0

        // Header row.
        Rectangle {
            width: parent.width
            height: AdaptiveLayoutManager.listHeaderHeight
            color: ThemeManager.surfaceColor
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
                    text: "Application"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.14
                    anchors.verticalCenter: parent.verticalCenter
                    text: "PID"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.14
                    anchors.verticalCenter: parent.verticalCenter
                    text: "CPU %"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.16
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Memory"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.14
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Status"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.14
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Start Time"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }
        }

        // Process rows.
        ListView {
            id: listView

            width: parent.width
            height: parent.height - header.height
            model: root.taskManager ? root.taskManager.tasks : []
            clip: true

            delegate: ProcessDelegate {
                width: listView.width
                task: modelData
                selected: modelData && modelData.processId === root.selectedProcessId

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedProcessId = modelData.processId;
                        root.processSelected(modelData.processId);
                    }
                }
            }
        }
    }
}
