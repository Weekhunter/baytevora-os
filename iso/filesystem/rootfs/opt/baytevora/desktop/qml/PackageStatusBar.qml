import QtQuick

/**
 * @brief Status bar for the Baytevora Package Manager Phase 2.
 */
Rectangle {
    id: root

    property int packageCount: 0
    property int installedCount: 0
    property int availableCount: 0
    property string statusText: ""

    width: parent ? parent.width : 600
    height: 24
    color: ThemeManager.surfaceColor

    Text {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: SpacingManager.space12
        text: root.statusText.length > 0
              ? root.statusText
              : root.installedCount + " installed / " + root.availableCount + " available / " + root.packageCount + " total"
        color: ThemeManager.textSecondary
        font.pixelSize: TypographyManager.caption
        font.family: TypographyManager.fontFamily
    }
}
