import QtQuick

/**
 * @brief Global drag feedback overlay.
 *
 * DragOverlay follows the current drag position while a drag is active. It
 * shows a DragIndicator with the dragged item name and a placeholder icon.
 * No animations or transparency effects are used.
 */
Rectangle {
    id: root

    visible: dragManager ? dragManager.active : false
    color: "transparent"
    width: dragIndicator.width
    height: dragIndicator.height
    x: dragManager ? dragManager.currentPosition.x - dragIndicator.width / 2 : 0
    y: dragManager ? dragManager.currentPosition.y - dragIndicator.height / 2 : 0
    z: 250

    DragIndicator {
        id: dragIndicator

        draggedName: dragManager && dragManager.currentOperation
                     ? dragManager.currentOperation.data.value
                     : ""
        draggedIcon: dragManager && dragManager.currentOperation
                     ? dragManager.currentOperation.data.typeName
                     : ""
    }
}
