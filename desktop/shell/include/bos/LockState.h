#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Lifecycle states of the LockManager.
 *
 * LockState is exposed to QML as LockState so the lock screen can react to
 * Unlocked, Locking, Locked, and Unlocking.
 */
class LockState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Unlocked,
        Locking,
        Locked,
        Unlocking
    };
    Q_ENUM(Value)

    explicit LockState(QObject *parent = nullptr);
};

} // namespace bos::shell
