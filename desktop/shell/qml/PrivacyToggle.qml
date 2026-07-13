import QtQuick

/**
 * @brief Simple toggle switch used by the browser privacy settings page.
 */
Rectangle {
    id: root

    property string label: ""
    property bool checked: false

    signal toggled(bool checked)

    height: 40
    width: parent ? parent.width : 400
    color: ThemeManager.surfaceColor
    radius: DesignTokens.radiusSmall

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space12

        Text {
            width: parent.width - switchArea.width - parent.spacing
            text: root.label
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            anchors.verticalCenter: parent.verticalCenter
            elide: Text.ElideRight
        }

        Rectangle {
            id: switchArea

            width: 48
            height: 24
            radius: height / 2
            color: root.checked
                ? (ThemeManager.accentColor)
                : (ThemeManager.borderColor)
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                x: root.checked ? parent.width - width - 2 : 2
                y: 2
                width: parent.height - 4
                height: parent.height - 4
                radius: width / 2
                color: ThemeManager.textPrimary
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.checked = !root.checked;
                    root.toggled(root.checked);
                }
            }
        }
    }
}
