#pragma once

#include <QObject>
#include <QTimer>

namespace bos::shell {

class NotificationManager;
class SystemInfo;

/**
 * @brief Gathers read-only system metrics and exposes them through SystemInfo.
 *
 * SystemMonitorManager refreshes metrics once per second while monitoring is
 * active. It uses /proc and platform APIs to collect CPU, memory, swap, disk,
 * uptime, and system identification information.
 */
class SystemMonitorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(SystemInfo *info READ info NOTIFY infoChanged FINAL)

public:
    explicit SystemMonitorManager(QObject *parent = nullptr);
    ~SystemMonitorManager() override;

    SystemInfo *info() const;

    Q_INVOKABLE void setNotificationManager(QObject *manager);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void startMonitoring();
    Q_INVOKABLE void stopMonitoring();

signals:
    void infoChanged();

private:
    void refreshCpu();
    void refreshMemory();
    void refreshDisk();
    void refreshUptime();
    void refreshPlatform();
    void refreshStaticInfo();

    qint64 readProcValue(const QString &path, const QString &key) const;

    SystemInfo *m_info = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QTimer *m_timer = nullptr;

    // Previous CPU counters for usage delta.
    quint64 m_lastCpuTotal = 0;
    quint64 m_lastCpuIdle = 0;
    bool m_hasCpuBaseline = false;
};

} // namespace bos::shell
