import QtQuick

/**
 * @brief Main view of the native Media Player application.
 *
 * MediaPlayerWindow fills the content area of a WindowFrame and arranges the
 * toolbar, playlist sidebar, media canvas, bottom controls, and status bar.
 * Each Media Player window owns its own MediaPlayerManager so playback state
 * stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    MediaPlayerManager {
        id: mediaManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                mediaManager.setNotificationManager(notificationManager);
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        MediaToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            mediaManager: mediaManager
        }

        Row {
            width: parent.width
            height: parent.height - toolbar.height - mediaControls.height - statusBar.height

            PlaylistSidebar {
                id: playlistSidebar

                height: parent.height
                mediaManager: mediaManager
            }

            MediaCanvas {
                id: mediaCanvas

                width: parent.width - playlistSidebar.width
                height: parent.height
                mediaManager: mediaManager
            }
        }

        MediaControls {
            id: mediaControls

            width: parent.width
            height: 64
            mediaManager: mediaManager
        }

        MediaStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            mediaManager: mediaManager
        }
    }

    // Keyboard shortcuts.
    Shortcut {
        sequences: ["Ctrl+O"]
        onActivated: toolbar.openDialog.open()
    }

    Shortcut {
        sequences: ["Space"]
        onActivated: mediaManager.togglePlayPause()
    }

    Shortcut {
        sequences: ["Left"]
        onActivated: {
            if (mediaManager && mediaManager.document) {
                mediaManager.seek(mediaManager.document.currentPosition - 5000);
            }
        }
    }

    Shortcut {
        sequences: ["Right"]
        onActivated: {
            if (mediaManager && mediaManager.document) {
                mediaManager.seek(mediaManager.document.currentPosition + 5000);
            }
        }
    }

    Shortcut {
        sequences: ["Up"]
        onActivated: {
            if (mediaManager && mediaManager.document) {
                mediaManager.setVolume(mediaManager.document.volume + 0.1);
            }
        }
    }

    Shortcut {
        sequences: ["Down"]
        onActivated: {
            if (mediaManager && mediaManager.document) {
                mediaManager.setVolume(mediaManager.document.volume - 0.1);
            }
        }
    }

    Shortcut {
        sequences: ["M"]
        onActivated: mediaManager.toggleMute()
    }

    Shortcut {
        sequences: ["Escape"]
        onActivated: mediaManager.stop()
    }
}
