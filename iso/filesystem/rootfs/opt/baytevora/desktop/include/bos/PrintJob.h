#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Describes a print job in the Printing Framework.
 */
class PrintJob : public QObject {
    Q_OBJECT

    Q_PROPERTY(int jobId READ jobId NOTIFY jobIdChanged FINAL)
    Q_PROPERTY(QString documentName READ documentName NOTIFY documentNameChanged FINAL)
    Q_PROPERTY(QString printerName READ printerName NOTIFY printerNameChanged FINAL)
    Q_PROPERTY(int pages READ pages NOTIFY pagesChanged FINAL)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged FINAL)
    Q_PROPERTY(QString submittedTime READ submittedTime NOTIFY submittedTimeChanged FINAL)

public:
    explicit PrintJob(QObject *parent = nullptr);

    int jobId() const;
    QString documentName() const;
    QString printerName() const;
    int pages() const;
    QString status() const;
    QString submittedTime() const;

    void setJobId(int value);
    void setDocumentName(const QString &value);
    void setPrinterName(const QString &value);
    void setPages(int value);
    void setStatus(const QString &value);
    void setSubmittedTime(const QString &value);

signals:
    void jobIdChanged();
    void documentNameChanged();
    void printerNameChanged();
    void pagesChanged();
    void statusChanged();
    void submittedTimeChanged();

private:
    int m_jobId = -1;
    QString m_documentName;
    QString m_printerName;
    int m_pages = 0;
    QString m_status;
    QString m_submittedTime;
};

} // namespace bos::shell
