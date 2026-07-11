#include "bos/TerminalSession.h"

#include <QSysInfo>

namespace bos::shell {

TerminalSession::TerminalSession(QObject *parent)
    : QObject(parent)
{
    m_userName = QString::fromLocal8Bit(qgetenv("USER"));
    if (m_userName.isEmpty()) {
        m_userName = QStringLiteral("user");
    }

    m_hostName = QSysInfo::machineHostName();
    if (m_hostName.isEmpty()) {
        m_hostName = QStringLiteral("bos");
    }

    m_currentDirectory = QDir::homePath();
    if (m_currentDirectory.isEmpty()) {
        m_currentDirectory = QStringLiteral("/");
    }
}

TerminalSession::~TerminalSession() = default;

QString TerminalSession::userName() const
{
    return m_userName;
}

QString TerminalSession::hostName() const
{
    return m_hostName;
}

QString TerminalSession::currentDirectory() const
{
    return m_currentDirectory;
}

void TerminalSession::setCurrentDirectory(const QString &path)
{
    if (m_currentDirectory == path || path.isEmpty()) {
        return;
    }

    m_currentDirectory = QDir(path).absolutePath();
    emit currentDirectoryChanged();
}

QString TerminalSession::prompt() const
{
    QString displayDir = m_currentDirectory;
    const QString homePath = QDir::homePath();

    if (!homePath.isEmpty() && displayDir.startsWith(homePath)) {
        if (displayDir == homePath) {
            displayDir = QStringLiteral("~");
        } else {
            displayDir = QStringLiteral("~") + displayDir.mid(homePath.length());
        }
    }

    return m_userName + QStringLiteral("@") + m_hostName + QStringLiteral(":") + displayDir + QStringLiteral("$");
}

} // namespace bos::shell
