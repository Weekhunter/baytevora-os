import QtQuick
import QtWebEngine

/**
 * @brief Multi-tab browser view using Qt WebEngineView.
 *
 * BrowserView creates one WebEngineView per tab. Only the active tab's view
 * is visible; inactive tabs remain in memory while the window is open.
 * Download requests from any view are forwarded to BrowserManager. Page
 * title changes that occur when a page is not loading are recorded in the
 * browsing history. Permission requests and popup window requests are routed
 * through BrowserPermissionManager and BrowserPrivacySettings.
 */
Rectangle {
    id: root

    property var browserManager: null

    color: ThemeManager.backgroundColor

    function featureToType(feature) {
        if (feature === WebEngineView.MediaAudioCapture) {
            return "Microphone";
        }
        if (feature === WebEngineView.MediaVideoCapture) {
            return "Camera";
        }
        if (feature === WebEngineView.MediaAudioVideoCapture) {
            return "Camera";
        }
        if (feature === WebEngineView.Geolocation) {
            return "Location";
        }
        if (feature === WebEngineView.Notifications) {
            return "Notifications";
        }
        if (feature === WebEngineView.ClipboardReadWrite) {
            return "Clipboard";
        }
        return "";
    }

    function handleFeaturePermission(view, feature, securityOrigin) {
        if (!root.browserManager || !root.browserManager.permissionManager) {
            view.grantFeaturePermission(securityOrigin, feature, false);
            return;
        }
        const type = root.featureToType(feature);
        if (type === "") {
            view.grantFeaturePermission(securityOrigin, feature, false);
            return;
        }

        const state = root.browserManager.permissionManager.permission(securityOrigin, type);
        if (state === "Allow") {
            view.grantFeaturePermission(securityOrigin, feature, true);
        } else if (state === "Block") {
            view.grantFeaturePermission(securityOrigin, feature, false);
        } else {
            permissionPrompt.show(view, feature, securityOrigin, type);
        }
    }

    function handlePopup(request) {
        if (!root.browserManager || !root.browserManager.privacySettings) {
            request.reject();
            return;
        }
        if (root.browserManager.privacySettings.popupsBlocked) {
            request.reject();
        } else {
            // Placeholder-safe: opening popup windows is reserved for a future sprint.
            request.reject();
        }
    }

    Repeater {
        id: tabViews

        model: root.browserManager ? root.browserManager.tabs : []

        WebEngineView {
            id: webView

            anchors.fill: parent
            visible: root.browserManager && modelData
                     ? modelData.tabId === root.browserManager.activeTabId
                     : false
            url: modelData ? modelData.url : ""

            onUrlChanged: {
                if (root.browserManager && modelData
                    && modelData.tabId === root.browserManager.activeTabId
                    && root.browserManager.currentUrl !== url.toString()) {
                    root.browserManager.setCurrentUrl(url.toString());
                }
            }

            onTitleChanged: {
                if (root.browserManager && modelData
                    && modelData.tabId === root.browserManager.activeTabId) {
                    root.browserManager.setPageTitle(title);
                    if (!loading) {
                        root.browserManager.recordHistory(title, url.toString());
                    }
                }
            }

            onLoadingChanged: {
                if (root.browserManager && modelData
                    && modelData.tabId === root.browserManager.activeTabId) {
                    root.browserManager.setLoading(loading);
                }
            }

            onCanGoBackChanged: {
                if (root.browserManager && modelData
                    && modelData.tabId === root.browserManager.activeTabId) {
                    root.browserManager.setCanGoBack(canGoBack);
                }
            }

            onCanGoForwardChanged: {
                if (root.browserManager && modelData
                    && modelData.tabId === root.browserManager.activeTabId) {
                    root.browserManager.setCanGoForward(canGoForward);
                }
            }

            onDownloadRequested: function(request) {
                if (root.browserManager) {
                    root.browserManager.acceptDownloadRequest(request);
                } else if (request) {
                    request.cancel();
                }
            }

            onFeaturePermissionRequested: function(feature, securityOrigin) {
                root.handleFeaturePermission(this, feature, securityOrigin);
            }

            onJavaScriptWindowRequested: function(request) {
                root.handlePopup(request);
            }
        }
    }

    Connections {
        target: root.browserManager

        function onReloadRequested() {
            for (let i = 0; i < tabViews.count; ++i) {
                const item = tabViews.itemAt(i);
                if (item && item.visible) {
                    item.reload();
                    return;
                }
            }
        }

        function onStopRequested() {
            for (let i = 0; i < tabViews.count; ++i) {
                const item = tabViews.itemAt(i);
                if (item && item.visible) {
                    item.stop();
                    return;
                }
            }
        }

        function onBackRequested() {
            for (let i = 0; i < tabViews.count; ++i) {
                const item = tabViews.itemAt(i);
                if (item && item.visible) {
                    item.goBack();
                    return;
                }
            }
        }

        function onForwardRequested() {
            for (let i = 0; i < tabViews.count; ++i) {
                const item = tabViews.itemAt(i);
                if (item && item.visible) {
                    item.goForward();
                    return;
                }
            }
        }

        function onManualDownloadRequested(downloadId, url) {
            if (manualDownloadView) {
                manualDownloadView.url = url;
            }
        }
    }

    // Hidden WebEngineView used to fulfill manual startDownload() requests.
    WebEngineView {
        id: manualDownloadView

        visible: false
        width: 1
        height: 1

        onDownloadRequested: function(request) {
            if (root.browserManager) {
                root.browserManager.acceptDownloadRequest(request);
            } else if (request) {
                request.cancel();
            }
        }
    }

    BrowserPermissionPrompt {
        id: permissionPrompt

        browserManager: root.browserManager
    }
}
