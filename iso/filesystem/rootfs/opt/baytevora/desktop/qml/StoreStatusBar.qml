import QtQuick

/**
 * @brief Status bar for the Baytevora Store Phase 2.
 */
Rectangle {
    id: root

    property int applicationCount: 0
    property string statusText: ""

    width: parent ? parent.width : 600
    height: 24
    color: ThemeManager.surfaceColor

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: SpacingManager.space12
        text: root.statusText.length > 0 ? root.statusText : root.applicationCount + " applications"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
    }
}
