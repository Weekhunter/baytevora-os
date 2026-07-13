import QtQuick

/**
 * @brief Delegate for a single archive entry in the file list.
 */
Rectangle {
    id: root

    property var entry: null
    property bool selected: false
    property var archiveManager: null

    signal activated()

    height: 36
    width: ListView.view ? ListView.view.width : 400
    color: root.selected
           ? (ThemeManager.primaryColor)
           : (mouseArea.containsMouse
              ? (ThemeManager.surfaceSecondaryColor)
              : (ThemeManager.surfaceColor))

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            if (root.archiveManager) {
                root.archiveManager.toggleSelection(index);
            }
            root.activated();
        }
    }

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space12

        Text {
            width: parent.width * 0.45
            anchors.verticalCenter: parent.verticalCenter
            text: root.entry ? root.entry.name : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.entry ? root.entry.size + " B" : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.18
            anchors.verticalCenter: parent.verticalCenter
            text: root.entry ? root.entry.compressedSize + " B" : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            width: parent.width * 0.15
            anchors.verticalCenter: parent.verticalCenter
            text: root.entry ? root.entry.modifiedDate : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }
    }
}
