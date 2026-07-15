import QtQuick

/**
 * @brief Browser toolbar with New Tab, Back, Forward, Reload/Stop, Home,
 *        Bookmarks, History, Add Bookmark, Downloads, Privacy, and Address Bar.
 */
Rectangle {
    id: root

    property var webView: null
    property var browserManager: null

    signal showDownloads()
    signal showBookmarks()
    signal showHistory()
    signal showPrivacy()

    height: AdaptiveLayoutManager.toolbarHeight
    width: parent ? parent.width : 600
    color: ThemeManager.surfaceColor
    border.color: ThemeManager.borderColor
    border.width: 1

    Row {
        anchors.fill: parent
        anchors.margins: SpacingManager.space8
        spacing: SpacingManager.space8

        BrowserToolButton {
            id: newTabButton

            label: "New Tab"
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.newTab();
                }
            }
        }

        BrowserToolButton {
            id: backButton

            label: "Back"
            enabled: root.browserManager ? root.browserManager.canGoBack : false
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.goBack();
                }
            }
        }

        BrowserToolButton {
            id: forwardButton

            label: "Forward"
            enabled: root.browserManager ? root.browserManager.canGoForward : false
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.goForward();
                }
            }
        }

        BrowserToolButton {
            id: reloadButton

            label: root.browserManager && root.browserManager.loading ? "Stop" : "Reload"
            onClicked: {
                if (root.browserManager && root.browserManager.loading) {
                    root.browserManager.stop();
                } else if (root.browserManager) {
                    root.browserManager.reload();
                }
            }
        }

        BrowserToolButton {
            id: homeButton

            label: "Home"
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.goHome();
                }
            }
        }

        BrowserToolButton {
            id: bookmarksButton

            label: "Bookmarks"
            onClicked: root.showBookmarks()
        }

        BrowserToolButton {
            id: historyButton

            label: "History"
            onClicked: root.showHistory()
        }

        BrowserToolButton {
            id: addBookmarkButton

            label: "Add Bookmark"
            enabled: root.browserManager && root.browserManager.currentUrl.length > 0
            opacity: enabled ? 1.0 : 0.4
            onClicked: {
                if (root.browserManager) {
                    root.browserManager.bookmarkManager.addBookmark(
                        root.browserManager.pageTitle || root.browserManager.currentUrl,
                        root.browserManager.currentUrl);
                }
            }
        }

        BrowserToolButton {
            id: downloadsButton

            label: "Downloads"
            onClicked: root.showDownloads()
        }

        BrowserToolButton {
            id: privacyButton

            label: "Privacy"
            onClicked: root.showPrivacy()
        }

        AddressBar {
            id: addressBar

            height: parent.height
            width: parent.width - newTabButton.width - backButton.width - forwardButton.width - reloadButton.width - homeButton.width - bookmarksButton.width - historyButton.width - addBookmarkButton.width - downloadsButton.width - privacyButton.width - parent.spacing * 10
            currentUrl: root.browserManager ? root.browserManager.currentUrl : ""
            onNavigateRequested: (url) => {
                if (root.browserManager) {
                    root.browserManager.navigate(url);
                }
            }
        }
    }
}
