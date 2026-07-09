import QtQuick

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

    /**
     * Wallpaper layer. The source is provided by the C++ Application class via
     * a context property so the application can resolve the file path relative
     * to the executable.
     */
    Wallpaper {
        id: desktopWallpaper

        anchors.fill: parent
        source: wallpaperSource
        fallbackColor: "#0f172a"
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
            visible: modelData.visible
            isActive: modelData.id === windowManager.activeWindowId
        }
    }
}
