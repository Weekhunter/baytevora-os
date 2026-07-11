#pragma once

#include <QObject>

#include "bos/LockState.h"

namespace bos::shell {

class NotificationManager;

/**
 * @brief Coordinates the Baytevora Lock Screen (BLS) state.
 *
 * LockManager tracks the desktop lock lifecycle. This sprint uses placeholder
 * authentication: calling unlock() always succeeds. Real authentication, idle
 * timers, and Linux session locking are reserved for future sprints.
 */
class LockManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(int lockState READ lockState NOTIFY lockStateChanged)
    Q_PROPERTY(bool isLocked READ isLocked NOTIFY isLockedChanged)

public:
    explicit LockManager(QObject *parent = nullptr);
    ~LockManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    int lockState() const;
    bool isLocked() const;

    Q_INVOKABLE void lock();
    Q_INVOKABLE void unlock();

    Q_INVOKABLE QString stateName() const;

signals:
    void lockStateChanged();
    void isLockedChanged();
    void locked();
    void unlocked();

private:
    void setLockState(LockState::Value state);
    void notify(const QString &title, const QString &message);

    LockState::Value m_state = LockState::Unlocked;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
