#include "bos/StoragePartition.h"

namespace bos::shell {

StoragePartition::StoragePartition(QObject *parent)
    : QObject(parent)
{
}

QString StoragePartition::partitionName() const { return m_partitionName; }
QString StoragePartition::filesystem() const { return m_filesystem; }
QString StoragePartition::mountPoint() const { return m_mountPoint; }
qint64 StoragePartition::totalSpace() const { return m_totalSpace; }
qint64 StoragePartition::usedSpace() const { return m_usedSpace; }
qint64 StoragePartition::freeSpace() const { return m_freeSpace; }
int StoragePartition::usagePercent() const { return m_usagePercent; }
bool StoragePartition::readOnly() const { return m_readOnly; }

void StoragePartition::setPartitionName(const QString &value)
{
    if (m_partitionName == value) {
        return;
    }
    m_partitionName = value;
    emit partitionNameChanged();
}

void StoragePartition::setFilesystem(const QString &value)
{
    if (m_filesystem == value) {
        return;
    }
    m_filesystem = value;
    emit filesystemChanged();
}

void StoragePartition::setMountPoint(const QString &value)
{
    if (m_mountPoint == value) {
        return;
    }
    m_mountPoint = value;
    emit mountPointChanged();
}

void StoragePartition::setTotalSpace(qint64 value)
{
    if (m_totalSpace == value) {
        return;
    }
    m_totalSpace = value;
    emit totalSpaceChanged();
}

void StoragePartition::setUsedSpace(qint64 value)
{
    if (m_usedSpace == value) {
        return;
    }
    m_usedSpace = value;
    emit usedSpaceChanged();
}

void StoragePartition::setFreeSpace(qint64 value)
{
    if (m_freeSpace == value) {
        return;
    }
    m_freeSpace = value;
    emit freeSpaceChanged();
}

void StoragePartition::setUsagePercent(int value)
{
    if (m_usagePercent == value) {
        return;
    }
    m_usagePercent = value;
    emit usagePercentChanged();
}

void StoragePartition::setReadOnly(bool value)
{
    if (m_readOnly == value) {
        return;
    }
    m_readOnly = value;
    emit readOnlyChanged();
}

} // namespace bos::shell
