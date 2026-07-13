#include "bos/SystemInfo.h"

namespace bos::shell {

SystemInfo::SystemInfo(QObject *parent)
    : QObject(parent)
{
}

double SystemInfo::cpuUsage() const { return m_cpuUsage; }
int SystemInfo::cpuThreads() const { return m_cpuThreads; }
double SystemInfo::cpuFrequency() const { return m_cpuFrequency; }

qint64 SystemInfo::memoryUsed() const { return m_memoryUsed; }
qint64 SystemInfo::memoryAvailable() const { return m_memoryAvailable; }
qint64 SystemInfo::memoryTotal() const { return m_memoryTotal; }

qint64 SystemInfo::swapUsed() const { return m_swapUsed; }
qint64 SystemInfo::swapTotal() const { return m_swapTotal; }

qint64 SystemInfo::diskUsed() const { return m_diskUsed; }
qint64 SystemInfo::diskFree() const { return m_diskFree; }
qint64 SystemInfo::diskTotal() const { return m_diskTotal; }

qint64 SystemInfo::uptime() const { return m_uptime; }
QString SystemInfo::operatingSystem() const { return m_operatingSystem; }
QString SystemInfo::kernelVersion() const { return m_kernelVersion; }
QString SystemInfo::architecture() const { return m_architecture; }

void SystemInfo::setCpuUsage(double value)
{
    if (qFuzzyCompare(m_cpuUsage, value)) {
        return;
    }
    m_cpuUsage = value;
    emit cpuUsageChanged();
}

void SystemInfo::setCpuThreads(int value)
{
    if (m_cpuThreads == value) {
        return;
    }
    m_cpuThreads = value;
    emit cpuThreadsChanged();
}

void SystemInfo::setCpuFrequency(double value)
{
    if (qFuzzyCompare(m_cpuFrequency, value)) {
        return;
    }
    m_cpuFrequency = value;
    emit cpuFrequencyChanged();
}

void SystemInfo::setMemoryUsed(qint64 value)
{
    if (m_memoryUsed == value) {
        return;
    }
    m_memoryUsed = value;
    emit memoryUsedChanged();
}

void SystemInfo::setMemoryAvailable(qint64 value)
{
    if (m_memoryAvailable == value) {
        return;
    }
    m_memoryAvailable = value;
    emit memoryAvailableChanged();
}

void SystemInfo::setMemoryTotal(qint64 value)
{
    if (m_memoryTotal == value) {
        return;
    }
    m_memoryTotal = value;
    emit memoryTotalChanged();
}

void SystemInfo::setSwapUsed(qint64 value)
{
    if (m_swapUsed == value) {
        return;
    }
    m_swapUsed = value;
    emit swapUsedChanged();
}

void SystemInfo::setSwapTotal(qint64 value)
{
    if (m_swapTotal == value) {
        return;
    }
    m_swapTotal = value;
    emit swapTotalChanged();
}

void SystemInfo::setDiskUsed(qint64 value)
{
    if (m_diskUsed == value) {
        return;
    }
    m_diskUsed = value;
    emit diskUsedChanged();
}

void SystemInfo::setDiskFree(qint64 value)
{
    if (m_diskFree == value) {
        return;
    }
    m_diskFree = value;
    emit diskFreeChanged();
}

void SystemInfo::setDiskTotal(qint64 value)
{
    if (m_diskTotal == value) {
        return;
    }
    m_diskTotal = value;
    emit diskTotalChanged();
}

void SystemInfo::setUptime(qint64 value)
{
    if (m_uptime == value) {
        return;
    }
    m_uptime = value;
    emit uptimeChanged();
}

void SystemInfo::setOperatingSystem(const QString &value)
{
    if (m_operatingSystem == value) {
        return;
    }
    m_operatingSystem = value;
    emit operatingSystemChanged();
}

void SystemInfo::setKernelVersion(const QString &value)
{
    if (m_kernelVersion == value) {
        return;
    }
    m_kernelVersion = value;
    emit kernelVersionChanged();
}

void SystemInfo::setArchitecture(const QString &value)
{
    if (m_architecture == value) {
        return;
    }
    m_architecture = value;
    emit architectureChanged();
}

} // namespace bos::shell
