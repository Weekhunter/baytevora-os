import QtQuick

/**
 * @brief Delegate for a print job in the Print Manager queue.
 */
Rectangle {
    id: root

    property var job: null
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
            width: parent.width * 0.10
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.jobId : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.26
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.documentName : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.printerName : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.08
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.pages : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.12
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.status : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.job ? root.job.submittedTime : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }
    }
}
