import QtQuick
import BOS.Shell

/**
 * @brief Custom toggle switch for wizard settings.
 */
Row {
    id: root

    property string label: ""
    property bool checked: false

    signal toggled()

    spacing: 12

    Rectangle {
        id: track

        width: 44
        height: 24
        radius: 12
        color: root.checked ? ThemeManager.highlightColor : ThemeManager.surfaceSecondaryColor
        border.color: ThemeManager.borderColor
        border.width: 1

        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            x: root.checked ? parent.width - width - 3 : 3
            width: 18
            height: 18
            radius: 9
            color: ThemeManager.textPrimary
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.checked = !root.checked;
                root.toggled();
            }
        }
    }

    Text {
        anchors.verticalCenter: track.verticalCenter
        text: root.label
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
    }
}
