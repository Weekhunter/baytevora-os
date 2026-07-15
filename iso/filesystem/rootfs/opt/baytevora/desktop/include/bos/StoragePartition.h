#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single storage partition in the Storage Manager.
 */
class StoragePartition : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString partitionName READ partitionName NOTIFY partitionNameChanged FINAL)
    Q_PROPERTY(QString filesystem READ filesystem NOTIFY filesystemChanged FINAL)
    Q_PROPERTY(QString mountPoint READ mountPoint NOTIFY mountPointChanged FINAL)
    Q_PROPERTY(qint64 totalSpace READ totalSpace NOTIFY totalSpaceChanged FINAL)
    Q_PROPERTY(qint64 usedSpace READ usedSpace NOTIFY usedSpaceChanged FINAL)
    Q_PROPERTY(qint64 freeSpace READ freeSpace NOTIFY freeSpaceChanged FINAL)
    Q_PROPERTY(int usagePercent READ usagePercent NOTIFY usagePercentChanged FINAL)
    Q_PROPERTY(bool readOnly READ readOnly NOTIFY readOnlyChanged FINAL)

public:
    explicit StoragePartition(QObject *parent = nullptr);

    QString partitionName() const;
    QString filesystem() const;
    QString mountPoint() const;
    qint64 totalSpace() const;
    qint64 usedSpace() const;
    qint64 freeSpace() const;
    int usagePercent() const;
    bool readOnly() const;

    void setPartitionName(const QString &value);
    void setFilesystem(const QString &value);
    void setMountPoint(const QString &value);
    void setTotalSpace(qint64 value);
    void setUsedSpace(qint64 value);
    void setFreeSpace(qint64 value);
    void setUsagePercent(int value);
    void setReadOnly(bool value);

signals:
    void partitionNameChanged();
    void filesystemChanged();
    void mountPointChanged();
    void totalSpaceChanged();
    void usedSpaceChanged();
    void freeSpaceChanged();
    void usagePercentChanged();
    void readOnlyChanged();

private:
    QString m_partitionName;
    QString m_filesystem;
    QString m_mountPoint;
    qint64 m_totalSpace = 0;
    qint64 m_usedSpace = 0;
    qint64 m_freeSpace = 0;
    int m_usagePercent = 0;
    bool m_readOnly = false;
};

} // namespace bos::shell
