#include "bos/PowerManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"

namespace bos::shell {

PowerManager::PowerManager(QObject *parent)
    : QObject(parent)
{
    registerDefaultActions();
    qDebug() << QStringLiteral("[BDE] PowerManager initialized");
}

PowerManager::~PowerManager() = default;

void PowerManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QVariantList PowerManager::actions() const
{
    QVariantList list;
    list.reserve(m_actions.size());
    for (const PowerAction &action : m_actions) {
        list.append(action.toMap());
    }
    return list;
}

bool PowerManager::executeAction(int type)
{
    const auto value = static_cast<PowerActionType::Value>(type);
    const PowerAction *action = findAction(value);
    if (!action || !action->enabled) {
        qWarning() << QStringLiteral("[BDE] Power action unavailable:") << typeToString(value);
        return false;
    }

    logActionRequest(value);

    if (m_notificationManager) {
        m_notificationManager->createNotification(
            QStringLiteral("Power"),
            typeToString(value) + QStringLiteral(" requested."),
            QStringLiteral("Power"),
            QStringLiteral("info"));
    }

    emit actionExecuted(static_cast<int>(value));
    return true;
}

bool PowerManager::isAvailable(int type) const
{
    const auto value = static_cast<PowerActionType::Value>(type);
    const PowerAction *action = findAction(value);
    return action && action->enabled;
}

int PowerManager::actionCount() const
{
    return m_actions.size();
}

void PowerManager::registerDefaultActions()
{
    auto add = [this](PowerActionType::Value type, const QString &title,
                      const QString &description, const QString &iconName) {
        PowerAction action;
        action.id = QStringLiteral("power-") + typeToString(type).toLower().replace(QStringLiteral(" "), QStringLiteral("-"));
        action.title = title;
        action.description = description;
        action.type = type;
        action.enabled = true;
        action.iconName = iconName;
        m_actions.append(action);
    };

    add(PowerActionType::Shutdown, QStringLiteral("Shutdown"),
        QStringLiteral("Power off the session (placeholder)"), QStringLiteral("shutdown"));
    add(PowerActionType::Restart, QStringLiteral("Restart"),
        QStringLiteral("Restart the session (placeholder)"), QStringLiteral("restart"));
    add(PowerActionType::LogOut, QStringLiteral("Log Out"),
        QStringLiteral("End the current session (placeholder)"), QStringLiteral("logout"));
    add(PowerActionType::Lock, QStringLiteral("Lock"),
        QStringLiteral("Lock the session (placeholder)"), QStringLiteral("lock"));
    add(PowerActionType::Sleep, QStringLiteral("Sleep"),
        QStringLiteral("Put the session to sleep (placeholder)"), QStringLiteral("sleep"));
    add(PowerActionType::Hibernate, QStringLiteral("Hibernate"),
        QStringLiteral("Hibernate the session (placeholder)"), QStringLiteral("hibernate"));

    emit actionsChanged();
}

void PowerManager::logActionRequest(PowerActionType::Value type) const
{
    qDebug() << QStringLiteral("[BDE]") << typeToString(type) + QStringLiteral(" requested");
}

QString PowerManager::typeToString(PowerActionType::Value type) const
{
    switch (type) {
    case PowerActionType::Shutdown:
        return QStringLiteral("Shutdown");
    case PowerActionType::Restart:
        return QStringLiteral("Restart");
    case PowerActionType::LogOut:
        return QStringLiteral("Log Out");
    case PowerActionType::Lock:
        return QStringLiteral("Lock");
    case PowerActionType::Sleep:
        return QStringLiteral("Sleep");
    case PowerActionType::Hibernate:
        return QStringLiteral("Hibernate");
    }
    return QStringLiteral("Unknown");
}

const PowerAction *PowerManager::findAction(PowerActionType::Value type) const
{
    for (const PowerAction &action : m_actions) {
        if (action.type == type) {
            return &action;
        }
    }
    return nullptr;
}

} // namespace bos::shell
