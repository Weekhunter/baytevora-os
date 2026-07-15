#include "boi/InstallationSummary.h"

namespace boi {

InstallationSummary::InstallationSummary(QObject *parent)
    : QObject(parent)
{
}

QString InstallationSummary::targetDisk() const { return m_targetDisk; }
void InstallationSummary::setTargetDisk(const QString &value)
{
    if (m_targetDisk == value) return;
    m_targetDisk = value;
    emit targetDiskChanged();
}

QString InstallationSummary::diskCapacity() const { return m_diskCapacity; }
void InstallationSummary::setDiskCapacity(const QString &value)
{
    if (m_diskCapacity == value) return;
    m_diskCapacity = value;
    emit diskCapacityChanged();
}

QString InstallationSummary::requiredSpace() const { return m_requiredSpace; }
void InstallationSummary::setRequiredSpace(const QString &value)
{
    if (m_requiredSpace == value) return;
    m_requiredSpace = value;
    emit requiredSpaceChanged();
}

QString InstallationSummary::installationType() const { return m_installationType; }
void InstallationSummary::setInstallationType(const QString &value)
{
    if (m_installationType == value) return;
    m_installationType = value;
    emit installationTypeChanged();
}

QString InstallationSummary::language() const { return m_language; }
void InstallationSummary::setLanguage(const QString &value)
{
    if (m_language == value) return;
    m_language = value;
    emit languageChanged();
}

QString InstallationSummary::keyboard() const { return m_keyboard; }
void InstallationSummary::setKeyboard(const QString &value)
{
    if (m_keyboard == value) return;
    m_keyboard = value;
    emit keyboardChanged();
}

} // namespace boi
