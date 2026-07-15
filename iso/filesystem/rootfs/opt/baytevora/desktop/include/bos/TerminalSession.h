#pragma once

#include <QDir>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Session data model for one Terminal window.
 *
 * TerminalSession holds the per-window identity and working directory. It does
 * not run external commands; it only provides the prompt prefix and directory
 * state that the UI displays.
 */
class TerminalSession : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName CONSTANT)
    Q_PROPERTY(QString hostName READ hostName CONSTANT)
    Q_PROPERTY(QString currentDirectory READ currentDirectory WRITE setCurrentDirectory NOTIFY currentDirectoryChanged)
    Q_PROPERTY(QString prompt READ prompt NOTIFY currentDirectoryChanged)

public:
    explicit TerminalSession(QObject *parent = nullptr);
    ~TerminalSession() override;

    QString userName() const;
    QString hostName() const;
    QString currentDirectory() const;
    void setCurrentDirectory(const QString &path);
    QString prompt() const;

signals:
    void currentDirectoryChanged();

private:
    QString m_userName;
    QString m_hostName;
    QString m_currentDirectory;
};

} // namespace bos::shell
