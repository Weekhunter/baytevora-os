#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Archive Manager application for BOS.
 *
 * ArchiveApplication requests a managed window from WindowManager and loads
 * the ArchiveWindow QML scene. Multiple Archive Manager windows can be opened,
 * each with its own ArchiveManager.
 */
class ArchiveApplication : public QObject {
    Q_OBJECT

public:
    explicit ArchiveApplication(QObject *parent = nullptr);
    ~ArchiveApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Archive Manager window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

    /**
     * @brief Opens a new Archive Manager window with the given archive file.
     *
     * This method is provided for future File Manager integration.
     */
    Q_INVOKABLE int openArchive(const QString &path);

private:
    int openInternal(const QString &initialPath);

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
