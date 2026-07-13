import QtQuick

/**
 * @brief A single note entry in the Notes sidebar.
 */
Rectangle {
    id: root

    property string noteTitle: ""
    property bool selected: false

    signal clicked()

    height: 36
    width: parent ? parent.width : 200
    color: root.selected
           ? (ThemeManager.highlightColor)
           : "transparent"
    radius: DesignTokens.radiusSmall

    Text {
        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        verticalAlignment: Text.AlignVCenter
        text: root.noteTitle
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        elide: Text.ElideRight
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
