import QtQuick

/**
 * @brief Main view of the native Browser application with multi-tab, download,
 *        bookmark, history, and privacy support.
 *
 * BrowserWindow fills the content area of a WindowFrame and arranges the
 * toolbar, tab bar, web view, status bar, and overlay panels. Each Browser
 * window creates its own BrowserManager so tab, download, bookmark, history,
 * permission, and privacy state stays isolated.
 */
Rectangle {
    id: root

    anchors.fill: parent
    color: ThemeManager.backgroundColor

    BrowserManager {
        id: browserManager

        Component.onCompleted: {
            if (typeof notificationManager !== "undefined") {
                browserManager.setNotificationManager(notificationManager);
            }
        }
    }

    Column {
        id: mainColumn

        anchors.fill: parent
        spacing: 0

        BrowserToolbar {
            id: toolbar

            width: parent.width
            height: AdaptiveLayoutManager.toolbarHeight
            browserManager: browserManager
            onShowDownloads: downloadsWindow.visible = true
            onShowBookmarks: bookmarksWindow.visible = true
            onShowHistory: historyWindow.visible = true
            onShowPrivacy: privacyWindow.visible = true
        }

        BrowserTabBar {
            id: tabBar

            width: parent.width
            height: AdaptiveLayoutManager.tabBarHeight
            browserManager: browserManager
        }

        BrowserView {
            id: browserView

            width: parent.width
            height: parent.height - toolbar.height - tabBar.height - statusBar.height
            browserManager: browserManager
        }

        BrowserStatusBar {
            id: statusBar

            width: parent.width
            height: AdaptiveLayoutManager.titleBarHeight
            browserManager: browserManager
        }
    }

    BrowserDownloadsWindow {
        id: downloadsWindow

        visible: false
        browserManager: browserManager
    }

    BrowserBookmarksWindow {
        id: bookmarksWindow

        visible: false
        browserManager: browserManager
    }

    BrowserHistoryWindow {
        id: historyWindow

        visible: false
        browserManager: browserManager
    }

    BrowserPrivacyWindow {
        id: privacyWindow

        visible: false
        browserManager: browserManager
    }
}
