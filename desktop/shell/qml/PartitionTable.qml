import QtQuick

/**
 * @brief Table of partitions for the Storage Manager.
 */
Rectangle {
    id: root

    property var partitions: []

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

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
                    width: parent.width * 0.16
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Partition"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.14
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Filesystem"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.18
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Mount Point"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.12
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Capacity"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.10
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Used"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.10
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Free"
                    color: ThemeManager.textPrimary
                    font.pixelSize: TypographyManager.caption
                    font.family: TypographyManager.fontFamily
                    font.weight: Font.DemiBold
                }

                Text {
                    width: parent.width * 0.12
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Usage %"
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
            model: root.partitions
            clip: true

            delegate: Rectangle {
                width: listView.width
                height: AdaptiveLayoutManager.listItemHeight
                color: ThemeManager.backgroundColor
                border.color: ThemeManager.borderColor
                border.width: 1

                Row {
                    anchors.fill: parent
                    anchors.leftMargin: SpacingManager.space12
                    anchors.rightMargin: SpacingManager.space12
                    spacing: SpacingManager.space8

                    Text {
                        width: parent.width * 0.16
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.partitionName : ""
                        color: ThemeManager.textPrimary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }

                    Text {
                        width: parent.width * 0.14
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.filesystem : ""
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        width: parent.width * 0.18
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.mountPoint : ""
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                        elide: Text.ElideRight
                    }

                    Text {
                        width: parent.width * 0.12
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.totalSpaceText : ""
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        width: parent.width * 0.10
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.usedSpaceText : ""
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    Text {
                        width: parent.width * 0.10
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData ? modelData.freeSpaceText : ""
                        color: ThemeManager.textSecondary
                        font.pixelSize: TypographyManager.body
                        font.family: TypographyManager.fontFamily
                    }

                    Item {
                        width: parent.width * 0.12
                        height: parent.height

                        Rectangle {
                            anchors.verticalCenter: parent.verticalCenter
                            width: parent.width
                            height: SpacingManager.space8
                            color: ThemeManager.surfaceSecondaryColor
                            radius: height / 2

                            Rectangle {
                                width: modelData ? parent.width * (modelData.usagePercent / 100.0) : 0
                                height: parent.height
                                color: ThemeManager.primaryColor
                                radius: parent.radius
                            }
                        }
                    }
                }
            }
        }
    }
}
