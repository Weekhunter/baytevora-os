import QtQuick
import BOS.Shell

/**
 * @brief Displays active notifications in a vertical column at the top-right.
 *
 * NotificationCenter binds to notificationManager.notifications and renders
 * one NotificationPopup per item. Notifications are dismissed through the
 * manager so business logic remains in C++.
 */
Column {
    id: root

    anchors {
        top: parent ? parent.top : undefined
        right: parent ? parent.right : undefined
        topMargin: SpacingManager ? SpacingManager.space20 : 20
        rightMargin: SpacingManager ? SpacingManager.space20 : 20
    }
    spacing: SpacingManager ? SpacingManager.space12 : 12

    property int __escapeShortcutId: -1

    Component.onCompleted: {
        if (shortcutManager) {
            __escapeShortcutId = shortcutManager.registerShortcut("Notification Center Close", "Escape",
                                                                   ShortcutContext.Global,
                                                                   "Close all visible notifications");
        }
    }

    Component.onDestruction: {
        if (shortcutManager && __escapeShortcutId !== -1) {
            shortcutManager.removeShortcut(__escapeShortcutId);
        }
    }

    Connections {
        target: shortcutManager
        function onShortcutActivated(id) {
            if (id === __escapeShortcutId && notificationManager) {
                notificationManager.clearNotifications();
            }
        }
    }

    Repeater {
        model: notificationManager ? notificationManager.notifications : []

        delegate: NotificationPopup {
            notificationId: modelData.id
            notificationTitle: modelData.title
            message: modelData.message
            sourceApplication: modelData.sourceApplication
            timestamp: Qt.formatDateTime(modelData.timestamp, "hh:mm")
            severity: modelData.severity

            onDismissed: {
                if (notificationManager) {
                    notificationManager.removeNotification(modelData.id)
                }
            }
        }
    }
}
