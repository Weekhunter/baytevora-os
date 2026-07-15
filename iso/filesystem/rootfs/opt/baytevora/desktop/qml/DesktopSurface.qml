import QtQuick
import BOS.Shell

/**
 * @brief The desktop surface container.
 *
 * This item fills the root window and holds the wallpaper layer and the
 * window layer. Future sprints can extend it to include desktop components or
 * widgets without modifying the root Window or wallpaper logic.
 */
Item {
    id: root

    anchors.fill: parent

    property int __deleteShortcutId: -1

    Component.onCompleted: {
        if (shortcutManager) {
            __deleteShortcutId = shortcutManager.registerShortcut("Desktop Delete", "Delete",
                                                                   ShortcutContext.Global,
                                                                   "Request desktop delete action");
        }
    }

    Component.onDestruction: {
        if (shortcutManager && __deleteShortcutId !== -1) {
            shortcutManager.removeShortcut(__deleteShortcutId);
        }
    }

    Connections {
        target: shortcutManager
        function onShortcutActivated(id) {
            if (id === __deleteShortcutId) {
                console.log("[BDE] Desktop delete requested");
            }
        }
    }

    /**
     * Wallpaper layer. The source is provided by the C++ Application class via
     * a context property so the application can resolve the file path relative
     * to the executable.
     */
    Wallpaper {
        id: desktopWallpaper

        anchors.fill: parent
        source: wallpaperSource
        fallbackColor: "ThemeManager.backgroundColor"
    }

    /**
     * Desktop icon layer. Renders all icons managed by the DesktopManager.
     * This layer sits above the wallpaper but below managed windows.
     */
    DesktopIcons {
        id: desktopIcons

        anchors.fill: parent
    }

    /**
     * Window layer. Renders one WindowFrame for every window registered with
     * the WindowManager. The windowManager context property is set by the
     * Application class before Desktop.qml is loaded.
     */
    Repeater {
        model: windowManager ? windowManager.windows : []

        delegate: WindowFrame {
            x: modelData.x
            y: modelData.y
            width: modelData.width
            height: modelData.height
            title: modelData.title
            applicationName: modelData.applicationName
            visible: modelData.visible && modelData.state !== "minimized"
            isActive: modelData.id === windowManager.activeWindowId
            state: modelData.state
        }
    }
}
