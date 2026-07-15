#include "bos/StorageManager.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

#include "bos/StorageDevice.h"
#include "bos/StoragePartition.h"

#include <sys/statvfs.h>

namespace bos::shell {

namespace {

struct MountInfo {
    QString device;
    QString mountPoint;
    QString filesystem;
    quint64 options;
};

QList<MountInfo> readProcMounts()
{
    QList<MountInfo> mounts;
    QFile file(QStringLiteral("/proc/mounts"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return mounts;
    }

    QTextStream stream(&file);
    while (!stream.atEnd()) {
        const QString line = stream.readLine();
        const QStringList parts = line.split(QRegularExpression(QStringLiteral("\\s+")), Qt::SkipEmptyParts);
        if (parts.size() < 4) {
            continue;
        }
        MountInfo info;
        info.device = parts.at(0);
        info.mountPoint = parts.at(1);
        info.filesystem = parts.at(2);
        info.options = 0; // options not used for Sprint 39
        mounts.append(info);
    }
    file.close();
    return mounts;
}

} // namespace

StorageManager::StorageManager(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &StorageManager::refresh);
    refresh();
}

StorageManager::~StorageManager()
{
    clearModel();
}

QVariantList StorageManager::devices() const
{
    QVariantList list;
    list.reserve(m_devices.size());
    for (StorageDevice *device : m_devices) {
        if (!device) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("deviceName"), device->deviceName());
        map.insert(QStringLiteral("displayName"), device->displayName());
        map.insert(QStringLiteral("deviceType"), device->deviceType());
        map.insert(QStringLiteral("model"), device->model());
        map.insert(QStringLiteral("serialNumber"), device->serialNumber());
        map.insert(QStringLiteral("capacity"), device->capacity());
        map.insert(QStringLiteral("capacityText"), formatBytes(device->capacity()));
        map.insert(QStringLiteral("removable"), device->removable());
        map.insert(QStringLiteral("mounted"), device->mounted());
        list.append(map);
    }
    return list;
}

QVariantList StorageManager::partitions() const
{
    QVariantList list;
    list.reserve(m_partitions.size());
    for (StoragePartition *partition : m_partitions) {
        if (!partition) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("partitionName"), partition->partitionName());
        map.insert(QStringLiteral("filesystem"), partition->filesystem());
        map.insert(QStringLiteral("mountPoint"), partition->mountPoint());
        map.insert(QStringLiteral("totalSpace"), partition->totalSpace());
        map.insert(QStringLiteral("totalSpaceText"), formatBytes(partition->totalSpace()));
        map.insert(QStringLiteral("usedSpace"), partition->usedSpace());
        map.insert(QStringLiteral("usedSpaceText"), formatBytes(partition->usedSpace()));
        map.insert(QStringLiteral("freeSpace"), partition->freeSpace());
        map.insert(QStringLiteral("freeSpaceText"), formatBytes(partition->freeSpace()));
        map.insert(QStringLiteral("usagePercent"), partition->usagePercent());
        map.insert(QStringLiteral("readOnly"), partition->readOnly());
        list.append(map);
    }
    return list;
}

void StorageManager::refresh()
{
    updateDevices();
    updatePartitions();
    emit devicesChanged();
    emit partitionsChanged();
}

void StorageManager::startMonitoring()
{
    if (m_timer && !m_timer->isActive()) {
        m_timer->start(5000);
    }
}

void StorageManager::stopMonitoring()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}

void StorageManager::updateDevices()
{
    qDeleteAll(m_devices);
    m_devices.clear();

    const QString sysBlock = QStringLiteral("/sys/block");
    QDir blockDir(sysBlock);
    const QStringList entries = blockDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    const QStringList mounts = [this]() {
        const auto infoList = readProcMounts();
        QStringList result;
        for (const auto &info : infoList) {
            result.append(info.device);
        }
        return result;
    }();

    for (const QString &name : entries) {
        if (name.startsWith(QLatin1Char('l')) && name.contains(QLatin1String("loop"))) {
            continue;
        }
        if (name == QStringLiteral("dm-")) {
            continue;
        }

        auto *device = new StorageDevice(this);
        device->setDeviceName(name);
        device->setDisplayName(name.toUpper());
        device->setDeviceType(deviceTypeFromName(name));
        device->setModel(readSysfsString(QStringLiteral("/sys/block/") + name + QStringLiteral("/device/model")));
        device->setSerialNumber(readSysfsString(QStringLiteral("/sys/block/") + name + QStringLiteral("/device/serial")));
        device->setRemovable(readSysfsString(QStringLiteral("/sys/block/") + name + QStringLiteral("/removable")) == QStringLiteral("1"));
        device->setCapacity(readSysfsSize(QStringLiteral("/sys/block/") + name + QStringLiteral("/size")) * 512);

        // A device is considered mounted if any of its partitions are mounted.
        bool mounted = false;
        QDir devDir(QStringLiteral("/sys/block/") + name);
        const QStringList partEntries = devDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QString &partName : partEntries) {
            if (!partName.startsWith(name)) {
                continue;
            }
            const QString devPath = QStringLiteral("/dev/") + partName;
            if (mounts.contains(devPath)) {
                mounted = true;
                break;
            }
        }
        device->setMounted(mounted);

        m_devices.append(device);
    }
}

void StorageManager::updatePartitions()
{
    qDeleteAll(m_partitions);
    m_partitions.clear();

    const auto mounts = readProcMounts();

    for (const auto &info : mounts) {
        const QString devicePath = info.device;
        if (!devicePath.startsWith(QStringLiteral("/dev/"))) {
            continue;
        }
        const QString partitionName = devicePath.mid(5);

        struct statvfs vfs;
        if (statvfs(info.mountPoint.toLocal8Bit().constData(), &vfs) != 0) {
            qWarning() << QStringLiteral("[BDE] StorageManager: statvfs failed for") << info.mountPoint;
            continue;
        }

        const qint64 blockSize = vfs.f_frsize;
        const qint64 totalSpace = blockSize * static_cast<qint64>(vfs.f_blocks);
        const qint64 freeSpace = blockSize * static_cast<qint64>(vfs.f_bavail);
        const qint64 usedSpace = totalSpace - freeSpace;
        int usagePercent = 0;
        if (totalSpace > 0) {
            usagePercent = static_cast<int>((usedSpace * 100) / totalSpace);
        }

        auto *partition = new StoragePartition(this);
        partition->setPartitionName(partitionName);
        partition->setFilesystem(info.filesystem);
        partition->setMountPoint(info.mountPoint);
        partition->setTotalSpace(totalSpace);
        partition->setUsedSpace(usedSpace);
        partition->setFreeSpace(freeSpace);
        partition->setUsagePercent(usagePercent);
        partition->setReadOnly(false);

        m_partitions.append(partition);
    }
}

void StorageManager::clearModel()
{
    qDeleteAll(m_devices);
    m_devices.clear();
    qDeleteAll(m_partitions);
    m_partitions.clear();
}

QString StorageManager::deviceTypeFromName(const QString &name) const
{
    if (name.startsWith(QStringLiteral("nvme"))) {
        return QStringLiteral("Internal SSD");
    }
    if (name.startsWith(QStringLiteral("sd"))) {
        return QStringLiteral("USB / SATA Drive");
    }
    if (name.startsWith(QStringLiteral("sr"))) {
        return QStringLiteral("Optical Drive");
    }
    if (name.startsWith(QStringLiteral("mmc"))) {
        return QStringLiteral("SD / MMC");
    }
    if (name.startsWith(QStringLiteral("hd"))) {
        return QStringLiteral("Internal Drive");
    }
    return QStringLiteral("Block Device");
}

qint64 StorageManager::readSysfsSize(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }
    QTextStream stream(&file);
    const QString value = stream.readLine().trimmed();
    file.close();
    bool ok = false;
    const qint64 result = value.toLongLong(&ok);
    return ok ? result : 0;
}

QString StorageManager::readSysfsString(const QString &path) const
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream stream(&file);
    const QString value = stream.readLine().trimmed();
    file.close();
    return value;
}

QString StorageManager::formatBytes(qint64 bytes) const
{
    if (bytes <= 0) {
        return QStringLiteral("0 B");
    }
    const QStringList units = {
        QStringLiteral("B"),
        QStringLiteral("KB"),
        QStringLiteral("MB"),
        QStringLiteral("GB"),
        QStringLiteral("TB"),
        QStringLiteral("PB")
    };
    int index = 0;
    double value = static_cast<double>(bytes);
    while (value >= 1024.0 && index < units.size() - 1) {
        value /= 1024.0;
        ++index;
    }
    return QString::number(value, 'f', 2) + QLatin1Char(' ') + units.at(index);
}

} // namespace bos::shell
