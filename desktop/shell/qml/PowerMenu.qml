import QtQuick
import BOS.Shell

/**
 * @brief Popup menu for power actions.
 *
 * PowerMenu binds to powerManager.actions and renders one PowerMenuItem per
 * action. Clicking outside the menu or pressing Escape closes it. Selecting an
 * item invokes powerManager.executeAction(type).
 */
Rectangle {
    id: root

    property bool menuOpen: false

    signal menuClosed()

    width: 200
    height: column.height + 16
    visible: menuOpen
    focus: menuOpen
    color: ThemeManager.launcherBackground
    border.color: ThemeManager.borderColor
    border.width: 1
    radius: DesignTokens.radiusMedium

    Keys.onEscapePressed: {
        root.menuOpen = false;
        root.menuClosed();
    }

    Column {
        id: column

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: SpacingManager.space8
        anchors.bottomMargin: SpacingManager.space8
        spacing: SpacingManager.space4

        Repeater {
            model: powerManager ? powerManager.actions : []

            PowerMenuItem {
                width: column.width
                itemTitle: modelData.title
                itemDescription: modelData.description
                itemIcon: BrandingManager.iconUrl(modelData.iconName)
                itemEnabled: modelData.enabled

                onActivated: {
                    if (powerManager) {
                        powerManager.executeAction(modelData.type);
                    }
                    root.menuOpen = false;
                    root.menuClosed();
                }
            }
        }

        // Sprint 23: lock action. It is rendered alongside the power actions
        // and delegates to the LockManager.
        PowerMenuItem {
            width: column.width
            itemTitle: "Lock"
            itemDescription: "Lock this session"
            itemIcon: BrandingManager.iconUrl("lock")
            itemEnabled: lockManager ? !lockManager.isLocked : false

            onActivated: {
                if (lockManager) {
                    lockManager.lock();
                }
                root.menuOpen = false;
                root.menuClosed();
            }
        }
    }
}
