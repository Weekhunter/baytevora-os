import QtQuick

/**
 * @brief Print job queue table for the Print Manager.
 */
Rectangle {
    id: root

    property var printManager: null
    property int selectedJobId: -1

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    signal jobSelected(int jobId)

    Column {
        anchors.fill: parent
        spacing: 0

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
                    width: parent.width * 0.10
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Job"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.26
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Document"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Printer"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.08
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Pages"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.12
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Status"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Submitted"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }
            }
        }

        ListView {
            id: listView

            width: parent.width
            height: parent.height - header.height
            model: root.printManager ? root.printManager.jobs : []
            clip: true

            delegate: PrintJobDelegate {
                width: listView.width
                job: modelData
                selected: modelData && modelData.jobId === root.selectedJobId

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (modelData) {
                            root.selectedJobId = modelData.jobId;
                            root.jobSelected(modelData.jobId);
                        }
                    }
                }
            }
        }
    }
}
