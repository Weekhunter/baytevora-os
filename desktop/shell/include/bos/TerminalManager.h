#pragma once

#include <memory>

#include <QDateTime>
#include <QList>
#include <QObject>
#include <QString>

#include "bos/TerminalSession.h"

namespace bos::shell {

/**
 * @brief Command processor and output buffer for one Terminal window.
 *
 * TerminalManager owns a single TerminalSession and manages the on-screen text
 * buffer. It implements a small set of built-in commands internally and logs
 * all input. External process execution, shell integration, and other forbidden
 * features are intentionally absent.
 *
 * Each TerminalWindow.qml instantiates its own TerminalManager so multiple
 * terminal windows remain isolated.
 */
class TerminalManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString output READ output NOTIFY outputChanged)
    Q_PROPERTY(int lineCount READ lineCount NOTIFY lineCountChanged)
    Q_PROPERTY(QString currentDirectory READ currentDirectory NOTIFY currentDirectoryChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(TerminalSession *session READ session CONSTANT)

public:
    explicit TerminalManager(QObject *parent = nullptr);
    ~TerminalManager() override;

    QString output() const;
    int lineCount() const;
    QString currentDirectory() const;
    QString status() const;
    TerminalSession *session() const;

    Q_INVOKABLE void executeCommand(const QString &command);
    Q_INVOKABLE void newSession();
    Q_INVOKABLE void clearOutput();

signals:
    void outputChanged();
    void lineCountChanged();
    void currentDirectoryChanged();
    void statusChanged();

private:
    void appendLine(const QString &line);
    void appendOutput(const QString &text);
    void appendPrompt();
    void processCommand(const QString &command);
    void processBuiltIn(const QString &command, const QStringList &args);
    void handleUnknownCommand(const QString &command);
    void setStatus(const QString &status);

    QString m_output;
    QList<QString> m_lines;
    QString m_status;
    std::unique_ptr<TerminalSession> m_session;
};

} // namespace bos::shell
