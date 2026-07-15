#include "bos/PrintJob.h"

namespace bos::shell {

PrintJob::PrintJob(QObject *parent)
    : QObject(parent)
{
}

int PrintJob::jobId() const { return m_jobId; }
QString PrintJob::documentName() const { return m_documentName; }
QString PrintJob::printerName() const { return m_printerName; }
int PrintJob::pages() const { return m_pages; }
QString PrintJob::status() const { return m_status; }
QString PrintJob::submittedTime() const { return m_submittedTime; }

void PrintJob::setJobId(int value)
{
    if (m_jobId == value) {
        return;
    }
    m_jobId = value;
    emit jobIdChanged();
}

void PrintJob::setDocumentName(const QString &value)
{
    if (m_documentName == value) {
        return;
    }
    m_documentName = value;
    emit documentNameChanged();
}

void PrintJob::setPrinterName(const QString &value)
{
    if (m_printerName == value) {
        return;
    }
    m_printerName = value;
    emit printerNameChanged();
}

void PrintJob::setPages(int value)
{
    if (m_pages == value) {
        return;
    }
    m_pages = value;
    emit pagesChanged();
}

void PrintJob::setStatus(const QString &value)
{
    if (m_status == value) {
        return;
    }
    m_status = value;
    emit statusChanged();
}

void PrintJob::setSubmittedTime(const QString &value)
{
    if (m_submittedTime == value) {
        return;
    }
    m_submittedTime = value;
    emit submittedTimeChanged();
}

} // namespace bos::shell
