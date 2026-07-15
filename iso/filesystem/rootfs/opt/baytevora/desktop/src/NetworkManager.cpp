#include "bos/NetworkManager.h"

#include <QAbstractSocket>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QTextStream>

#include "bos/NetworkInterface.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

namespace {

QString interfaceTypeName(QNetworkInterface::InterfaceType type)
{
    switch (type) {
    case QNetworkInterface::Loopback:
        return QStringLiteral("Loopback");
    case QNetworkInterface::Ethernet:
        return QStringLiteral("Ethernet");
    case QNetworkInterface::Ieee80211:
        return QStringLiteral("Wi-Fi");
    case QNetworkInterface::Ppp:
        return QStringLiteral("PPP");
    case QNetworkInterface::Virtual:
        return QStringLiteral("Virtual");
    default:
        return QStringLiteral("Unknown");
    }
}

QString readSysFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream stream(&file);
    QString value = stream.readLine().trimmed();
    file.close();
    return value;
}

QString readInterfaceSpeed(const QString &name)
{
    const QString value = readSysFile(QStringLiteral("/sys/class/net/") + name + QStringLiteral("/speed"));
    if (value.isEmpty() || value == QStringLiteral("-1")) {
        return QStringLiteral("Unknown");
    }
    bool ok = false;
    const qint64 mbps = value.toLongLong(&ok);
    if (!ok) {
        return QStringLiteral("Unknown");
    }
    return QString::number(mbps) + QStringLiteral(" Mb/s");
}

QString readOperState(const QString &name)
{
    return readSysFile(QStringLiteral("/sys/class/net/") + name + QStringLiteral("/operstate"));
}

QString defaultGatewayForInterface(const QString &name)
{
    QFile file(QStringLiteral("/proc/net/route"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    QTextStream stream(&file);
    stream.readLine(); // skip header
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        const QStringList parts = line.split(QRegularExpression(QStringLiteral("\\s+")), Qt::SkipEmptyParts);
        if (parts.size() < 3) {
            continue;
        }
        if (parts.at(0) != name) {
            continue;
        }
        if (parts.at(1) == QStringLiteral("00000000")) {
            bool ok = false;
            const quint32 gateway = parts.at(2).toUInt(&ok, 16);
            if (ok) {
                file.close();
                return QHostAddress(qToBigEndian(gateway)).toString();
            }
        }
    }
    file.close();
    return QString();
}

QStringList readDnsServers()
{
    QStringList servers;
    QFile file(QStringLiteral("/etc/resolv.conf"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return servers;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.startsWith(QStringLiteral("nameserver"))) {
            const QString address = line.section(QRegularExpression(QStringLiteral("\\s+")), 1, 1).trimmed();
            if (!address.isEmpty()) {
                servers.append(address);
            }
        }
    }
    file.close();
    return servers;
}

} // namespace

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout, this, &NetworkManager::refresh);
    refresh();
}

NetworkManager::~NetworkManager() = default;

QVariantList NetworkManager::interfaces() const
{
    QVariantList list;
    list.reserve(m_interfaces.size());
    for (NetworkInterface *iface : m_interfaces) {
        if (!iface) {
            continue;
        }
        QVariantMap map;
        map.insert(QStringLiteral("interfaceName"), iface->interfaceName());
        map.insert(QStringLiteral("displayName"), iface->displayName());
        map.insert(QStringLiteral("interfaceType"), iface->interfaceType());
        map.insert(QStringLiteral("connected"), iface->connected());
        map.insert(QStringLiteral("enabled"), iface->enabled());
        map.insert(QStringLiteral("ipAddress"), iface->ipAddress());
        map.insert(QStringLiteral("subnetMask"), iface->subnetMask());
        map.insert(QStringLiteral("gateway"), iface->gateway());
        map.insert(QStringLiteral("dnsServers"), iface->dnsServers());
        map.insert(QStringLiteral("dnsServersText"), iface->dnsServers().join(QLatin1String(", ")));
        map.insert(QStringLiteral("macAddress"), iface->macAddress());
        map.insert(QStringLiteral("speed"), iface->speed());
        list.append(map);
    }
    return list;
}

void NetworkManager::setNotificationManager(QObject *manager)
{
    m_notificationManager = qobject_cast<NotificationManager*>(manager);
}

void NetworkManager::refresh()
{
    updateInterfaces();
    emit interfacesChanged();
}

void NetworkManager::startMonitoring()
{
    if (m_timer && !m_timer->isActive()) {
        m_timer->start(2000);
    }
}

void NetworkManager::stopMonitoring()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
    }
}

void NetworkManager::enableInterface(const QString &name)
{
    NetworkInterface *iface = findInterface(name);
    if (!iface) {
        return;
    }
    iface->setEnabled(true);
    notify(QStringLiteral("Interface Enabled."));
    emit interfacesChanged();
}

void NetworkManager::disableInterface(const QString &name)
{
    NetworkInterface *iface = findInterface(name);
    if (!iface) {
        return;
    }
    iface->setEnabled(false);
    iface->setConnected(false);
    notify(QStringLiteral("Interface Disabled."));
    emit interfacesChanged();
}

void NetworkManager::connectInterface(const QString &name)
{
    NetworkInterface *iface = findInterface(name);
    if (!iface) {
        return;
    }
    iface->setEnabled(true);
    iface->setConnected(true);
    notify(QStringLiteral("Connected."));
    emit interfacesChanged();
}

void NetworkManager::disconnectInterface(const QString &name)
{
    NetworkInterface *iface = findInterface(name);
    if (!iface) {
        return;
    }
    iface->setConnected(false);
    notify(QStringLiteral("Disconnected."));
    emit interfacesChanged();
}

void NetworkManager::updateInterfaces()
{
    const QStringList dnsServers = readDnsServers();

    QMap<QString, NetworkInterface*> existing;
    for (NetworkInterface *iface : std::as_const(m_interfaces)) {
        existing.insert(iface->interfaceName(), iface);
    }

    QList<NetworkInterface*> newList;
    const QList<QNetworkInterface> systemInterfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface &sysIface : systemInterfaces) {
        const QString name = sysIface.name();

        NetworkInterface *iface = existing.take(name);
        if (!iface) {
            iface = new NetworkInterface(this);
            iface->setInterfaceName(name);
        }

        iface->setDisplayName(sysIface.humanReadableName());
        iface->setInterfaceType(interfaceTypeName(sysIface.type()));
        iface->setMacAddress(sysIface.hardwareAddress());

        const QFlags<QNetworkInterface::InterfaceFlag> flags = sysIface.flags();
        iface->setEnabled(flags.testFlag(QNetworkInterface::IsUp));

        const bool isLoopback = sysIface.type() == QNetworkInterface::Loopback;
        const QString operState = readOperState(name);
        const bool linkActive = operState == QStringLiteral("up") || operState == QStringLiteral("unknown");
        iface->setConnected(iface->enabled() && (linkActive || isLoopback));

        // Pick an IPv4 address if available, otherwise fall back to the first address.
        QString ipAddress;
        QString subnetMask;
        const QList<QNetworkAddressEntry> entries = sysIface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                ipAddress = entry.ip().toString();
                subnetMask = entry.netmask().toString();
                break;
            }
        }
        if (ipAddress.isEmpty() && !entries.isEmpty()) {
            ipAddress = entries.first().ip().toString();
            subnetMask = entries.first().netmask().toString();
        }
        iface->setIpAddress(ipAddress);
        iface->setSubnetMask(subnetMask);

        iface->setGateway(defaultGatewayForInterface(name));
        iface->setDnsServers(dnsServers);
        iface->setSpeed(readInterfaceSpeed(name));

        newList.append(iface);
    }

    // Any interfaces left in existing are no longer present.
    for (NetworkInterface *iface : existing) {
        iface->deleteLater();
    }

    m_interfaces = newList;
}

NetworkInterface *NetworkManager::findInterface(const QString &name)
{
    for (NetworkInterface *iface : std::as_const(m_interfaces)) {
        if (iface->interfaceName() == name) {
            return iface;
        }
    }
    return nullptr;
}

void NetworkManager::notify(const QString &body)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(QStringLiteral("Network Manager"),
                                                  body,
                                                  QStringLiteral("Network Manager"),
                                                  QStringLiteral("info"));
    }
}

} // namespace bos::shell
