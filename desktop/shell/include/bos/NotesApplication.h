#pragma once

#include <QObject>
#include <QStringList>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Notes application for BOS.
 *
 * NotesApplication requests a managed window from WindowManager and loads the
 * NotesWindow QML scene. Multiple notes windows can be opened. It also accepts
 * requests to open .bnote files from the File Manager.
 */
class NotesApplication : public QObject {
    Q_OBJECT

    Q_PROPERTY(QStringList pendingOpenFiles READ pendingOpenFiles NOTIFY pendingOpenFilesChanged)

public:
    explicit NotesApplication(QObject *parent = nullptr);
    ~NotesApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE int open();
    Q_INVOKABLE int openFile(const QString &filePath);

    QStringList pendingOpenFiles() const;
    Q_INVOKABLE QString takePendingOpenFile();

signals:
    void pendingOpenFilesChanged();

private:
    int doOpen();

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    QStringList m_pendingOpenFiles;
};

} // namespace bos::shell
