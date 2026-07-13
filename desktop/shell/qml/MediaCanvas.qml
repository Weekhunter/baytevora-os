import QtQuick
import QtMultimedia as QMM

/**
 * @brief Media playback canvas for the Media Player.
 *
 * MediaCanvas displays the video surface when a video is loaded, shows an
 * album-artwork placeholder for audio, and a friendly empty-state placeholder
 * when no media is loaded.
 */
Rectangle {
    id: root

    property var mediaManager: null

    color: ThemeManager.backgroundColor

    QMM.VideoOutput {
        id: videoOutput

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        source: root.mediaManager ? root.mediaManager.player : null
        visible: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                 && root.mediaManager.document.mediaType === "Video"
    }

    Rectangle {
        id: audioPlaceholder

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        color: ThemeManager.surfaceColor
        radius: DesignTokens.radiusMedium
        visible: root.mediaManager && root.mediaManager.document && root.mediaManager.document.loaded
                 && root.mediaManager.document.mediaType === "Audio"

        Text {
            anchors.centerIn: parent
            text: "Audio"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.subheading
            font.family: TypographyManager.fontFamily
            font.weight: Font.DemiBold
        }
    }

    Rectangle {
        id: emptyPlaceholder

        anchors.fill: parent
        anchors.margins: SpacingManager.space12
        color: ThemeManager.surfaceColor
        radius: DesignTokens.radiusMedium
        visible: !root.mediaManager || !root.mediaManager.document || !root.mediaManager.document.loaded

        Text {
            anchors.centerIn: parent
            text: "Open a media file to begin playback"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
        }
    }
}
