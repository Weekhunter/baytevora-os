import QtQuick
import QtQuick.Dialogs

/**
 * @brief Media Player toolbar with Open, Play, Pause, Stop, and Mute actions.
 */
Rectangle {
    id: root

    property var mediaManager: null
    property alias openDialog: openDialog

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    FileDialog {
        id: openDialog

        title: "Open Media"
        nameFilters: ["Media files (*.mp4 *.webm *.mp3 *.wav *.ogg)"]
        onAccepted: {
            if (root.mediaManager) {
                root.mediaManager.openMedia(selectedFile.toString());
            }
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        MediaToolButton {
            label: "Open"
            onClicked: openDialog.open()
        }

        MediaToolButton {
            label: "Play"
            onClicked: {
                if (root.mediaManager) {
                    root.mediaManager.play();
                }
            }
        }

        MediaToolButton {
            label: "Pause"
            onClicked: {
                if (root.mediaManager) {
                    root.mediaManager.pause();
                }
            }
        }

        MediaToolButton {
            label: "Stop"
            onClicked: {
                if (root.mediaManager) {
                    root.mediaManager.stop();
                }
            }
        }

        MediaToolButton {
            label: "Mute"
            onClicked: {
                if (root.mediaManager) {
                    root.mediaManager.toggleMute();
                }
            }
        }
    }
}
