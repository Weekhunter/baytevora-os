import QtQuick
import BOS.Shell

/**
 * @brief Displays one button per non-closed window managed by WindowManager.
 *
 * RunningApps binds to windowManager.windows and activeWindowId so the list
 * updates automatically when windows are created, closed, minimized,
 * restored, or renamed. Clicking a button delegates to
 * WindowManager.taskbarButtonClicked() so all interaction logic stays in C++.
 */
Row {
    id: root

    spacing: 4
    height: parent ? parent.height : 40

    Repeater {
        model: windowManager ? windowManager.windows : []

        delegate: TaskbarButton {
            text: modelData.title
            iconSource: BrandingManager.applicationSymbolUrl(modelData.applicationName)
            active: modelData.id === windowManager.activeWindowId
            height: root.height
            onClicked: {
                if (windowManager) {
                    windowManager.taskbarButtonClicked(modelData.id)
                }
            }
        }
    }
}
