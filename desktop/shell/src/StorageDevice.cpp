#include "bos/StorageDevice.h"

namespace bos::shell {

StorageDevice::StorageDevice(QObject *parent)
    : QObject(parent)
{
}

QString StorageDevice::deviceName() const { return m_deviceName; }
QString StorageDevice::displayName() const { return m_displayName; }
QString StorageDevice::deviceType() const { return m_deviceType; }
QString StorageDevice::model() const { return m_model; }
QString StorageDevice::serialNumber() const { return m_serialNumber; }
qint64 StorageDevice::capacity() const { return m_capacity; }
bool StorageDevice::removable() const { return m_removable; }
bool StorageDevice::mounted() const { return m_mounted; }

void StorageDevice::setDeviceName(const QString &value)
{
    if (m_deviceName == value) {
        return;
    }
    m_deviceName = value;
    emit deviceNameChanged();
}

void StorageDevice::setDisplayName(const QString &value)
{
    if (m_displayName == value) {
        return;
    }
    m_displayName = value;
    emit displayNameChanged();
}

void StorageDevice::setDeviceType(const QString &value)
{
    if (m_deviceType == value) {
        return;
    }
    m_deviceType = value;
    emit deviceTypeChanged();
}

void StorageDevice::setModel(const QString &value)
{
    if (m_model == value) {
        return;
    }
    m_model = value;
    emit modelChanged();
}

void StorageDevice::setSerialNumber(const QString &value)
{
    if (m_serialNumber == value) {
        return;
    }
    m_serialNumber = value;
    emit serialNumberChanged();
}

void StorageDevice::setCapacity(qint64 value)
{
    if (m_capacity == value) {
        return;
    }
    m_capacity = value;
    emit capacityChanged();
}

void StorageDevice::setRemovable(bool value)
{
    if (m_removable == value) {
        return;
    }
    m_removable = value;
    emit removableChanged();
}

void StorageDevice::setMounted(bool value)
{
    if (m_mounted == value) {
        return;
    }
    m_mounted = value;
    emit mountedChanged();
}

} // namespace bos::shell
