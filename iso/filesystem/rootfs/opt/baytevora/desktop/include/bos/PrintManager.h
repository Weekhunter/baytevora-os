#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class NotificationManager;
class PrinterInfo;
class PrintJob;

/**
 * @brief Manages printer discovery and print jobs for the Printing Framework.
 *
 * PrintManager uses Qt Print Support for printer discovery. Jobs are managed
 * in memory and support placeholder-safe submission and cancellation.
 */
class PrintManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList printers READ printers NOTIFY printersChanged FINAL)
    Q_PROPERTY(QVariantList jobs READ jobs NOTIFY jobsChanged FINAL)

public:
    explicit PrintManager(QObject *parent = nullptr);
    ~PrintManager() override;

    QVariantList printers() const;
    QVariantList jobs() const;

    Q_INVOKABLE void refreshPrinters();
    Q_INVOKABLE void refreshJobs();
    Q_INVOKABLE bool printDocument(const QString &filePath);
    Q_INVOKABLE bool cancelJob(int jobId);
    Q_INVOKABLE bool setDefaultPrinter(const QString &printerName);

    void setNotificationManager(NotificationManager *notificationManager);

signals:
    void printersChanged();
    void jobsChanged();

private:
    void updatePrinters();
    void submitJob(const QString &filePath, const QString &printerName, int pages);
    void emitNotification(const QString &title, const QString &message);
    int nextJobId() const;

    QList<PrinterInfo*> m_printers;
    QList<PrintJob*> m_jobs;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
