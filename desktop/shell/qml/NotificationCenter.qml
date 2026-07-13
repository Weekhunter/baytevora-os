import QtQuick

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
        topMargin: SpacingManager.space20
        rightMargin: SpacingManager.space20
    }
    spacing: SpacingManager.space12

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
