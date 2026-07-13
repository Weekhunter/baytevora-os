#pragma once

#include <QList>
#include <QObject>
#include <QStringList>
#include <QTimer>
#include <QVariantList>

namespace bos::shell {

class NetworkInterface;
class NotificationManager;

/**
 * @brief Manages network interface discovery and state for the Network Manager.
 *
 * NetworkManager refreshes interface information every two seconds. In
 * Sprint 38 the enable/disable/connect/disconnect methods use placeholder
 * behavior that updates the local model and emits notifications; future
 * sprints will wire them to platform networking APIs.
 */
class NetworkManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList interfaces READ interfaces NOTIFY interfacesChanged FINAL)

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager() override;

    QVariantList interfaces() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void startMonitoring();
    Q_INVOKABLE void stopMonitoring();

    Q_INVOKABLE void enableInterface(const QString &name);
    Q_INVOKABLE void disableInterface(const QString &name);
    Q_INVOKABLE void connectInterface(const QString &name);
    Q_INVOKABLE void disconnectInterface(const QString &name);

signals:
    void interfacesChanged();

private:
    void updateInterfaces();
    NetworkInterface *findInterface(const QString &name);
    void notify(const QString &body);

    QList<NetworkInterface*> m_interfaces;
    NotificationManager *m_notificationManager = nullptr;
    QTimer *m_timer = nullptr;
};

} // namespace bos::shell
