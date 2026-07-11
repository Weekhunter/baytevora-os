#include "bos/TerminalManager.h"

#include <QDebug>
#include <QDir>
#include <QLocale>

#include "bos/TerminalSession.h"

namespace bos::shell {

TerminalManager::TerminalManager(QObject *parent)
    : QObject(parent)
    , m_status(QStringLiteral("Ready"))
    , m_session(std::make_unique<TerminalSession>())
{
    connect(m_session.get(), &TerminalSession::currentDirectoryChanged,
            this, &TerminalManager::currentDirectoryChanged);

    appendOutput(QStringLiteral("Baytevora Terminal\nType 'help' for available commands.\n\n"));
    appendPrompt();
}

TerminalManager::~TerminalManager() = default;

QString TerminalManager::output() const
{
    return m_output;
}

int TerminalManager::lineCount() const
{
    return m_lines.size();
}

QString TerminalManager::currentDirectory() const
{
    return m_session->currentDirectory();
}

QString TerminalManager::status() const
{
    return m_status;
}

TerminalSession *TerminalManager::session() const
{
    return m_session.get();
}

void TerminalManager::executeCommand(const QString &command)
{
    qDebug() << QStringLiteral("[BDE] Command received:") << command;

    const QString trimmed = command.trimmed();

    appendLine(m_session->prompt() + QLatin1Char(' ') + trimmed);

    if (trimmed.isEmpty()) {
        appendPrompt();
        return;
    }

    processCommand(trimmed);
    appendPrompt();
}

void TerminalManager::newSession()
{
    qDebug() << QStringLiteral("[BDE] New session requested");
    setStatus(QStringLiteral("Ready"));
}

void TerminalManager::clearOutput()
{
    qDebug() << QStringLiteral("[BDE] Terminal output cleared");
    m_lines.clear();
    m_output.clear();
    appendOutput(QStringLiteral("Baytevora Terminal\nType 'help' for available commands.\n\n"));
    appendPrompt();
    emit outputChanged();
    emit lineCountChanged();
    setStatus(QStringLiteral("Terminal cleared"));
}

void TerminalManager::appendLine(const QString &line)
{
    m_output.append(line + QLatin1Char('\n'));
    m_lines.append(line);
    emit outputChanged();
    emit lineCountChanged();
}

void TerminalManager::appendOutput(const QString &text)
{
    const QStringList split = text.split(QLatin1Char('\n'));
    for (const QString &line : split) {
        m_lines.append(line);
    }

    m_output.append(text);
    emit outputChanged();
    emit lineCountChanged();
}

void TerminalManager::appendPrompt()
{
    appendLine(m_session->prompt());
}

void TerminalManager::processCommand(const QString &command)
{
    const QStringList parts = command.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (parts.isEmpty()) {
        return;
    }

    const QString name = parts.first();
    const QStringList args = parts.mid(1);

    const QStringList builtIns = {
        QStringLiteral("help"),
        QStringLiteral("clear"),
        QStringLiteral("version"),
        QStringLiteral("date"),
        QStringLiteral("pwd")
    };

    if (builtIns.contains(name)) {
        processBuiltIn(name, args);
    } else {
        handleUnknownCommand(name);
    }
}

void TerminalManager::processBuiltIn(const QString &command, const QStringList &args)
{
    Q_UNUSED(args)

    if (command == QStringLiteral("help")) {
        appendOutput(QStringLiteral("Available commands:\n"
                                    "  help    - Show this help message\n"
                                    "  clear   - Clear the terminal screen\n"
                                    "  version - Show BOS version\n"
                                    "  date    - Show current date and time\n"
                                    "  pwd     - Show current working directory\n\n"));
    } else if (command == QStringLiteral("clear")) {
        m_output.clear();
        m_lines.clear();
        emit outputChanged();
        emit lineCountChanged();
    } else if (command == QStringLiteral("version")) {
        appendOutput(QStringLiteral("Baytevora OS Terminal 0.14.0\n\n"));
    } else if (command == QStringLiteral("date")) {
        appendOutput(QLocale::system().toString(QDateTime::currentDateTime(),
                                                QLocale::LongFormat)
                     + QStringLiteral("\n\n"));
    } else if (command == QStringLiteral("pwd")) {
        appendOutput(m_session->currentDirectory() + QStringLiteral("\n\n"));
    }
}

void TerminalManager::handleUnknownCommand(const QString &command)
{
    Q_UNUSED(command)
    appendOutput(QStringLiteral("Command execution is not implemented yet.\n\n"));
}

void TerminalManager::setStatus(const QString &status)
{
    if (m_status == status) {
        return;
    }

    m_status = status;
    emit statusChanged();
}

} // namespace bos::shell
