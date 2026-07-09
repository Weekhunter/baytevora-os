import QtQuick

/**
 * @brief Reusable wallpaper component.
 *
 * Displays an image scaled to fill the parent while preserving its aspect ratio.
 * If the image cannot be loaded, a solid fallback color is shown instead and a
 * warning is logged. The component is intentionally simple so it can later be
 * extended to support multiple wallpapers, slideshows, or dynamic wallpapers.
 */
Item {
    id: root

    /** URL of the wallpaper image to display. */
    property url source

    /** Background color used when the wallpaper image cannot be loaded. */
    property color fallbackColor: "#0f172a"

    /**
     * The actual image item. fillMode is set to PreserveAspectCrop so the image
     * fills the screen without distortion, cropping edges when the aspect ratio
     * does not match the screen.
     */
    Image {
        id: wallpaperImage

        anchors.fill: parent
        source: root.source
        fillMode: Image.PreserveAspectCrop
        smooth: true
        asynchronous: true
        visible: status === Image.Ready
    }

    /**
     * Fallback rectangle shown when the image is missing, still loading, or
     * failed to load. It uses the configured fallbackColor.
     */
    Rectangle {
        anchors.fill: parent
        color: root.fallbackColor
        visible: !wallpaperImage.visible
    }

    /**
     * Watch the image status and log a warning when loading fails. This keeps
     * the error handling explicit without breaking the desktop surface.
     */
    Connections {
        target: wallpaperImage

        function onStatusChanged() {
            if (wallpaperImage.status === Image.Error) {
                console.warn("Wallpaper: failed to load image from " + root.source);
            }
        }
    }
}
