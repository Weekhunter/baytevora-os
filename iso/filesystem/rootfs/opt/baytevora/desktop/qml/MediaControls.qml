import QtQuick
import QtQuick.Controls as QQC

/**
 * @brief Bottom media controls with playback, seek, and volume sliders.
 */
Rectangle {
    id: root

    property var mediaManager: null

    height: 64
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    function formatTime(ms) {
        if (!ms || ms < 0) {
            return "0:00";
        }
        const totalSeconds = Math.floor(ms / 1000);
        const minutes = Math.floor(totalSeconds / 60);
        const seconds = totalSeconds % 60;
        return minutes + ":" + (seconds < 10 ? "0" + seconds : seconds);
    }

    Row {
        id: controlsRow

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        spacing: SpacingManager.space12

        MediaToolButton {
            id: previousButton

            label: "Previous"
            onClicked: {
                // Placeholder for future playlist support.
            }
        }

        MediaToolButton {
            id: playButton

            label: root.mediaManager && root.mediaManager.document && root.mediaManager.document.playing ? "Pause" : "Play"
            onClicked: {
                if (root.mediaManager) {
                    root.mediaManager.togglePlayPause();
                }
            }
        }

        MediaToolButton {
            id: nextButton

            label: "Next"
            onClicked: {
                // Placeholder for future playlist support.
            }
        }

        Rectangle {
            id: timeBox

            width: 140
            height: parent.height
            color: "transparent"

            Text {
                anchors.centerIn: parent
                text: root.mediaManager
                      ? formatTime(root.mediaManager.document.currentPosition) + " / " + formatTime(root.mediaManager.document.duration)
                      : "0:00 / 0:00"
                color: ThemeManager.textSecondary
                font.pixelSize: TypographyManager.caption
                font.family: TypographyManager.fontFamily
            }
        }

        Rectangle {
            height: parent.height
            width: parent.width - previousButton.width - playButton.width - nextButton.width - timeBox.width - volumeBox.width - (parent.spacing * 6)
            color: "transparent"

            QQC.Slider {
                id: seekSlider

                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                enabled: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                from: 0
                to: root.mediaManager && root.mediaManager.document ? root.mediaManager.document.duration : 0
                value: root.mediaManager && root.mediaManager.document ? root.mediaManager.document.currentPosition : 0

                onMoved: {
                    if (root.mediaManager) {
                        root.mediaManager.seek(seekSlider.value);
                    }
                }
            }
        }

        Rectangle {
            id: volumeBox

            width: 120
            height: parent.height
            color: "transparent"

            QQC.Slider {
                id: volumeSlider

                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                enabled: root.mediaManager !== null
                from: 0
                to: 1
                value: root.mediaManager && root.mediaManager.document ? root.mediaManager.document.volume : 1.0
                stepSize: 0.05

                onMoved: {
                    if (root.mediaManager) {
                        root.mediaManager.setVolume(volumeSlider.value);
                    }
                }
            }
        }
    }
}
