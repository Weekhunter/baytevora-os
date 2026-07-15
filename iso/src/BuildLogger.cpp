#include "big/BuildLogger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>

namespace big {

BuildLogger::BuildLogger(QObject *parent)
    : QObject(parent)
{
}

void BuildLogger::logInfo(const QString &message)
{
    const QString line = formatLine(QStringLiteral("INFO"), message);
    m_logs.append(line);
    emit logAdded(line);
}

void BuildLogger::logWarning(const QString &message)
{
    const QString line = formatLine(QStringLiteral("WARN"), message);
    m_logs.append(line);
    emit logAdded(line);
}

void BuildLogger::logError(const QString &message)
{
    const QString line = formatLine(QStringLiteral("ERROR"), message);
    m_logs.append(line);
    emit logAdded(line);
}

QStringList BuildLogger::logs() const
{
    return m_logs;
}

QString BuildLogger::getLogs() const
{
    return m_logs.join(QStringLiteral("\n"));
}

bool BuildLogger::saveToFile(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    file.write(getLogs().toUtf8());
    return true;
}

QString BuildLogger::formatLine(const QString &level, const QString &message) const
{
    return QStringLiteral("%1 [%2] %3")
        .arg(QDateTime::currentDateTime().toString(Qt::ISODate))
        .arg(level)
        .arg(message);
}

} // namespace big
