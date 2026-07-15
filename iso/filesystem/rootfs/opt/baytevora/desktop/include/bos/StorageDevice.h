#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Represents a single storage device in the Storage Manager.
 */
class StorageDevice : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString deviceName READ deviceName NOTIFY deviceNameChanged FINAL)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged FINAL)
    Q_PROPERTY(QString deviceType READ deviceType NOTIFY deviceTypeChanged FINAL)
    Q_PROPERTY(QString model READ model NOTIFY modelChanged FINAL)
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged FINAL)
    Q_PROPERTY(qint64 capacity READ capacity NOTIFY capacityChanged FINAL)
    Q_PROPERTY(bool removable READ removable NOTIFY removableChanged FINAL)
    Q_PROPERTY(bool mounted READ mounted NOTIFY mountedChanged FINAL)

public:
    explicit StorageDevice(QObject *parent = nullptr);

    QString deviceName() const;
    QString displayName() const;
    QString deviceType() const;
    QString model() const;
    QString serialNumber() const;
    qint64 capacity() const;
    bool removable() const;
    bool mounted() const;

    void setDeviceName(const QString &value);
    void setDisplayName(const QString &value);
    void setDeviceType(const QString &value);
    void setModel(const QString &value);
    void setSerialNumber(const QString &value);
    void setCapacity(qint64 value);
    void setRemovable(bool value);
    void setMounted(bool value);

signals:
    void deviceNameChanged();
    void displayNameChanged();
    void deviceTypeChanged();
    void modelChanged();
    void serialNumberChanged();
    void capacityChanged();
    void removableChanged();
    void mountedChanged();

private:
    QString m_deviceName;
    QString m_displayName;
    QString m_deviceType;
    QString m_model;
    QString m_serialNumber;
    qint64 m_capacity = 0;
    bool m_removable = false;
    bool m_mounted = false;
};

} // namespace bos::shell
