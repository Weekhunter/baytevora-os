#include "bos/PrintManager.h"

#include <QDebug>
#include <QFileInfo>
#include <QPrinter>
#include <QPrinterInfo>

#include "bos/NotificationManager.h"
#include "bos/PrinterInfo.h"
#include "bos/PrintJob.h"

namespace bos::shell {

PrintManager::PrintManager(QObject *parent)
    : QObject(parent)
{
    updatePrinters();
}

PrintManager::~PrintManager()
{
    qDeleteAll(m_printers);
    m_printers.clear();
    qDeleteAll(m_jobs);
    m_jobs.clear();
}

QVariantList PrintManager::printers() const
{
    QVariantList list;
    list.reserve(m_printers.size());
    for (PrinterInfo *printer : m_printers) {
        if (!printer) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("printerName"), printer->printerName());
        map.insert(QStringLiteral("displayName"), printer->displayName());
        map.insert(QStringLiteral("manufacturer"), printer->manufacturer());
        map.insert(QStringLiteral("model"), printer->model());
        map.insert(QStringLiteral("location"), printer->location());
        map.insert(QStringLiteral("status"), printer->status());
        map.insert(QStringLiteral("online"), printer->online());
        map.insert(QStringLiteral("defaultPrinter"), printer->defaultPrinter());
        map.insert(QStringLiteral("colorSupported"), printer->colorSupported());
        map.insert(QStringLiteral("duplexSupported"), printer->duplexSupported());
        list.append(map);
    }
    return list;
}

QVariantList PrintManager::jobs() const
{
    QVariantList list;
    list.reserve(m_jobs.size());
    for (PrintJob *job : m_jobs) {
        if (!job) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("jobId"), job->jobId());
        map.insert(QStringLiteral("documentName"), job->documentName());
        map.insert(QStringLiteral("printerName"), job->printerName());
        map.insert(QStringLiteral("pages"), job->pages());
        map.insert(QStringLiteral("status"), job->status());
        map.insert(QStringLiteral("submittedTime"), job->submittedTime());
        list.append(map);
    }
    return list;
}

void PrintManager::refreshPrinters()
{
    updatePrinters();
    emit printersChanged();
}

void PrintManager::refreshJobs()
{
    emit jobsChanged();
}

bool PrintManager::printDocument(const QString &filePath)
{
    const QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qWarning() << QStringLiteral("[BDE] PrintManager: file not found:") << filePath;
        emitNotification(QStringLiteral("Print Error"),
                       QStringLiteral("Document not found: %1").arg(filePath));
        return false;
    }

    const QString suffix = fileInfo.suffix().toLower();
    const bool supported = (suffix == QStringLiteral("pdf"))
                           || (suffix == QStringLiteral("txt"))
                           || (suffix == QStringLiteral("png"))
                           || (suffix == QStringLiteral("jpg"))
                           || (suffix == QStringLiteral("jpeg"));
    if (!supported) {
        qWarning() << QStringLiteral("[BDE] PrintManager: unsupported file type:") << suffix;
        emitNotification(QStringLiteral("Print Error"),
                       QStringLiteral("Unsupported file type: %1").arg(suffix));
        return false;
    }

    QString printerName;
    for (PrinterInfo *printer : m_printers) {
        if (printer && printer->defaultPrinter()) {
            printerName = printer->printerName();
            break;
        }
    }
    if (printerName.isEmpty() && !m_printers.isEmpty()) {
        printerName = m_printers.first()->printerName();
    }
    if (printerName.isEmpty()) {
        printerName = QStringLiteral("None");
    }

    // Sprint 40: jobs are managed in memory and do not perform real
    // printing. A future sprint can wire this to platform print APIs.
    constexpr int placeholderPages = 1;
    submitJob(filePath, printerName, placeholderPages);
    emitNotification(QStringLiteral("Print Job Submitted"),
                   fileInfo.fileName());
    return true;
}

bool PrintManager::cancelJob(int jobId)
{
    for (int i = 0; i < m_jobs.size(); ++i) {
        PrintJob *job = m_jobs.at(i);
        if (job && job->jobId() == jobId) {
            job->setStatus(QStringLiteral("Cancelled"));
            emit jobsChanged();
            emitNotification(QStringLiteral("Print Job Cancelled"),
                           QStringLiteral("Job %1 cancelled.").arg(jobId));
            return true;
        }
    }
    return false;
}

bool PrintManager::setDefaultPrinter(const QString &printerName)
{
    bool changed = false;
    for (PrinterInfo *printer : m_printers) {
        if (!printer) {
            continue;
        }
        const bool shouldBeDefault = (printer->printerName() == printerName);
        if (printer->defaultPrinter() != shouldBeDefault) {
            printer->setDefaultPrinter(shouldBeDefault);
            changed = true;
        }
    }
    if (changed) {
        emit printersChanged();
    }
    return changed;
}

void PrintManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

void PrintManager::updatePrinters()
{
    qDeleteAll(m_printers);
    m_printers.clear();

    const QList<QPrinterInfo> printerInfoList = QPrinterInfo::availablePrinters();
    const QPrinterInfo defaultInfo = QPrinterInfo::defaultPrinter();

    if (printerInfoList.isEmpty()) {
        // Placeholder-safe behavior: present a virtual printer so the UI
        // remains functional when no real printer is configured.
        auto *printer = new PrinterInfo(this);
        printer->setPrinterName(QStringLiteral("virtual"));
        printer->setDisplayName(QStringLiteral("Virtual Printer"));
        printer->setManufacturer(QStringLiteral("Baytevora"));
        printer->setModel(QStringLiteral("Generic PostScript"));
        printer->setLocation(QStringLiteral("Local"));
        printer->setStatus(QStringLiteral("Idle"));
        printer->setOnline(true);
        printer->setDefaultPrinter(true);
        printer->setColorSupported(true);
        printer->setDuplexSupported(false);
        m_printers.append(printer);
        return;
    }

    for (const QPrinterInfo &info : printerInfoList) {
        auto *printer = new PrinterInfo(this);
        printer->setPrinterName(info.printerName());
        printer->setDisplayName(info.description().isEmpty()
                                ? info.printerName()
                                : info.description());
        printer->setManufacturer(QStringLiteral("Unknown"));
        printer->setModel(QStringLiteral("Unknown"));
        printer->setLocation(QStringLiteral("Local"));
        printer->setStatus(info.isNull() ? QStringLiteral("Offline") : QStringLiteral("Idle"));
        printer->setOnline(!info.isNull());
        printer->setDefaultPrinter(info.printerName() == defaultInfo.printerName());
        printer->setColorSupported(info.isNull() ? false : info.defaultColorMode() != QPrinter::GrayScale);
        printer->setDuplexSupported(info.isNull() ? false : true);
        m_printers.append(printer);
    }
}

void PrintManager::submitJob(const QString &filePath, const QString &printerName, int pages)
{
    const QFileInfo fileInfo(filePath);

    auto *job = new PrintJob(this);
    job->setJobId(nextJobId());
    job->setDocumentName(fileInfo.fileName());
    job->setPrinterName(printerName);
    job->setPages(pages);
    job->setStatus(QStringLiteral("Completed"));
    job->setSubmittedTime(QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss")));

    m_jobs.append(job);
    emit jobsChanged();
    emitNotification(QStringLiteral("Print Job Completed"), fileInfo.fileName());
}

void PrintManager::emitNotification(const QString &title, const QString &message)
{
    if (!m_notificationManager) {
        return;
    }
    m_notificationManager->createNotification(title, message,
                                              QStringLiteral("Print Manager"),
                                              QStringLiteral("info"));
}

int PrintManager::nextJobId() const
{
    int maxId = 0;
    for (const PrintJob *job : m_jobs) {
        if (job && job->jobId() > maxId) {
            maxId = job->jobId();
        }
    }
    return maxId + 1;
}

} // namespace bos::shell
