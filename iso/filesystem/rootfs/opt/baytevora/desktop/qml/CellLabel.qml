import QtQuick

/**
 * @brief Cell text label used by the File Manager list view.
 */
Text {
    height: parent.height
    verticalAlignment: Text.AlignVCenter
    color: "ThemeManager.textSecondary"
    font.pixelSize: 13
    elide: Text.ElideRight
}
