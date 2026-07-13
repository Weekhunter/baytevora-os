import QtQuick
import BOS.Shell

/**
 * @brief Reusable drop target with hover state and accept/reject callbacks.
 *
 * DropTarget uses design tokens for colors and visual feedback. While a drag is
 * active the target tracks whether the cursor is inside its bounds and reports
 * itself to DragManager as the current target.
 */
Rectangle {
    id: root

    property string targetId: ""
    property var acceptedTypes: []

    signal dragEntered()
    signal dragExited()
    signal dragDropped()

    default property alias content: contentArea.children

    color: dragManager && dragManager.currentTarget === root.targetId && root.isAccepted
           ? (ThemeManager.primaryColor)
           : "transparent"
    border.color: dragManager && dragManager.currentTarget === root.targetId && root.isAccepted
                  ? (ThemeManager.accentColor)
                  : (ThemeManager.borderColor)
    border.width: dragManager && dragManager.currentTarget === root.targetId && root.isAccepted ? 2 : 0

    property bool isHovered: false
    property bool isAccepted: acceptedTypes.length === 0
                              || acceptedTypes.indexOf(dragManager ? dragManager.currentDragType : -1) !== -1

    Rectangle {
        id: contentArea

        anchors.fill: parent
        anchors.margins: SpacingManager.space2
        color: "transparent"
    }

    MouseArea {
        id: hoverArea

        anchors.fill: parent
        hoverEnabled: true
        enabled: dragManager ? dragManager.active : false
        propagateComposedEvents: true

        onEntered: {
            root.isHovered = true;
            if (dragManager && root.isAccepted) {
                dragManager.setTarget(root.targetId);
            }
            root.dragEntered();
        }

        onExited: {
            root.isHovered = false;
            if (dragManager && dragManager.currentTarget === root.targetId) {
                dragManager.clearTarget();
            }
            root.dragExited();
        }

        onReleased: {
            if (dragManager && dragManager.active && root.isHovered && root.isAccepted) {
                dragManager.completeDrop(root.targetId);
                root.dragDropped();
            }
        }
    }
}
