#pragma once

#include <QList>
#include <QObject>
#include <QTimer>
#include <QVariantList>

namespace bos::shell {

class StorageDevice;
class StoragePartition;

/**
 * @brief Manages storage devices and partitions for the Storage Manager.
 *
 * StorageManager refreshes every five seconds from Linux sysfs and mount
 * information. All operations are read-only in Sprint 39.
 */
class StorageManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList devices READ devices NOTIFY devicesChanged FINAL)
    Q_PROPERTY(QVariantList partitions READ partitions NOTIFY partitionsChanged FINAL)

public:
    explicit StorageManager(QObject *parent = nullptr);
    ~StorageManager() override;

    QVariantList devices() const;
    QVariantList partitions() const;

    Q_INVOKABLE void refresh();
    Q_INVOKABLE void startMonitoring();
    Q_INVOKABLE void stopMonitoring();

signals:
    void devicesChanged();
    void partitionsChanged();

private:
    void updateDevices();
    void updatePartitions();
    void clearModel();
    QString deviceTypeFromName(const QString &name) const;
    qint64 readSysfsSize(const QString &path) const;
    QString readSysfsString(const QString &path) const;
    QString formatBytes(qint64 bytes) const;

    QList<StorageDevice*> m_devices;
    QList<StoragePartition*> m_partitions;
    QTimer *m_timer = nullptr;
};

} // namespace bos::shell
