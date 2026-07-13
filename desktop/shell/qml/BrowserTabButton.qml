import QtQuick

/**
 * @brief BDL-styled button for a single browser tab.
 */
Rectangle {
    id: root

    property var tab: null
    property bool active: false

    signal tabSelected()
    signal tabClosed()
    signal tabMoved(int newIndex)

    width: 160
    height: parent ? parent.height : 32
    radius: DesignTokens.radiusSmall
    color: root.active
           ? (ThemeManager.surfaceSecondaryColor)
           : (ThemeManager.surfaceColor)
    border.color: ThemeManager.borderColor
    border.width: 1

    MouseArea {
        id: dragArea

        anchors.fill: parent
        drag.target: root
        drag.axis: Drag.XAxis
        onClicked: root.tabSelected()
        onReleased: {
            if (root.parent) {
                const centerX = root.x + root.width / 2;
                const newIndex = Math.floor(centerX / root.width);
                root.tabMoved(Math.max(0, Math.min(newIndex, root.parent.children.length - 1)));
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space4

        Text {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - closeButton.width - parent.spacing
            text: root.tab ? (root.tab.title || "New Tab") : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Rectangle {
            id: closeButton

            anchors.verticalCenter: parent.verticalCenter
            width: 16
            height: 16
            radius: 4
            color: closeArea.containsMouse
                   ? (ThemeManager.surfaceSecondaryColor)
                   : "transparent"

            Text {
                anchors.centerIn: parent
                text: "x"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }

            MouseArea {
                id: closeArea

                anchors.fill: parent
                hoverEnabled: true
                onClicked: root.tabClosed()
            }
        }
    }
}
