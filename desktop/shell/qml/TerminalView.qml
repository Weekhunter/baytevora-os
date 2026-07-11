import QtQuick
import QtQuick.Controls
import BOS.Shell

/**
 * @brief Terminal output and command input view.
 *
 * Displays the buffered output from TerminalManager and provides a prompt-line
 * TextField for typing commands. Pressing Enter sends the typed command to
 * TerminalManager::executeCommand() and clears the input.
 */
Rectangle {
    id: root

    property var terminalManager: null

    property int __copyShortcutId: -1
    property int __pasteShortcutId: -1
    property int __clearShortcutId: -1
    property int __selectAllShortcutId: -1

    color: "#0c0c0c"

    Component.onCompleted: {
        if (shortcutManager) {
            __copyShortcutId = shortcutManager.registerShortcut("Terminal Copy", "Ctrl+C",
                                                                  ShortcutContext.Global,
                                                                  "Copy terminal command input");
            __pasteShortcutId = shortcutManager.registerShortcut("Terminal Paste", "Ctrl+V",
                                                                  ShortcutContext.Global,
                                                                  "Paste into terminal command input");
            __clearShortcutId = shortcutManager.registerShortcut("Terminal Clear", "Ctrl+L",
                                                                  ShortcutContext.Global,
                                                                  "Clear terminal output");
            __selectAllShortcutId = shortcutManager.registerShortcut("Terminal Select All", "Ctrl+A",
                                                                      ShortcutContext.Global,
                                                                      "Select terminal command input");
        }
    }

    Component.onDestruction: {
        if (shortcutManager) {
            if (__copyShortcutId !== -1) shortcutManager.removeShortcut(__copyShortcutId);
            if (__pasteShortcutId !== -1) shortcutManager.removeShortcut(__pasteShortcutId);
            if (__clearShortcutId !== -1) shortcutManager.removeShortcut(__clearShortcutId);
            if (__selectAllShortcutId !== -1) shortcutManager.removeShortcut(__selectAllShortcutId);
        }
    }

    Connections {
        target: shortcutManager
        function onShortcutActivated(id) {
            if (id === __copyShortcutId) {
                if (clipboardManager) {
                    clipboardManager.copyText(commandInput.text);
                }
            } else if (id === __pasteShortcutId) {
                if (clipboardManager) {
                    commandInput.text = clipboardManager.pasteText();
                }
            } else if (id === __clearShortcutId) {
                if (root.terminalManager) {
                    root.terminalManager.clearOutput();
                }
            } else if (id === __selectAllShortcutId) {
                commandInput.selectAll();
            }
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 8
        spacing: 4

        ScrollView {
            id: outputScroll

            width: parent.width
            height: parent.height - 36 - 4

            TextArea {
                id: outputArea

                readOnly: true
                text: root.terminalManager ? root.terminalManager.output : ""
                color: "#e2e8f0"
                font.family: "monospace"
                font.pixelSize: 14
                wrapMode: TextEdit.Wrap
                background: Rectangle {
                    color: "transparent"
                }
            }

            Component.onCompleted: {
                outputArea.textChanged.connect(function () {
                    outputArea.cursorPosition = outputArea.text.length;
                });
            }
        }

        Row {
            width: parent.width
            height: 36
            spacing: 6

            Text {
                id: promptLabel

                anchors.verticalCenter: parent.verticalCenter
                text: root.terminalManager && root.terminalManager.session
                      ? root.terminalManager.session.prompt + " "
                      : ""
                color: "#22c55e"
                font.family: "monospace"
                font.pixelSize: 14
            }

            TextField {
                id: commandInput

                width: parent.width - promptLabel.width - parent.spacing - copyButton.width - pasteButton.width - 3 * parent.spacing
                height: parent.height
                color: "#e2e8f0"
                font.family: "monospace"
                font.pixelSize: 14
                background: Rectangle {
                    color: "#171717"
                    radius: 4
                }
                placeholderText: "Type a command..."
                placeholderTextColor: "#64748b"

                Keys.onReturnPressed: {
                    if (root.terminalManager) {
                        root.terminalManager.executeCommand(commandInput.text);
                    }
                    commandInput.clear();
                }
            }

            Button {
                id: copyButton

                text: "Copy"
                height: parent.height

                onClicked: {
                    if (clipboardManager) {
                        clipboardManager.copyText(commandInput.text);
                    }
                }
            }

            Button {
                id: pasteButton

                text: "Paste"
                height: parent.height

                onClicked: {
                    if (clipboardManager) {
                        commandInput.text = clipboardManager.pasteText();
                    }
                }
            }
        }
    }
}
