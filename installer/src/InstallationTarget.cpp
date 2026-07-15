#include "boi/InstallationTarget.h"

#include <QLocale>

namespace boi {

InstallationTarget::InstallationTarget(QObject *parent)
    : QObject(parent)
{
}

QString InstallationTarget::diskId() const { return m_diskId; }
void InstallationTarget::setDiskId(const QString &value)
{
    if (m_diskId == value) return;
    m_diskId = value;
    emit diskIdChanged();
}

QString InstallationTarget::diskName() const { return m_diskName; }
void InstallationTarget::setDiskName(const QString &value)
{
    if (m_diskName == value) return;
    m_diskName = value;
    emit diskNameChanged();
}

QString InstallationTarget::model() const { return m_model; }
void InstallationTarget::setModel(const QString &value)
{
    if (m_model == value) return;
    m_model = value;
    emit modelChanged();
}

QString InstallationTarget::filesystem() const { return m_filesystem; }
void InstallationTarget::setFilesystem(const QString &value)
{
    if (m_filesystem == value) return;
    m_filesystem = value;
    emit filesystemChanged();
}

qint64 InstallationTarget::capacityBytes() const { return m_capacityBytes; }
void InstallationTarget::setCapacityBytes(qint64 value)
{
    if (m_capacityBytes == value) return;
    m_capacityBytes = value;
    emit capacityBytesChanged();
    emit capacityTextChanged();
}

QString InstallationTarget::capacityText() const
{
    return QLocale::system().formattedDataSize(m_capacityBytes);
}

bool InstallationTarget::removable() const { return m_removable; }
void InstallationTarget::setRemovable(bool value)
{
    if (m_removable == value) return;
    m_removable = value;
    emit removableChanged();
}

bool InstallationTarget::valid() const { return m_valid; }
void InstallationTarget::setValid(bool value)
{
    if (m_valid == value) return;
    m_valid = value;
    emit validChanged();
}

} // namespace boi
