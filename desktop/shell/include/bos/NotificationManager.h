#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

#include "bos/Notification.h"

namespace bos::shell {

/**
 * @brief Manages active notifications for the Baytevora Desktop Environment.
 *
 * NotificationManager is a QObject exposed to QML. It owns the list of active
 * notifications and provides methods to create, remove, and clear them. The
 * manager does not persist notifications, group them, or dismiss them automatically.
 */
class NotificationManager : public QObject {
    Q_OBJECT

    /**
     * @brief Active notifications exposed to QML.
     */
    Q_PROPERTY(QVariantList notifications READ notifications NOTIFY notificationsChanged)

public:
    explicit NotificationManager(QObject *parent = nullptr);
    ~NotificationManager() override;

    /**
     * @brief Creates a notification and adds it to the active list.
     * @return The unique notification ID.
     */
    Q_INVOKABLE int createNotification(const QString &title,
                                       const QString &message,
                                       const QString &sourceApplication,
                                       const QString &severity);

    /**
     * @brief Removes the notification with the given ID.
     */
    Q_INVOKABLE void removeNotification(int id);

    /**
     * @brief Clears all active notifications.
     */
    Q_INVOKABLE void clearNotifications();

    /**
     * @return A list of all active notifications as QVariantMap items.
     */
    QVariantList notifications() const;

    /**
     * @brief Finds a notification by ID.
     * @return The notification map, or an empty map if not found.
     */
    Q_INVOKABLE QVariantMap findNotification(int id) const;

signals:
    void notificationsChanged();

private:
    QList<Notification> m_notifications;
    int m_nextId = 1;
};

} // namespace bos::shell
