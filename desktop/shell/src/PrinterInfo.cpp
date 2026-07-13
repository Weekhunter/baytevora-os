#include "bos/PrinterInfo.h"

namespace bos::shell {

PrinterInfo::PrinterInfo(QObject *parent)
    : QObject(parent)
{
}

QString PrinterInfo::printerName() const { return m_printerName; }
QString PrinterInfo::displayName() const { return m_displayName; }
QString PrinterInfo::manufacturer() const { return m_manufacturer; }
QString PrinterInfo::model() const { return m_model; }
QString PrinterInfo::location() const { return m_location; }
QString PrinterInfo::status() const { return m_status; }
bool PrinterInfo::online() const { return m_online; }
bool PrinterInfo::defaultPrinter() const { return m_defaultPrinter; }
bool PrinterInfo::colorSupported() const { return m_colorSupported; }
bool PrinterInfo::duplexSupported() const { return m_duplexSupported; }

void PrinterInfo::setPrinterName(const QString &value)
{
    if (m_printerName == value) {
        return;
    }
    m_printerName = value;
    emit printerNameChanged();
}

void PrinterInfo::setDisplayName(const QString &value)
{
    if (m_displayName == value) {
        return;
    }
    m_displayName = value;
    emit displayNameChanged();
}

void PrinterInfo::setManufacturer(const QString &value)
{
    if (m_manufacturer == value) {
        return;
    }
    m_manufacturer = value;
    emit manufacturerChanged();
}

void PrinterInfo::setModel(const QString &value)
{
    if (m_model == value) {
        return;
    }
    m_model = value;
    emit modelChanged();
}

void PrinterInfo::setLocation(const QString &value)
{
    if (m_location == value) {
        return;
    }
    m_location = value;
    emit locationChanged();
}

void PrinterInfo::setStatus(const QString &value)
{
    if (m_status == value) {
        return;
    }
    m_status = value;
    emit statusChanged();
}

void PrinterInfo::setOnline(bool value)
{
    if (m_online == value) {
        return;
    }
    m_online = value;
    emit onlineChanged();
}

void PrinterInfo::setDefaultPrinter(bool value)
{
    if (m_defaultPrinter == value) {
        return;
    }
    m_defaultPrinter = value;
    emit defaultPrinterChanged();
}

void PrinterInfo::setColorSupported(bool value)
{
    if (m_colorSupported == value) {
        return;
    }
    m_colorSupported = value;
    emit colorSupportedChanged();
}

void PrinterInfo::setDuplexSupported(bool value)
{
    if (m_duplexSupported == value) {
        return;
    }
    m_duplexSupported = value;
    emit duplexSupportedChanged();
}

} // namespace bos::shell
