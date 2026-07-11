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
    color: ThemeManager ? ThemeManager.launcherBackground : "#1e293b"
    border.color: ThemeManager ? ThemeManager.borderColor : "#475569"
    border.width: 1
    radius: DesignTokens ? DesignTokens.radiusMedium : 8

    Keys.onEscapePressed: {
        root.menuOpen = false;
        root.menuClosed();
    }

    Column {
        id: column

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 8
        anchors.bottomMargin: 8
        spacing: 4

        Repeater {
            model: powerManager ? powerManager.actions : []

            PowerMenuItem {
                width: column.width
                itemTitle: modelData.title
                itemDescription: modelData.description
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
    }
}
