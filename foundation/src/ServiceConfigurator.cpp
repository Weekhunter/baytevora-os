#include "bldf/ServiceConfigurator.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

namespace bldf {

ServiceConfigurator::ServiceConfigurator(QObject *parent)
    : QObject(parent)
{
}

QString ServiceConfigurator::targetRoot() const { return m_targetRoot; }
void ServiceConfigurator::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

bool ServiceConfigurator::configureAll()
{
    if (m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("targetRoot is not set."));
        return false;
    }
    return createBaytevoraServiceUnits() && configureNetworkManager() &&
           configurePipeWire() && configureCUPS() && enableDebianServices();
}

bool ServiceConfigurator::createBaytevoraServiceUnits()
{
    const QString systemdDir = m_targetRoot + QStringLiteral("/etc/systemd/system");
    QDir().mkpath(systemdDir);

    const struct Unit {
        QString name;
        QString description;
        QString exec;
        QString after;
    } units[] = {
        { QStringLiteral("baytevora-storage.service"),
          QStringLiteral("Baytevora Storage Manager"),
          QStringLiteral("/opt/baytevora/services/storage/storage-daemon"),
          QStringLiteral("dbus.service") },
        { QStringLiteral("baytevora-printing.service"),
          QStringLiteral("Baytevora Printing Framework"),
          QStringLiteral("/opt/baytevora/services/printing/printing-daemon"),
          QStringLiteral("cups.service") },
        { QStringLiteral("baytevora-application.service"),
          QStringLiteral("Baytevora Application Framework"),
          QStringLiteral("/opt/baytevora/services/application/app-framework"),
          QStringLiteral("network.target") }
    };

    for (const auto &unit : units) {
        const QString path = systemdDir + QStringLiteral("/") + unit.name;
        const QString contents = QStringLiteral(
            "[Unit]\n"
            "Description=%1\n"
            "After=%2\n"
            "\n"
            "[Service]\n"
            "Type=simple\n"
            "ExecStart=%3\n"
            "Restart=on-failure\n"
            "\n"
            "[Install]\n"
            "WantedBy=multi-user.target\n"
        ).arg(unit.description, unit.after, unit.exec);
        if (!writeFile(path, contents)) return false;

        // Create placeholder executables if missing.
        const QString execPath = m_targetRoot + unit.exec;
        if (!QFile::exists(execPath)) {
            QDir().mkpath(QFileInfo(execPath).absolutePath());
            QFile f(execPath);
            if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream s(&f);
                s << "#!/bin/sh\n# Placeholder for " << unit.description << "\nexit 0\n";
                f.setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                                 QFile::ReadGroup | QFile::ExeGroup |
                                 QFile::ReadOther | QFile::ExeOther);
            }
        }
    }

    emit logInfo(QStringLiteral("Baytevora systemd service units created."));
    return true;
}

bool ServiceConfigurator::configureNetworkManager()
{
    const QString confDir = m_targetRoot + QStringLiteral("/etc/NetworkManager");
    QDir().mkpath(confDir);
    const QString path = confDir + QStringLiteral("/NetworkManager.conf");
    const QString contents = QStringLiteral(
        "[main]\n"
        "plugins=ifupdown,keyfile\n"
        "dhcp=internal\n"
        "\n"
        "[ifupdown]\n"
        "managed=true\n"
        "\n"
        "[connectivity]\n"
        "uri=http://nm.check-network.org/check\n"
        "interval=300\n"
    );
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("NetworkManager configured."));
    return true;
}

bool ServiceConfigurator::configurePipeWire()
{
    const QString confDir = m_targetRoot + QStringLiteral("/etc/pipewire");
    QDir().mkpath(confDir);
    const QString path = confDir + QStringLiteral("/pipewire.conf");
    const QString contents = QStringLiteral(
        "# Baytevora OS PipeWire configuration\n"
        "context.modules = [\n"
        "    { name = libpipewire-module-protocol-native }\n"
        "    { name = libpipewire-module-client-node }\n"
        "    { name = libpipewire-module-adapter }\n"
        "    { name = libpipewire-module-metadata }\n"
        "]\n"
    );
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("PipeWire configured."));
    return true;
}

bool ServiceConfigurator::configureCUPS()
{
    const QString confDir = m_targetRoot + QStringLiteral("/etc/cups");
    QDir().mkpath(confDir);
    const QString path = confDir + QStringLiteral("/cupsd.conf");
    const QString contents = QStringLiteral(
        "# Baytevora OS CUPS configuration\n"
        "Listen localhost:631\n"
        "Listen /run/cups/cups.sock\n"
        "BROWSING Off\n"
        "DefaultAuthType Basic\n"
        "WebInterface Yes\n"
    );
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("CUPS configured."));
    return true;
}

bool ServiceConfigurator::enableDebianServices()
{
    const QString enableDir = m_targetRoot + QStringLiteral("/etc/systemd/system/multi-user.target.wants");
    QDir().mkpath(enableDir);

    const QStringList services = {
        QStringLiteral("NetworkManager.service"),
        QStringLiteral("bluetooth.service"),
        QStringLiteral("cups.service"),
        QStringLiteral("systemd-timesyncd.service"),
        QStringLiteral("udisks2.service"),
        QStringLiteral("polkit.service"),
        QStringLiteral("sddm.service"),
        QStringLiteral("baytevora-storage.service"),
        QStringLiteral("baytevora-printing.service"),
        QStringLiteral("baytevora-application.service")
    };

    for (const QString &service : services) {
        const QString source = m_targetRoot + QStringLiteral("/etc/systemd/system/") + service;
        const QString link = enableDir + QStringLiteral("/") + service;
        if (QFile::exists(source) || QFile::exists(QStringLiteral("/lib/systemd/system/") + service)) {
            QFile::remove(link);
            if (!QFile::link(source, link) && !QFile::link(QStringLiteral("/lib/systemd/system/") + service, link)) {
                // Placeholder marker for sandbox without systemd paths.
                QFile marker(link + QStringLiteral(".placeholder"));
                marker.open(QIODevice::WriteOnly);
            }
        }
    }

    emit logInfo(QStringLiteral("Services enabled for multi-user target."));
    return true;
}

bool ServiceConfigurator::writeFile(const QString &path, const QString &contents)
{
    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit logError(QStringLiteral("Failed to write %1").arg(path));
        return false;
    }
    QTextStream stream(&file);
    stream << contents;
    return true;
}

} // namespace bldf
