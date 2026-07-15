import QtQuick
import BOS.Shell

/**
 * @brief The Baytevora Launcher overlay and panel.
 *
 * Launcher is a full-screen overlay that appears when launcher.visible is true.
 * A click anywhere outside the panel closes the launcher, and pressing Escape
 * closes it as well. The panel is anchored to the bottom-left of the screen,
 * directly above the taskbar.
 *
 * The launcher has rounded corners, a dark background, and a thin border.
 * It uses no see-through effects, blur, or motion effects.
 */
Item {
    id: root

    anchors.fill: parent
    visible: launcher ? launcher.visible : false
    z: 200
    focus: visible

    onVisibleChanged: {
        if (!visible && searchField) {
            searchField.text = "";
            if (searchManager) {
                searchManager.clearResults();
            }
        }
    }

    Keys.onEscapePressed: (event) => {
        if (launcher) {
            launcher.closeLauncher();
        }
        event.accepted = true;
    }

    // Full-screen overlay behind the panel. Clicking it closes the launcher.
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (launcher) {
                launcher.closeLauncher()
            }
        }
    }

    // Launcher panel
    Rectangle {
        id: panel

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: AdaptiveLayoutManager.taskbarHeight
        anchors.leftMargin: SpacingManager.space8
        width: 320
        height: 280
        color: ThemeManager.launcherBackground
        border.color: ThemeManager.borderColor
        border.width: 1
        radius: DesignTokens.radiusMedium

        // Absorb clicks on the panel so they do not propagate to the overlay.
        MouseArea {
            anchors.fill: parent
        }

        Column {
            anchors.fill: parent
            anchors.margins: SpacingManager.space16
            spacing: SpacingManager.space12

            LauncherHeader {
                id: header

                width: parent.width
            }

            SearchField {
                id: searchField

                width: parent.width
                height: 32

                onTextChanged: {
                    if (searchManager) {
                        searchManager.search(text);
                    }
                }
            }

            Item {
                width: parent.width
                height: parent.height - header.height - searchField.height - 2 * parent.spacing

                LauncherGrid {
                    anchors.fill: parent
                    visible: searchField.text.length === 0
                }

                SearchResults {
                    anchors.fill: parent
                    visible: searchField.text.length > 0

                    onResultSelected: {
                        if (!result) {
                            return;
                        }

                        if (result.category === SearchCategory.Application) {
                            if (applicationManager) {
                                applicationManager.launchApplication(result.title);
                            }
                        } else if (result.category === SearchCategory.Setting) {
                            if (settingsApplication) {
                                const pageId = result.id.replace(/^settings-/, "");
                                settingsApplication.openPage(pageId);
                            }
                        } else if (result.category === SearchCategory.Desktop) {
                            console.log("[BDE] Desktop item selected: " + result.title);
                        }

                        if (launcher) {
                            launcher.closeLauncher();
                        }
                    }
                }
            }
        }
    }
}
