import QtQuick

/**
 * @brief A minimal digital clock for the taskbar.
 *
 * Clock displays the current time in HH:MM format and updates every minute
 * using a Qt Quick Timer. It does not show the date, time zones, or calendar.
 */
Rectangle {
    id: root

    color: "transparent"
    width: 60
    height: parent ? parent.height : 40

    property string timeText: ""

    Text {
        anchors.centerIn: parent
        text: root.timeText
        color: "ThemeManager.textSecondary"
        font.pixelSize: 14
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: root.timeText = Qt.formatTime(new Date(), "hh:mm")
    }
}
