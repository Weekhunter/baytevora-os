#pragma once

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <QVariantMap>

#include "bos/UpdateState.h"

namespace bos::shell {

class NotificationManager;

/**
 * @brief Coordinates the Baytevora Update Manager (BUM) lifecycle.
 *
 * UpdateManager tracks update state and owns placeholder update metadata. This
 * sprint performs no network access: checkForUpdates() transitions through the
 * states locally after a short delay.
 */
class UpdateManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentVersion READ currentVersion NOTIFY currentVersionChanged)
    Q_PROPERTY(QString latestVersion READ latestVersion NOTIFY latestVersionChanged)
    Q_PROPERTY(int updateState READ updateState NOTIFY updateStateChanged)
    Q_PROPERTY(int updatesAvailable READ updatesAvailable NOTIFY updatesAvailableChanged)
    Q_PROPERTY(QVariantList availableUpdates READ availableUpdates NOTIFY availableUpdatesChanged)

public:
    explicit UpdateManager(QObject *parent = nullptr);
    ~UpdateManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    QString currentVersion() const;
    QString latestVersion() const;
    int updateState() const;
    int updatesAvailable() const;
    QVariantList availableUpdates() const;

    Q_INVOKABLE void checkForUpdates();
    Q_INVOKABLE void clearUpdates();

    Q_INVOKABLE QString stateName() const;

signals:
    void currentVersionChanged();
    void latestVersionChanged();
    void updateStateChanged();
    void updatesAvailableChanged();
    void availableUpdatesChanged();

private:
    void setUpdateState(UpdateState::Value state);
    void notify(const QString &title, const QString &message);
    void createPlaceholderUpdate();

    QString m_currentVersion = QStringLiteral("0.1.0-alpha");
    QString m_latestVersion = QStringLiteral("0.1.0-alpha");
    UpdateState::Value m_state = UpdateState::Idle;
    QList<UpdateInfo> m_updates;
    NotificationManager *m_notificationManager = nullptr;
    QTimer m_delayTimer;
};

} // namespace bos::shell
