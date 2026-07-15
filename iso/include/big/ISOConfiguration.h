#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace big {

/**
 * @brief ISO-specific metadata and bootloader parameters.
 */
class ISOConfiguration : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString volumeLabel READ volumeLabel WRITE setVolumeLabel NOTIFY volumeLabelChanged FINAL)
    Q_PROPERTY(QString publisher READ publisher WRITE setPublisher NOTIFY publisherChanged FINAL)
    Q_PROPERTY(QString applicationID READ applicationID WRITE setApplicationID NOTIFY applicationIDChanged FINAL)
    Q_PROPERTY(QString bootMode READ bootMode WRITE setBootMode NOTIFY bootModeChanged FINAL)
    Q_PROPERTY(int bootTimeout READ bootTimeout WRITE setBootTimeout NOTIFY bootTimeoutChanged FINAL)

public:
    explicit ISOConfiguration(QObject *parent = nullptr);

    QString volumeLabel() const;
    void setVolumeLabel(const QString &value);

    QString publisher() const;
    void setPublisher(const QString &value);

    QString applicationID() const;
    void setApplicationID(const QString &value);

    QString bootMode() const;
    void setBootMode(const QString &value);

    int bootTimeout() const;
    void setBootTimeout(int value);

    Q_INVOKABLE bool loadFromFile(const QString &path);
    Q_INVOKABLE bool validate() const;
    Q_INVOKABLE QVariantMap toMap() const;

signals:
    void volumeLabelChanged();
    void publisherChanged();
    void applicationIDChanged();
    void bootModeChanged();
    void bootTimeoutChanged();

private:
    QString m_volumeLabel = QStringLiteral("Baytevora OS 0.1 Alpha");
    QString m_publisher = QStringLiteral("Baytevora Project");
    QString m_applicationID = QStringLiteral("Baytevora-OS-Installer");
    QString m_bootMode = QStringLiteral("UEFI");
    int m_bootTimeout = 5;
};

} // namespace big
