import QtQuick
import BOS.Shell

/**
 * @brief A single desktop icon.
 *
 * Displays a placeholder icon and the item name. Single click selects the
 * item; double click activates it and logs the activation. Visual state uses
 * BDL tokens for colors, typography, and spacing.
 */
Rectangle {
    id: root

    property int itemId: 0
    property string displayName: ""
    property string iconName: ""
    property url iconSource: ""
    property string itemType: ""
    property bool selected: false

    width: 64
    height: 80
    color: root.selected
        ? (ThemeManager.primaryColor)
        : "transparent"
    radius: DesignTokens.radiusMedium
    opacity: ThemeManager ? 1.0 : 1.0

    Column {
        anchors.fill: parent
        anchors.margins: SpacingManager.space4
        spacing: SpacingManager.space4

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: IconManager.large
            height: width
            color: root.iconSource.toString().length > 0 ? "transparent" : ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusSmall

            Image {
                anchors.fill: parent
                anchors.margins: 4
                source: root.iconSource
                fillMode: Image.PreserveAspectFit
                sourceSize.width: IconManager.large * 2
                sourceSize.height: IconManager.large * 2
                visible: root.iconSource.toString().length > 0
            }

            Text {
                anchors.centerIn: parent
                text: root.displayName.length > 0 ? root.displayName.charAt(0).toUpperCase() : "?"
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.title
                font.family: TypographyManager.fontFamily
                font.weight: Font.Bold
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                visible: root.iconSource.toString().length === 0
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            text: root.displayName
            color: root.selected
                ? (ThemeManager.textPrimary)
                : (ThemeManager.textPrimary)
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            elide: Text.ElideRight
            maximumLineCount: 2
        }
    }

    Timer {
        id: singleClickTimer

        interval: 200
        onTriggered: {
            if (desktopManager) {
                desktopManager.selectItem(root.itemId);
            }
        }
    }

    MouseArea {
        id: iconMouseArea

        property point pressPos: Qt.point(0, 0)
        property bool dragHappened: false

        anchors.fill: parent
        onPressed: {
            pressPos = Qt.point(mouse.x, mouse.y);
            dragHappened = false;
        }
        onPositionChanged: {
            const dx = mouse.x - pressPos.x;
            const dy = mouse.y - pressPos.y;
            if (!dragHappened && Math.sqrt(dx * dx + dy * dy) > 8) {
                dragHappened = true;
                if (dragManager) {
                    dragManager.beginDrag(DragType.DesktopItem,
                                          "desktop-" + root.itemId,
                                          root.displayName);
                }
            }
            if (dragHappened && dragManager) {
                const globalPos = root.mapToGlobal(mouse.x, mouse.y);
                dragManager.updatePosition(globalPos.x, globalPos.y);
            }
        }
        onReleased: {
            if (dragHappened && dragManager && dragManager.active) {
                dragManager.completeDrop(dragManager.currentTarget);
            }
        }
        onClicked: {
            if (!dragHappened) {
                singleClickTimer.start();
            }
        }
        onDoubleClicked: {
            singleClickTimer.stop();
            if (desktopManager) {
                desktopManager.activateItem(root.itemId);
            }
        }
    }
}
