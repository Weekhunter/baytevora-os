import QtQuick

/**
 * @brief Empty-state placeholder shown when no image is loaded.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    Text {
        anchors.centerIn: parent
        text: "Open an image to begin."
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
