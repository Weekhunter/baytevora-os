import QtQuick

/**
 * @brief A minimal window frame for the BDE Window Manager framework.
 *
 * WindowFrame renders a simple title bar, background, and border. It is
 * intentionally static in Sprint 5 and avoids any interactive controls or
 * decorative effects.
 */
Rectangle {
    id: root

    /** Window title shown in the title bar. */
    property string title: ""

    /** Whether this window is the active window. */
    property bool isActive: false

    color: "#1e293b"
    border.color: isActive ? "#475569" : "#334155"
    border.width: isActive ? 2 : 1
    z: isActive ? 1 : 0

    MouseArea {
        anchors.fill: parent
        onClicked: {
            // Delegate focus handling to the WindowManager. The window ID is
            // provided by the surrounding Repeater delegate via modelData.id.
            if (windowManager) {
                windowManager.setActiveWindow(modelData.id)
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Title bar
        Rectangle {
            id: titleBar

            width: parent.width
            height: 32
            color: isActive ? "#1e293b" : "#0f172a"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 12
                text: root.title
                color: "#e2e8f0"
                font.pixelSize: 14
            }
        }

        // Content area placeholder
        Rectangle {
            width: parent.width
            height: parent.height - titleBar.height
            color: root.color
        }
    }
}
