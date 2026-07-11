#include "bos/LockManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"

namespace bos::shell {

LockManager::LockManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << QStringLiteral("[BDE] LockManager initialized");
}

LockManager::~LockManager() = default;

void LockManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

int LockManager::lockState() const
{
    return static_cast<int>(m_state);
}

bool LockManager::isLocked() const
{
    return m_state == LockState::Locked;
}

void LockManager::lock()
{
    if (m_state == LockState::Locked || m_state == LockState::Locking) {
        return;
    }

    setLockState(LockState::Locking);
    qDebug() << QStringLiteral("[BDE] Session lock requested");

    setLockState(LockState::Locked);
    notify(QStringLiteral("Session"), QStringLiteral("Session locked."));
    emit locked();
}

void LockManager::unlock()
{
    if (m_state == LockState::Unlocked || m_state == LockState::Unlocking) {
        return;
    }

    setLockState(LockState::Unlocking);
    qDebug() << QStringLiteral("[BDE] Session unlock requested");

    // Sprint 23: authentication is a placeholder. Any unlock request succeeds.
    setLockState(LockState::Unlocked);
    notify(QStringLiteral("Session"), QStringLiteral("Session unlocked."));
    emit unlocked();
}

QString LockManager::stateName() const
{
    switch (m_state) {
    case LockState::Unlocked:
        return QStringLiteral("Unlocked");
    case LockState::Locking:
        return QStringLiteral("Locking");
    case LockState::Locked:
        return QStringLiteral("Locked");
    case LockState::Unlocking:
        return QStringLiteral("Unlocking");
    }
    return QStringLiteral("Unknown");
}

void LockManager::setLockState(LockState::Value state)
{
    if (m_state != state) {
        m_state = state;
        emit lockStateChanged();
        emit isLockedChanged();
    }
}

void LockManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                  QStringLiteral("Lock"),
                                                  QStringLiteral("info"));
    }
}

} // namespace bos::shell
