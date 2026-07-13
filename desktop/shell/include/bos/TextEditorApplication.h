#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

class NotificationManager;
class WindowManager;

/**
 * @brief Native Baytevora Text Editor application for BOS.
 *
 * TextEditorApplication requests a managed window from WindowManager and loads
 * the TextEditorWindow QML scene. Multiple Text Editor windows can be opened,
 * each with its own TextEditorManager.
 */
class TextEditorApplication : public QObject {
    Q_OBJECT

public:
    explicit TextEditorApplication(QObject *parent = nullptr);
    ~TextEditorApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);

    /**
     * @brief Opens a new Text Editor window.
     * @return The window ID, or -1 on failure.
     */
    Q_INVOKABLE int open();

    /**
     * @brief Opens a new Text Editor window and loads the given file.
     *
     * This method is provided for future File Manager integration.
     */
    Q_INVOKABLE int openDocument(const QString &path);

private:
    int openInternal(const QString &initialPath);

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
