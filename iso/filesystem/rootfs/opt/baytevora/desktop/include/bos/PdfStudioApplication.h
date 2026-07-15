#pragma once

#include <QObject>
#include <QStringList>

namespace bos::shell {

class NotificationManager;
class PrintApplication;
class WindowManager;

/**
 * @brief Native Baytevora PDF Studio application for BOS.
 *
 * PdfStudioApplication requests managed windows from WindowManager and loads
 * the PdfStudioWindow QML scene. Multiple PDF Studio windows can be opened,
 * each with its own PdfStudioManager. It also exposes a pending-file queue so
 * File Manager can open a PDF in a new window.
 */
class PdfStudioApplication : public QObject {
    Q_OBJECT

public:
    explicit PdfStudioApplication(QObject *parent = nullptr);
    ~PdfStudioApplication() override;

    void setWindowManager(WindowManager *windowManager);
    void setNotificationManager(NotificationManager *notificationManager);
    void setPrintApplication(PrintApplication *printApplication);

    Q_INVOKABLE int open();
    Q_INVOKABLE int openFile(const QString &filePath);

    Q_INVOKABLE bool hasPendingOpenFile() const;
    Q_INVOKABLE QString takePendingOpenFile();

private:
    int doOpen();

    WindowManager *m_windowManager = nullptr;
    NotificationManager *m_notificationManager = nullptr;
    PrintApplication *m_printApplication = nullptr;
    QStringList m_pendingOpenFiles;
};

} // namespace bos::shell
