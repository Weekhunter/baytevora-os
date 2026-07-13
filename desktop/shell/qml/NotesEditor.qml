import QtQuick
import QtQuick.Controls

/**
 * @brief Notes editor containing an editable title and plain-text content.
 */
Rectangle {
    id: root

    property var notesManager: null
    property bool __updatingFromManager: false

    color: ThemeManager.backgroundColor
    border.color: ThemeManager.borderColor
    border.width: 1

    function __syncFromManager() {
        if (!root.notesManager) {
            return;
        }
        root.__updatingFromManager = true;
        titleInput.text = root.notesManager.activeNoteTitle;
        contentArea.text = root.notesManager.activeNoteContent;
        root.__updatingFromManager = false;
    }

    Column {
        anchors.fill: parent
        spacing: 0

        // Editable title
        Rectangle {
            width: parent.width
            height: 44
            color: ThemeManager.surfaceColor

            TextInput {
                id: titleInput

                anchors.fill: parent
                anchors.margins: SpacingManager.space12
                verticalAlignment: TextInput.AlignVCenter
                text: root.notesManager ? root.notesManager.activeNoteTitle : ""
                color: ThemeManager.textPrimary
                font.pixelSize: TypographyManager.subheading
                font.family: TypographyManager.fontFamily
                font.weight: Font.DemiBold
                selectByMouse: true
                clip: true

                onTextChanged: {
                    if (!root.__updatingFromManager && root.notesManager) {
                        root.notesManager.setActiveNoteTitle(titleInput.text);
                    }
                }
            }
        }

        // Plain text content editor
        TextArea {
            id: contentArea

            width: parent.width
            height: parent.height - 44
            text: root.notesManager ? root.notesManager.activeNoteContent : ""
            color: ThemeManager.textPrimary
            font.pixelSize: TypographyManager.body
            font.family: TypographyManager.fontFamily
            background: Rectangle {
                color: "transparent"
            }
            wrapMode: TextArea.Wrap
            selectByMouse: true

            onTextChanged: {
                if (!root.__updatingFromManager && root.notesManager) {
                    root.notesManager.setActiveNoteContent(contentArea.text);
                }
            }
        }
    }

    Connections {
        target: root.notesManager
        enabled: root.notesManager !== null

        function onActiveNoteChanged() {
            root.__syncFromManager();
        }
    }
}
