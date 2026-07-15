import QtQuick

/**
 * @brief Status bar for the Text Editor.
 */
Rectangle {
    id: root

    property var editorManager: null

    height: AdaptiveLayoutManager.titleBarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.leftMargin: SpacingManager.space12
        anchors.rightMargin: SpacingManager.space12
        spacing: SpacingManager.space16

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.editorManager && root.editorManager.document && root.editorManager.document.loaded
                  ? root.editorManager.document.fileName + (root.editorManager.document.modified ? " *" : "")
                  : "Untitled"
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
            elide: Text.ElideRight
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.editorManager
                  ? "Lines: " + root.editorManager.document.lineCount
                  : "Lines: 1"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.editorManager
                  ? "Characters: " + root.editorManager.document.characterCount
                  : "Characters: 0"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: root.editorManager
                  ? "Ln " + root.editorManager.cursorLine + ", Col " + root.editorManager.cursorColumn
                  : "Ln 1, Col 1"
            color: ThemeManager.textSecondary
            font.pixelSize: TypographyManager.caption
            font.family: TypographyManager.fontFamily
        }
    }
}
