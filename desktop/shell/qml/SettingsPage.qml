import QtQuick

/**
 * @brief Renders the body of the currently selected Settings page.
 *
 * SettingsPage displays placeholder controls for Appearance and Wallpaper,
 * read-only system information, and static About details. All configuration
 * requests are delegated to SettingsManager and only logged for now.
 */
Rectangle {
    id: root

    property var settingsManager: null
    property var lastCompletedOperation: null

    color: "transparent"

    Connections {
        target: dragManager
        function onDragCompleted() {
            if (dragManager) {
                root.lastCompletedOperation = dragManager.currentOperation;
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 20

        // Appearance
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "appearance"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Text {
                    text: "Theme"
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                }

                Row {
                    spacing: 12

                    SettingsButton {
                        text: "Light"
                        onClicked: root.settingsManager.setTheme("light")
                    }

                    SettingsButton {
                        text: "Dark"
                        onClicked: root.settingsManager.setTheme("dark")
                    }

                    SettingsButton {
                        text: "Auto"
                        onClicked: root.settingsManager.setTheme("auto")
                    }
                }

                Text {
                    text: "Accent Color"
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                }

                Row {
                    spacing: 12

                    SettingsButton {
                        text: "Blue"
                        onClicked: root.settingsManager.setAccentColor("blue")
                    }

                    SettingsButton {
                        text: "Green"
                        onClicked: root.settingsManager.setAccentColor("green")
                    }

                    SettingsButton {
                        text: "Purple"
                        onClicked: root.settingsManager.setAccentColor("purple")
                    }
                }

                Text {
                    text: "Font Size"
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                }

                Row {
                    spacing: 12

                    SettingsButton {
                        text: "Small"
                        onClicked: root.settingsManager.setFontSize(12)
                    }

                    SettingsButton {
                        text: "Medium"
                        onClicked: root.settingsManager.setFontSize(16)
                    }

                    SettingsButton {
                        text: "Large"
                        onClicked: root.settingsManager.setFontSize(20)
                    }
                }
            }
        }

        // Wallpaper
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "wallpaper"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Text {
                    text: "Current Wallpaper"
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                }

                Text {
                    text: root.settingsManager ? root.settingsManager.wallpaperPath : ""
                    color: "ThemeManager.textDisabled"
                    font.pixelSize: 14
                    wrapMode: Text.WrapAnywhere
                    width: parent.width
                }

                Row {
                    spacing: 12

                    SettingsButton {
                        text: "Choose Wallpaper"
                        onClicked: root.settingsManager.chooseWallpaper()
                    }

                    SettingsButton {
                        text: "Restore Default"
                        onClicked: root.settingsManager.restoreDefaultWallpaper()
                    }
                }
            }
        }

        // System
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "system"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "BOS Version"
                    value: root.settingsManager ? root.settingsManager.bosVersion : ""
                }

                InfoRow {
                    label: "Qt Version"
                    value: root.settingsManager ? root.settingsManager.qtVersion : ""
                }

                InfoRow {
                    label: "Architecture"
                    value: root.settingsManager ? root.settingsManager.architecture : ""
                }

                InfoRow {
                    label: "Session Uptime"
                    value: root.settingsManager ? root.settingsManager.uptime : ""
                }

                InfoRow {
                    label: "Current User"
                    value: loginManager && loginManager.selectedUser
                           ? loginManager.selectedUser.displayName
                           : "—"
                }

                InfoRow {
                    label: "Session State"
                    value: loginManager ? loginManager.stateName() : "—"
                }

                InfoRow {
                    label: "Lock State"
                    value: lockManager ? lockManager.stateName() : "—"
                }
            }
        }

        // Clipboard
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "clipboard"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "Clipboard Available"
                    value: clipboardManager && clipboardManager.hasContent ? "Yes" : "No"
                }

                InfoRow {
                    label: "Current Content Length"
                    value: clipboardManager && clipboardManager.hasContent
                           ? String(clipboardManager.text.length)
                           : "0"
                }

                SettingsButton {
                    text: "Clear Clipboard"
                    onClicked: {
                        if (clipboardManager) {
                            clipboardManager.clearClipboard();
                        }
                    }
                }
            }
        }

        // Shortcuts
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "shortcuts"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "Shortcut Subsystem"
                    value: shortcutManager ? "Active" : "Inactive"
                }

                InfoRow {
                    label: "Total Shortcut Count"
                    value: shortcutManager ? String(shortcutManager.registeredShortcuts.length) : "0"
                }

                Text {
                    text: "Registered Shortcuts"
                    color: "ThemeManager.surfaceSecondaryColor"
                    font.pixelSize: 16
                    font.weight: Font.DemiBold
                }

                Repeater {
                    model: shortcutManager ? shortcutManager.registeredShortcuts : []

                    Text {
                        text: modelData.name + " (" + modelData.keySequence + ")"
                        color: "ThemeManager.borderColor"
                        font.pixelSize: 14
                    }
                }
            }
        }

        // Search
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "search"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "Search Subsystem"
                    value: searchManager ? "Active" : "Inactive"
                }

                InfoRow {
                    label: "Registered Providers"
                    value: searchManager ? String(searchManager.providerCount()) : "0"
                }

                InfoRow {
                    label: "Indexed Items"
                    value: searchManager ? String(searchManager.itemCount()) : "0"
                }

                InfoRow {
                    label: "Current Result Count"
                    value: searchManager && searchManager.results ? String(searchManager.results.length) : "0"
                }
            }
        }

        // Power
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "power"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "Power Subsystem"
                    value: powerManager ? "Active" : "Inactive"
                }

                InfoRow {
                    label: "Registered Actions"
                    value: powerManager ? String(powerManager.actionCount()) : "0"
                }

                InfoRow {
                    label: "Session Uptime"
                    value: root.settingsManager ? root.settingsManager.uptime : "—"
                }
            }
        }

        // Drag & Drop
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "dragdrop"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 14

                InfoRow {
                    label: "Framework Status"
                    value: dragManager ? "Active" : "Inactive"
                }

                InfoRow {
                    label: "Current State"
                    value: dragManager && dragManager.currentOperation
                           ? dragManager.currentOperation.stateName
                           : "Idle"
                }

                InfoRow {
                    label: "Current Drag Type"
                    value: dragManager && dragManager.currentOperation
                           ? dragManager.currentOperation.data.typeName
                           : "None"
                }

                InfoRow {
                    label: "Last Completed Operation"
                    value: root.lastCompletedOperation
                           ? (root.lastCompletedOperation.source + " → " + root.lastCompletedOperation.target)
                           : "—"
                }
            }
        }

        // Updates
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "updates"

            UpdatesPage {
                anchors.fill: parent
                anchors.margins: 24
            }
        }

        // Packages
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "packages"

            PackagesPage {
                anchors.fill: parent
                anchors.margins: 24
            }
        }

        // Store
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: "ThemeManager.surfaceSecondaryColor"
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "store"

            StoreSettingsPage {
                anchors.fill: parent
                anchors.margins: 24
            }
        }

        // About
        Rectangle {
            width: parent.width
            height: childrenRect.height + 48
            color: ThemeManager.surfaceSecondaryColor
            radius: DesignTokens.radiusXLarge
            visible: root.settingsManager && root.settingsManager.currentPage === "about"

            Column {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 16

                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 96
                    height: 115
                    source: BrandingManager.applicationSymbolUrl("Baytevora OS")
                    fillMode: Image.PreserveAspectFit
                    sourceSize.width: 192
                    sourceSize.height: 230
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: BrandingManager.osName
                    color: ThemeManager.textPrimary
                    font.pixelSize: 22
                    font.weight: Font.DemiBold
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: BrandingManager.osVersion
                    color: ThemeManager.textSecondary
                    font.pixelSize: 14
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: BrandingManager.poweredBy
                    color: ThemeManager.textDisabled
                    font.pixelSize: 14
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Copyright \u00A9 2026 " + BrandingManager.companyName
                    color: ThemeManager.textDisabled
                    font.pixelSize: 14
                }
            }
        }
    }
}
