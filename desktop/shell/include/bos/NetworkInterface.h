#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

namespace bos::shell {

/**
 * @brief Represents a single network interface in the Network Manager.
 */
class NetworkInterface : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString interfaceName READ interfaceName NOTIFY interfaceNameChanged FINAL)
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged FINAL)
    Q_PROPERTY(QString interfaceType READ interfaceType NOTIFY interfaceTypeChanged FINAL)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged FINAL)
    Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY ipAddressChanged FINAL)
    Q_PROPERTY(QString subnetMask READ subnetMask NOTIFY subnetMaskChanged FINAL)
    Q_PROPERTY(QString gateway READ gateway NOTIFY gatewayChanged FINAL)
    Q_PROPERTY(QStringList dnsServers READ dnsServers NOTIFY dnsServersChanged FINAL)
    Q_PROPERTY(QString macAddress READ macAddress NOTIFY macAddressChanged FINAL)
    Q_PROPERTY(QString speed READ speed NOTIFY speedChanged FINAL)

public:
    explicit NetworkInterface(QObject *parent = nullptr);

    QString interfaceName() const;
    QString displayName() const;
    QString interfaceType() const;
    bool connected() const;
    bool enabled() const;
    QString ipAddress() const;
    QString subnetMask() const;
    QString gateway() const;
    QStringList dnsServers() const;
    QString macAddress() const;
    QString speed() const;

    void setInterfaceName(const QString &value);
    void setDisplayName(const QString &value);
    void setInterfaceType(const QString &value);
    void setConnected(bool value);
    void setEnabled(bool value);
    void setIpAddress(const QString &value);
    void setSubnetMask(const QString &value);
    void setGateway(const QString &value);
    void setDnsServers(const QStringList &value);
    void setMacAddress(const QString &value);
    void setSpeed(const QString &value);

signals:
    void interfaceNameChanged();
    void displayNameChanged();
    void interfaceTypeChanged();
    void connectedChanged();
    void enabledChanged();
    void ipAddressChanged();
    void subnetMaskChanged();
    void gatewayChanged();
    void dnsServersChanged();
    void macAddressChanged();
    void speedChanged();

private:
    QString m_interfaceName;
    QString m_displayName;
    QString m_interfaceType;
    bool m_connected = false;
    bool m_enabled = false;
    QString m_ipAddress;
    QString m_subnetMask;
    QString m_gateway;
    QStringList m_dnsServers;
    QString m_macAddress;
    QString m_speed;
};

} // namespace bos::shell
