#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

#include "bos/PowerAction.h"
#include "bos/PowerActionType.h"

namespace bos::shell {

class NotificationManager;

/**
 * @brief Central manager for the Baytevora Power Management Service (BPS).
 *
 * PowerManager owns the set of power actions, exposes them to QML, and
 * handles action requests. It does not perform real hardware operations;
 * instead it logs the request and emits an information notification.
 */
class PowerManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList actions READ actions NOTIFY actionsChanged)

public:
    explicit PowerManager(QObject *parent = nullptr);
    ~PowerManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    QVariantList actions() const;

    Q_INVOKABLE bool executeAction(int type);
    Q_INVOKABLE bool isAvailable(int type) const;
    Q_INVOKABLE int actionCount() const;

signals:
    void actionExecuted(int type);
    void actionsChanged();

private:
    void registerDefaultActions();
    void logActionRequest(PowerActionType::Value type) const;
    QString typeToString(PowerActionType::Value type) const;
    const PowerAction *findAction(PowerActionType::Value type) const;

    QList<PowerAction> m_actions;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
