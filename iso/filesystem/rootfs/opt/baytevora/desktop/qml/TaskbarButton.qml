import QtQuick

/**
 * @brief A flat, reusable button for the taskbar.
 *
 * TaskbarButton displays simple text, emits clicked(), and highlights when
 * active. It has no motion effects, hover styling, gradients, or shadows.
 */
Rectangle {
    id: root

    property string text: ""
    property url iconSource: ""
    property bool active: false

    signal clicked()

    color: active ? ThemeManager.surfaceSecondaryColor : "transparent"
    implicitWidth: row.implicitWidth + 24
    height: parent ? parent.height : 40

    Row {
        id: row

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 6

        Image {
            width: root.iconSource.toString().length > 0 ? 18 : 0
            height: 18
            source: root.iconSource
            fillMode: Image.PreserveAspectFit
            sourceSize.width: 36
            sourceSize.height: 36
            visible: root.iconSource.toString().length > 0
        }

        Text {
            id: label

            text: root.text
            color: ThemeManager.textSecondary
            font.pixelSize: 13
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
