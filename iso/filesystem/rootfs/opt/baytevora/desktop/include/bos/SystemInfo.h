#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Exposes read-only system monitoring metrics to QML.
 */
class SystemInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged FINAL)
    Q_PROPERTY(int cpuThreads READ cpuThreads NOTIFY cpuThreadsChanged FINAL)
    Q_PROPERTY(double cpuFrequency READ cpuFrequency NOTIFY cpuFrequencyChanged FINAL)

    Q_PROPERTY(qint64 memoryUsed READ memoryUsed NOTIFY memoryUsedChanged FINAL)
    Q_PROPERTY(qint64 memoryAvailable READ memoryAvailable NOTIFY memoryAvailableChanged FINAL)
    Q_PROPERTY(qint64 memoryTotal READ memoryTotal NOTIFY memoryTotalChanged FINAL)

    Q_PROPERTY(qint64 swapUsed READ swapUsed NOTIFY swapUsedChanged FINAL)
    Q_PROPERTY(qint64 swapTotal READ swapTotal NOTIFY swapTotalChanged FINAL)

    Q_PROPERTY(qint64 diskUsed READ diskUsed NOTIFY diskUsedChanged FINAL)
    Q_PROPERTY(qint64 diskFree READ diskFree NOTIFY diskFreeChanged FINAL)
    Q_PROPERTY(qint64 diskTotal READ diskTotal NOTIFY diskTotalChanged FINAL)

    Q_PROPERTY(qint64 uptime READ uptime NOTIFY uptimeChanged FINAL)
    Q_PROPERTY(QString operatingSystem READ operatingSystem NOTIFY operatingSystemChanged FINAL)
    Q_PROPERTY(QString kernelVersion READ kernelVersion NOTIFY kernelVersionChanged FINAL)
    Q_PROPERTY(QString architecture READ architecture NOTIFY architectureChanged FINAL)

public:
    explicit SystemInfo(QObject *parent = nullptr);

    double cpuUsage() const;
    int cpuThreads() const;
    double cpuFrequency() const;

    qint64 memoryUsed() const;
    qint64 memoryAvailable() const;
    qint64 memoryTotal() const;

    qint64 swapUsed() const;
    qint64 swapTotal() const;

    qint64 diskUsed() const;
    qint64 diskFree() const;
    qint64 diskTotal() const;

    qint64 uptime() const;
    QString operatingSystem() const;
    QString kernelVersion() const;
    QString architecture() const;

    void setCpuUsage(double value);
    void setCpuThreads(int value);
    void setCpuFrequency(double value);

    void setMemoryUsed(qint64 value);
    void setMemoryAvailable(qint64 value);
    void setMemoryTotal(qint64 value);

    void setSwapUsed(qint64 value);
    void setSwapTotal(qint64 value);

    void setDiskUsed(qint64 value);
    void setDiskFree(qint64 value);
    void setDiskTotal(qint64 value);

    void setUptime(qint64 value);
    void setOperatingSystem(const QString &value);
    void setKernelVersion(const QString &value);
    void setArchitecture(const QString &value);

signals:
    void cpuUsageChanged();
    void cpuThreadsChanged();
    void cpuFrequencyChanged();

    void memoryUsedChanged();
    void memoryAvailableChanged();
    void memoryTotalChanged();

    void swapUsedChanged();
    void swapTotalChanged();

    void diskUsedChanged();
    void diskFreeChanged();
    void diskTotalChanged();

    void uptimeChanged();
    void operatingSystemChanged();
    void kernelVersionChanged();
    void architectureChanged();

private:
    double m_cpuUsage = 0.0;
    int m_cpuThreads = 0;
    double m_cpuFrequency = 0.0;

    qint64 m_memoryUsed = 0;
    qint64 m_memoryAvailable = 0;
    qint64 m_memoryTotal = 0;

    qint64 m_swapUsed = 0;
    qint64 m_swapTotal = 0;

    qint64 m_diskUsed = 0;
    qint64 m_diskFree = 0;
    qint64 m_diskTotal = 0;

    qint64 m_uptime = 0;
    QString m_operatingSystem;
    QString m_kernelVersion;
    QString m_architecture;
};

} // namespace bos::shell
