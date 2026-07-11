#include "bos/UpdateManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"
#include "bos/UpdateInfo.h"

namespace bos::shell {

UpdateManager::UpdateManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << QStringLiteral("[BDE] UpdateManager initialized");

    m_delayTimer.setSingleShot(true);
    connect(&m_delayTimer, &QTimer::timeout, this, [this]() {
        createPlaceholderUpdate();
        setUpdateState(UpdateState::UpdatesAvailable);
        notify(QStringLiteral("Updates available"),
               QStringLiteral("Baytevora OS Preview Update is ready."));
        notify(QStringLiteral("Update Manager"), QStringLiteral("Check completed."));
    });
}

UpdateManager::~UpdateManager() = default;

void UpdateManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QString UpdateManager::currentVersion() const
{
    return m_currentVersion;
}

QString UpdateManager::latestVersion() const
{
    return m_latestVersion;
}

int UpdateManager::updateState() const
{
    return static_cast<int>(m_state);
}

int UpdateManager::updatesAvailable() const
{
    return m_updates.size();
}

QVariantList UpdateManager::availableUpdates() const
{
    QVariantList list;
    for (const UpdateInfo &info : m_updates) {
        list.append(info.toMap());
    }
    return list;
}

void UpdateManager::checkForUpdates()
{
    if (m_state == UpdateState::Checking) {
        return;
    }

    setUpdateState(UpdateState::Checking);
    qDebug() << QStringLiteral("[BDE] Checking for updates...");
    notify(QStringLiteral("Update Manager"), QStringLiteral("Checking for updates..."));

    // Sprint 24: placeholder delay that simulates an online check. No network
    // request is performed.
    m_delayTimer.start(1200);
}

void UpdateManager::clearUpdates()
{
    if (!m_updates.isEmpty()) {
        m_updates.clear();
        m_latestVersion = m_currentVersion;
        emit latestVersionChanged();
        emit updatesAvailableChanged();
        emit availableUpdatesChanged();
    }

    if (m_state != UpdateState::Idle) {
        setUpdateState(UpdateState::Idle);
    }
}

QString UpdateManager::stateName() const
{
    switch (m_state) {
    case UpdateState::Idle:
        return QStringLiteral("Idle");
    case UpdateState::Checking:
        return QStringLiteral("Checking for updates");
    case UpdateState::UpdatesAvailable:
        return QStringLiteral("Updates available");
    case UpdateState::Downloading:
        return QStringLiteral("Downloading updates");
    case UpdateState::ReadyToInstall:
        return QStringLiteral("Ready to install");
    case UpdateState::UpToDate:
        return QStringLiteral("System is up to date");
    case UpdateState::Error:
        return QStringLiteral("Error");
    }
    return QStringLiteral("Unknown");
}

void UpdateManager::setUpdateState(UpdateState::Value state)
{
    if (m_state != state) {
        m_state = state;
        emit updateStateChanged();
    }
}

void UpdateManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                  QStringLiteral("Update"),
                                                  QStringLiteral("info"));
    }
}

void UpdateManager::createPlaceholderUpdate()
{
    UpdateInfo info;
    info.version = QStringLiteral("0.2.0-alpha");
    info.title = QStringLiteral("Baytevora OS Preview Update");
    info.description = QStringLiteral("Placeholder update used for framework validation.");
    info.size = QStringLiteral("128 MB");
    info.releaseDate = QDateTime::currentDateTimeUtc();
    info.type = QStringLiteral("System");

    m_updates.append(info);
    m_latestVersion = info.version;

    emit latestVersionChanged();
    emit updatesAvailableChanged();
    emit availableUpdatesChanged();
}

} // namespace bos::shell
