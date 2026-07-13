import QtQuick

/**
 * @brief Notes status bar showing character count, word count, and last saved time.
 */
Rectangle {
    id: root

    property var notesManager: null

    height: 24
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space16

        Text {
            text: root.notesManager
                  ? root.notesManager.noteCount + " notes"
                  : "0 notes"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.notesManager
                  ? root.notesManager.characterCount() + " characters"
                  : "0 characters"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.notesManager
                  ? root.notesManager.wordCount() + " words"
                  : "0 words"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            text: root.notesManager && root.notesManager.activeNoteUpdatedAt.length > 0
                  ? "Last saved " + root.notesManager.activeNoteUpdatedAt
                  : ""
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
