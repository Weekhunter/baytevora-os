#include "bos/SystemMonitorManager.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QSysInfo>
#include <QTextStream>
#include <QThread>

#include "bos/NotificationManager.h"
#include "bos/SystemInfo.h"

#include <sys/statvfs.h>

namespace bos::shell {

SystemMonitorManager::SystemMonitorManager(QObject *parent)
    : QObject(parent)
    , m_info(new SystemInfo(this))
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &SystemMonitorManager::refresh);
    refreshStaticInfo();
    refresh();
}

SystemMonitorManager::~SystemMonitorManager() = default;

SystemInfo *SystemMonitorManager::info() const
{
    return m_info;
}

void SystemMonitorManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void SystemMonitorManager::refresh()
{
    if (!m_info) {
        return;
    }

    refreshCpu();
    refreshMemory();
    refreshDisk();
    refreshUptime();
    refreshPlatform();
}

void SystemMonitorManager::startMonitoring()
{
    if (m_timer && !m_timer->isActive()) {
        m_timer->start(1000);
    }
}

void SystemMonitorManager::stopMonitoring()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}

void SystemMonitorManager::refreshCpu()
{
    if (!m_info) {
        return;
    }

    m_info->setCpuThreads(QThread::idealThreadCount());

    QFile file(QStringLiteral("/proc/stat"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream(&file);
    QString line = stream.readLine();
    file.close();

    const QStringList parts = line.split(QRegularExpression(QStringLiteral("\\s+")), Qt::SkipEmptyParts);
    if (parts.size() < 5 || !parts.first().startsWith(QStringLiteral("cpu"))) {
        return;
    }

    quint64 user = parts.at(1).toULongLong();
    quint64 nice = parts.at(2).toULongLong();
    quint64 system = parts.at(3).toULongLong();
    quint64 idle = parts.at(4).toULongLong();
    quint64 iowait = parts.size() > 5 ? parts.at(5).toULongLong() : 0;
    quint64 irq = parts.size() > 6 ? parts.at(6).toULongLong() : 0;
    quint64 softirq = parts.size() > 7 ? parts.at(7).toULongLong() : 0;
    quint64 steal = parts.size() > 8 ? parts.at(8).toULongLong() : 0;

    quint64 total = user + nice + system + idle + iowait + irq + softirq + steal;
    quint64 idleTime = idle + iowait;

    if (m_hasCpuBaseline) {
        quint64 totalDelta = total - m_lastCpuTotal;
        quint64 idleDelta = idleTime - m_lastCpuIdle;
        if (totalDelta > 0) {
            double usage = 100.0 * (static_cast<double>(totalDelta - idleDelta) / static_cast<double>(totalDelta));
            m_info->setCpuUsage(qBound(0.0, usage, 100.0));
        }
    }

    m_lastCpuTotal = total;
    m_lastCpuIdle = idleTime;
    m_hasCpuBaseline = true;

    // Try to read the first CPU frequency from /proc/cpuinfo.
    QFile cpuInfo(QStringLiteral("/proc/cpuinfo"));
    if (cpuInfo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream cpuStream(&cpuInfo);
        while (!cpuStream.atEnd()) {
            QString cpuLine = cpuStream.readLine();
            if (cpuLine.startsWith(QStringLiteral("cpu MHz"))) {
                QString value = cpuLine.section(':', 1).trimmed();
                m_info->setCpuFrequency(value.toDouble());
                break;
            }
        }
        cpuInfo.close();
    }
}

void SystemMonitorManager::refreshMemory()
{
    if (!m_info) {
        return;
    }

    QFile file(QStringLiteral("/proc/meminfo"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    qint64 memTotal = -1;
    qint64 memAvailable = -1;
    qint64 swapTotal = -1;
    qint64 swapFree = -1;

    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QString key = line.section(':', 0, 0).trimmed();
        QString value = line.section(':', 1).trimmed();
        value = value.section(' ', 0, 0).trimmed();
        qint64 kb = value.toLongLong();

        if (key == QStringLiteral("MemTotal")) {
            memTotal = kb * 1024;
        } else if (key == QStringLiteral("MemAvailable")) {
            memAvailable = kb * 1024;
        } else if (key == QStringLiteral("SwapTotal")) {
            swapTotal = kb * 1024;
        } else if (key == QStringLiteral("SwapFree")) {
            swapFree = kb * 1024;
        }
    }
    file.close();

    if (memTotal >= 0) {
        m_info->setMemoryTotal(memTotal);
    }
    if (memAvailable >= 0) {
        m_info->setMemoryAvailable(memAvailable);
    }
    if (memTotal >= 0 && memAvailable >= 0) {
        m_info->setMemoryUsed(memTotal - memAvailable);
    }

    if (swapTotal >= 0) {
        m_info->setSwapTotal(swapTotal);
    }
    if (swapTotal >= 0 && swapFree >= 0) {
        m_info->setSwapUsed(swapTotal - swapFree);
    }
}

void SystemMonitorManager::refreshDisk()
{
    if (!m_info) {
        return;
    }

    struct statvfs buf;
    if (statvfs("/", &buf) != 0) {
        return;
    }

    qint64 blockSize = buf.f_frsize;
    qint64 total = static_cast<qint64>(buf.f_blocks) * blockSize;
    qint64 free = static_cast<qint64>(buf.f_bfree) * blockSize;
    qint64 used = total - free;

    m_info->setDiskTotal(total);
    m_info->setDiskFree(free);
    m_info->setDiskUsed(used);
}

void SystemMonitorManager::refreshUptime()
{
    if (!m_info) {
        return;
    }

    QFile file(QStringLiteral("/proc/uptime"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream(&file);
    QString value = stream.readLine().section(' ', 0, 0).trimmed();
    file.close();

    bool ok = false;
    double seconds = value.toDouble(&ok);
    if (ok) {
        m_info->setUptime(static_cast<qint64>(seconds));
    }
}

void SystemMonitorManager::refreshPlatform()
{
    if (!m_info) {
        return;
    }

    m_info->setOperatingSystem(QSysInfo::prettyProductName());
    m_info->setKernelVersion(QSysInfo::kernelVersion());
    m_info->setArchitecture(QSysInfo::currentCpuArchitecture());
}

void SystemMonitorManager::refreshStaticInfo()
{
    refreshPlatform();
    m_info->setCpuThreads(QThread::idealThreadCount());
}

qint64 SystemMonitorManager::readProcValue(const QString &path, const QString &key) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.startsWith(key)) {
            QString value = line.section(':', 1).trimmed();
            value = value.section(' ', 0, 0).trimmed();
            file.close();
            return value.toLongLong() * 1024;
        }
    }
    file.close();
    return -1;
}

} // namespace bos::shell
