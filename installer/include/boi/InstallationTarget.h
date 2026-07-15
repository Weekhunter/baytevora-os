#pragma once

#include <QObject>
#include <QString>

namespace boi {

/**
 * @brief Represents a disk chosen as the installation target.
 *
 * InstallationTarget wraps the properties needed by the installer UI and
 * validation logic. It is intentionally separate from StorageDevice so the
 * installer does not depend on storage implementation details.
 */
class InstallationTarget : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString diskId READ diskId WRITE setDiskId NOTIFY diskIdChanged FINAL)
    Q_PROPERTY(QString diskName READ diskName WRITE setDiskName NOTIFY diskNameChanged FINAL)
    Q_PROPERTY(QString model READ model WRITE setModel NOTIFY modelChanged FINAL)
    Q_PROPERTY(QString filesystem READ filesystem WRITE setFilesystem NOTIFY filesystemChanged FINAL)
    Q_PROPERTY(qint64 capacityBytes READ capacityBytes WRITE setCapacityBytes NOTIFY capacityBytesChanged FINAL)
    Q_PROPERTY(QString capacityText READ capacityText NOTIFY capacityTextChanged FINAL)
    Q_PROPERTY(bool removable READ removable WRITE setRemovable NOTIFY removableChanged FINAL)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged FINAL)

public:
    explicit InstallationTarget(QObject *parent = nullptr);

    QString diskId() const;
    void setDiskId(const QString &value);

    QString diskName() const;
    void setDiskName(const QString &value);

    QString model() const;
    void setModel(const QString &value);

    QString filesystem() const;
    void setFilesystem(const QString &value);

    qint64 capacityBytes() const;
    void setCapacityBytes(qint64 value);

    QString capacityText() const;

    bool removable() const;
    void setRemovable(bool value);

    bool valid() const;
    void setValid(bool value);

signals:
    void diskIdChanged();
    void diskNameChanged();
    void modelChanged();
    void filesystemChanged();
    void capacityBytesChanged();
    void capacityTextChanged();
    void removableChanged();
    void validChanged();

private:
    QString m_diskId;
    QString m_diskName;
    QString m_model;
    QString m_filesystem;
    qint64 m_capacityBytes = 0;
    bool m_removable = false;
    bool m_valid = false;
};

} // namespace boi
