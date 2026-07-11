import QtQuick

/**
 * @brief Renders all desktop icons from the DesktopManager model.
 *
 * Icons are positioned using the coordinates stored in the model. They are
 * rendered as children of this item, which is placed between the wallpaper
 * layer and the window layer so they remain on the desktop surface.
 */
Item {
    id: root

    anchors.fill: parent

    Repeater {
        id: iconRepeater

        model: desktopManager ? desktopManager.model : null

        delegate: DesktopIcon {
            itemId: model.itemId
            displayName: model.name
            iconName: model.icon
            itemType: model.type
            selected: model.selected
            visible: model.visible
            x: model.positionX
            y: model.positionY
        }
    }
}
