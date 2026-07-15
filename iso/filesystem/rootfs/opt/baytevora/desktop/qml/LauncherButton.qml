import QtQuick
import BOS.Shell

/**
 * @brief A flat, reusable button for an entry in the launcher grid.
 *
 * LauncherButton displays a simple placeholder icon and an application name.
 * It has no motion effects, hover styling, gradients, or shadows.
 */
Rectangle {
    id: root

    property string iconName: ""
    property url iconSource: ""
    property string appName: ""

    signal clicked()

    color: "transparent"
    width: 88
    height: 88

    Column {
        anchors.centerIn: parent
        spacing: SpacingManager.space8

        // Official application symbol or fallback initials.
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: 40
            height: 40
            color: root.iconSource.toString().length > 0 ? "transparent" : ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusSmall

            Image {
                anchors.fill: parent
                source: root.iconSource
                fillMode: Image.PreserveAspectFit
                sourceSize.width: 80
                sourceSize.height: 80
                visible: root.iconSource.toString().length > 0
            }

            Text {
                anchors.centerIn: parent
                text: root.appName.substring(0, 2).toUpperCase()
                color: ThemeManager.textSecondary
                font.pixelSize: 16
                visible: root.iconSource.toString().length === 0
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.appName
            color: ThemeManager.textSecondary
            font.pixelSize: 12
            elide: Text.ElideRight
        }
    }

    MouseArea {
        id: launcherMouseArea

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
                    dragManager.beginDrag(DragType.Application,
                                          "launcher-" + root.appName,
                                          root.appName);
                }
            }
            if (dragHappened && dragManager) {
                const globalPos = root.mapToGlobal(mouse.x, mouse.y);
                dragManager.updatePosition(globalPos.x, globalPos.y);
            }
        }
        onReleased: {
            if (dragHappened && dragManager && dragManager.active) {
                console.log("[BDE] Launcher drag dropped (ignored)");
                dragManager.cancelDrag();
            }
        }
        onClicked: {
            if (!dragHappened) {
                root.clicked();
            }
        }
    }
}
