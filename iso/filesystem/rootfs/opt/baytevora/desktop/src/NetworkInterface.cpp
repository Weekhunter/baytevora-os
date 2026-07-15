#include "bos/NetworkInterface.h"

namespace bos::shell {

NetworkInterface::NetworkInterface(QObject *parent)
    : QObject(parent)
{
}

QString NetworkInterface::interfaceName() const { return m_interfaceName; }
QString NetworkInterface::displayName() const { return m_displayName; }
QString NetworkInterface::interfaceType() const { return m_interfaceType; }
bool NetworkInterface::connected() const { return m_connected; }
bool NetworkInterface::enabled() const { return m_enabled; }
QString NetworkInterface::ipAddress() const { return m_ipAddress; }
QString NetworkInterface::subnetMask() const { return m_subnetMask; }
QString NetworkInterface::gateway() const { return m_gateway; }
QStringList NetworkInterface::dnsServers() const { return m_dnsServers; }
QString NetworkInterface::macAddress() const { return m_macAddress; }
QString NetworkInterface::speed() const { return m_speed; }

void NetworkInterface::setInterfaceName(const QString &value)
{
    if (m_interfaceName == value) {
        return;
    }
    m_interfaceName = value;
    emit interfaceNameChanged();
}

void NetworkInterface::setDisplayName(const QString &value)
{
    if (m_displayName == value) {
        return;
    }
    m_displayName = value;
    emit displayNameChanged();
}

void NetworkInterface::setInterfaceType(const QString &value)
{
    if (m_interfaceType == value) {
        return;
    }
    m_interfaceType = value;
    emit interfaceTypeChanged();
}

void NetworkInterface::setConnected(bool value)
{
    if (m_connected == value) {
        return;
    }
    m_connected = value;
    emit connectedChanged();
}

void NetworkInterface::setEnabled(bool value)
{
    if (m_enabled == value) {
        return;
    }
    m_enabled = value;
    emit enabledChanged();
}

void NetworkInterface::setIpAddress(const QString &value)
{
    if (m_ipAddress == value) {
        return;
    }
    m_ipAddress = value;
    emit ipAddressChanged();
}

void NetworkInterface::setSubnetMask(const QString &value)
{
    if (m_subnetMask == value) {
        return;
    }
    m_subnetMask = value;
    emit subnetMaskChanged();
}

void NetworkInterface::setGateway(const QString &value)
{
    if (m_gateway == value) {
        return;
    }
    m_gateway = value;
    emit gatewayChanged();
}

void NetworkInterface::setDnsServers(const QStringList &value)
{
    if (m_dnsServers == value) {
        return;
    }
    m_dnsServers = value;
    emit dnsServersChanged();
}

void NetworkInterface::setMacAddress(const QString &value)
{
    if (m_macAddress == value) {
        return;
    }
    m_macAddress = value;
    emit macAddressChanged();
}

void NetworkInterface::setSpeed(const QString &value)
{
    if (m_speed == value) {
        return;
    }
    m_speed = value;
    emit speedChanged();
}

} // namespace bos::shell
