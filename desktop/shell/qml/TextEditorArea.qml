import QtQuick
import QtQuick.Controls as QQC

/**
 * @brief Plain-text editing area for the Text Editor.
 */
Rectangle {
    id: root

    property var editorManager: null
    property bool wrapLines: true

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    function updateCursorInfo() {
        if (!textArea.activeFocus || !root.editorManager) {
            return;
        }
        const text = textArea.text;
        const pos = textArea.cursorPosition;
        const before = text.substring(0, pos);
        const line = before.split('\n').length;
        const column = before.length - before.lastIndexOf('\n');
        root.editorManager.setCursorInfo(line, column);
    }

    QQC.TextArea {
        id: textArea

        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        text: root.editorManager ? root.editorManager.content : ""
        color: ThemeManager.textPrimary
        font.pixelSize: TypographyManager.body
        font.family: TypographyManager.fontFamily
        wrapMode: root.wrapLines ? Text.Wrap : Text.NoWrap
        selectByMouse: true
        selectByKeyboard: true

        background: Rectangle {
            color: "transparent"
        }

        onTextChanged: {
            if (root.editorManager) {
                root.editorManager.setContent(text);
            }
            updateCursorInfo();
        }

        onCursorPositionChanged: updateCursorInfo()

        Connections {
            target: root.editorManager
            function onUndoRequested() { textArea.undo(); }
            function onRedoRequested() { textArea.redo(); }
            function onCutRequested() { textArea.cut(); }
            function onCopyRequested() { textArea.copy(); }
            function onPasteRequested() { textArea.paste(); }
            function onSelectAllRequested() { textArea.selectAll(); }
            function onContentChanged() {
                if (textArea.text !== root.editorManager.content) {
                    textArea.text = root.editorManager.content;
                }
            }
        }
    }
}
