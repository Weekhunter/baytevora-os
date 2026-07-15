import QtQuick

/**
 * @brief Status bar for the Calculator application.
 *
 * CalculatorStatusBar provides a subtle footer label that identifies the
 * application and confirms the standard calculator mode.
 */
Rectangle {
    id: root

    color: ThemeManager.backgroundColor

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: SpacingManager.space12
        text: "Standard Calculator"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
    }
}
