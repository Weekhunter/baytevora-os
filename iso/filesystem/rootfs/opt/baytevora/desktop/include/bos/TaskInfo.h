#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents one running application task in the Task Manager.
 */
class TaskInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(int processId READ processId NOTIFY processIdChanged FINAL)
    Q_PROPERTY(QString applicationName READ applicationName NOTIFY applicationNameChanged FINAL)
    Q_PROPERTY(QString executableName READ executableName NOTIFY executableNameChanged FINAL)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged FINAL)
    Q_PROPERTY(qint64 memoryUsage READ memoryUsage NOTIFY memoryUsageChanged FINAL)
    Q_PROPERTY(QString startTime READ startTime NOTIFY startTimeChanged FINAL)
    Q_PROPERTY(int windowCount READ windowCount NOTIFY windowCountChanged FINAL)

public:
    explicit TaskInfo(QObject *parent = nullptr);

    int processId() const;
    QString applicationName() const;
    QString executableName() const;
    QString state() const;
    double cpuUsage() const;
    qint64 memoryUsage() const;
    QString startTime() const;
    int windowCount() const;

    void setProcessId(int id);
    void setApplicationName(const QString &name);
    void setExecutableName(const QString &name);
    void setState(const QString &state);
    void setCpuUsage(double usage);
    void setMemoryUsage(qint64 usage);
    void setStartTime(const QString &time);
    void setWindowCount(int count);

signals:
    void processIdChanged();
    void applicationNameChanged();
    void executableNameChanged();
    void stateChanged();
    void cpuUsageChanged();
    void memoryUsageChanged();
    void startTimeChanged();
    void windowCountChanged();

private:
    int m_processId = -1;
    QString m_applicationName;
    QString m_executableName;
    QString m_state;
    double m_cpuUsage = 0.0;
    qint64 m_memoryUsage = 0;
    QString m_startTime;
    int m_windowCount = 0;
};

} // namespace bos::shell
