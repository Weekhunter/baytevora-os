#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Describes a discovered printer in the Printing Framework.
 */
class PrinterInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString printerName READ printerName NOTIFY printerNameChanged FINAL)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged FINAL)
    Q_PROPERTY(QString manufacturer READ manufacturer NOTIFY manufacturerChanged FINAL)
    Q_PROPERTY(QString model READ model NOTIFY modelChanged FINAL)
    Q_PROPERTY(QString location READ location NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged FINAL)
    Q_PROPERTY(bool online READ online NOTIFY onlineChanged FINAL)
    Q_PROPERTY(bool defaultPrinter READ defaultPrinter NOTIFY defaultPrinterChanged FINAL)
    Q_PROPERTY(bool colorSupported READ colorSupported NOTIFY colorSupportedChanged FINAL)
    Q_PROPERTY(bool duplexSupported READ duplexSupported NOTIFY duplexSupportedChanged FINAL)

public:
    explicit PrinterInfo(QObject *parent = nullptr);

    QString printerName() const;
    QString displayName() const;
    QString manufacturer() const;
    QString model() const;
    QString location() const;
    QString status() const;
    bool online() const;
    bool defaultPrinter() const;
    bool colorSupported() const;
    bool duplexSupported() const;

    void setPrinterName(const QString &value);
    void setDisplayName(const QString &value);
    void setManufacturer(const QString &value);
    void setModel(const QString &value);
    void setLocation(const QString &value);
    void setStatus(const QString &value);
    void setOnline(bool value);
    void setDefaultPrinter(bool value);
    void setColorSupported(bool value);
    void setDuplexSupported(bool value);

signals:
    void printerNameChanged();
    void displayNameChanged();
    void manufacturerChanged();
    void modelChanged();
    void locationChanged();
    void statusChanged();
    void onlineChanged();
    void defaultPrinterChanged();
    void colorSupportedChanged();
    void duplexSupportedChanged();

private:
    QString m_printerName;
    QString m_displayName;
    QString m_manufacturer;
    QString m_model;
    QString m_location;
    QString m_status;
    bool m_online = false;
    bool m_defaultPrinter = false;
    bool m_colorSupported = false;
    bool m_duplexSupported = false;
};

} // namespace bos::shell
