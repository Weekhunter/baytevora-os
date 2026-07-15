#include "bos/TaskInfo.h"

namespace bos::shell {

TaskInfo::TaskInfo(QObject *parent)
    : QObject(parent)
{
}

int TaskInfo::processId() const { return m_processId; }
QString TaskInfo::applicationName() const { return m_applicationName; }
QString TaskInfo::executableName() const { return m_executableName; }
QString TaskInfo::state() const { return m_state; }
double TaskInfo::cpuUsage() const { return m_cpuUsage; }
qint64 TaskInfo::memoryUsage() const { return m_memoryUsage; }
QString TaskInfo::startTime() const { return m_startTime; }
int TaskInfo::windowCount() const { return m_windowCount; }

void TaskInfo::setProcessId(int id)
{
    if (m_processId == id) {
        return;
    }
    m_processId = id;
    emit processIdChanged();
}

void TaskInfo::setApplicationName(const QString &name)
{
    if (m_applicationName == name) {
        return;
    }
    m_applicationName = name;
    emit applicationNameChanged();
}

void TaskInfo::setExecutableName(const QString &name)
{
    if (m_executableName == name) {
        return;
    }
    m_executableName = name;
    emit executableNameChanged();
}

void TaskInfo::setState(const QString &state)
{
    if (m_state == state) {
        return;
    }
    m_state = state;
    emit stateChanged();
}

void TaskInfo::setCpuUsage(double usage)
{
    if (qFuzzyCompare(m_cpuUsage, usage)) {
        return;
    }
    m_cpuUsage = usage;
    emit cpuUsageChanged();
}

void TaskInfo::setMemoryUsage(qint64 usage)
{
    if (m_memoryUsage == usage) {
        return;
    }
    m_memoryUsage = usage;
    emit memoryUsageChanged();
}

void TaskInfo::setStartTime(const QString &time)
{
    if (m_startTime == time) {
        return;
    }
    m_startTime = time;
    emit startTimeChanged();
}

void TaskInfo::setWindowCount(int count)
{
    if (m_windowCount == count) {
        return;
    }
    m_windowCount = count;
    emit windowCountChanged();
}

} // namespace bos::shell
