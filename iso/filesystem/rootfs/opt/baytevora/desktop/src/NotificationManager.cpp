#include "bos/NotificationManager.h"

#include <algorithm>

#include <QDebug>
#include <QDateTime>

namespace bos::shell {

NotificationManager::NotificationManager(QObject *parent)
    : QObject(parent)
{
}

NotificationManager::~NotificationManager() = default;

int NotificationManager::createNotification(const QString &title,
                                            const QString &message,
                                            const QString &sourceApplication,
                                            const QString &severity)
{
    NotificationSeverity level = NotificationSeverity::Info;
    const QString lowerSeverity = severity.toLower();
    if (lowerSeverity == QStringLiteral("success")) {
        level = NotificationSeverity::Success;
    } else if (lowerSeverity == QStringLiteral("warning")) {
        level = NotificationSeverity::Warning;
    } else if (lowerSeverity == QStringLiteral("error")) {
        level = NotificationSeverity::Error;
    }

    const int id = m_nextId++;
    m_notifications.append(Notification(id,
                                        title,
                                        message,
                                        sourceApplication,
                                        QDateTime::currentDateTime(),
                                        level));

    qDebug() << QStringLiteral("[BDE] Notification created");
    emit notificationsChanged();
    return id;
}

void NotificationManager::removeNotification(int id)
{
    const int before = m_notifications.size();
    m_notifications.erase(
        std::remove_if(m_notifications.begin(),
                       m_notifications.end(),
                       [id](const Notification &notification) { return notification.id() == id; }),
        m_notifications.end());

    if (m_notifications.size() != before) {
        qDebug() << QStringLiteral("[BDE] Notification dismissed");
        emit notificationsChanged();
    }
}

void NotificationManager::clearNotifications()
{
    if (m_notifications.isEmpty()) {
        return;
    }

    m_notifications.clear();
    qDebug() << QStringLiteral("[BDE] Notification cleared");
    emit notificationsChanged();
}

QVariantList NotificationManager::notifications() const
{
    QVariantList list;
    list.reserve(m_notifications.size());
    for (const auto &notification : m_notifications) {
        list.append(notification.toMap());
    }
    return list;
}

QVariantMap NotificationManager::findNotification(int id) const
{
    for (const auto &notification : m_notifications) {
        if (notification.id() == id) {
            return notification.toMap();
        }
    }
    return {};
}

} // namespace bos::shell
