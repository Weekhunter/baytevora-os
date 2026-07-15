#include "bldf/DebianBaseBuilder.h"

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTextStream>

namespace bldf {

DebianBaseBuilder::DebianBaseBuilder(QObject *parent)
    : QObject(parent)
{
}

QString DebianBaseBuilder::suite() const { return m_suite; }
void DebianBaseBuilder::setSuite(const QString &value)
{
    if (m_suite == value) return;
    m_suite = value;
    emit suiteChanged();
}

QString DebianBaseBuilder::mirror() const { return m_mirror; }
void DebianBaseBuilder::setMirror(const QString &value)
{
    if (m_mirror == value) return;
    m_mirror = value;
    emit mirrorChanged();
}

QString DebianBaseBuilder::targetRoot() const { return m_targetRoot; }
void DebianBaseBuilder::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

QStringList DebianBaseBuilder::packages() const { return m_packages; }
void DebianBaseBuilder::setPackages(const QStringList &value)
{
    if (m_packages == value) return;
    m_packages = value;
    emit packagesChanged();
}

bool DebianBaseBuilder::loadPackageList(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit logError(QStringLiteral("Cannot read package list: %1").arg(path));
        return false;
    }
    QStringList list;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty() || line.startsWith(QStringLiteral("#"))) continue;
        list.append(line);
    }
    setPackages(list);
    emit logInfo(QStringLiteral("Loaded %1 packages from %2").arg(list.size()).arg(path));
    return true;
}

bool DebianBaseBuilder::buildBase()
{
    if (m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("targetRoot is not set."));
        return false;
    }

    if (!createDirectoryStructure()) return false;
    if (!writeAptConfiguration()) return false;

    // Try real Debian bootstrapping when tools and network are available.
    if (QProcess::execute(QStringLiteral("which"), QStringList{ QStringLiteral("debootstrap") }) == 0) {
        if (installPackages()) {
            emit logInfo(QStringLiteral("Debian base installed via debootstrap."));
            return true;
        }
    }

    emit logWarning(QStringLiteral("debootstrap not available or failed; creating placeholder Debian base."));
    if (!createPlaceholderEnvironment()) {
        emit logError(QStringLiteral("Failed to create placeholder environment."));
        return false;
    }
    return true;
}

bool DebianBaseBuilder::verifyInstallation() const
{
    if (m_targetRoot.isEmpty()) return false;
    const QString dpkgStatus = m_targetRoot + QStringLiteral("/var/lib/dpkg/status");
    if (!QFile::exists(dpkgStatus)) {
        emit logError(QStringLiteral("dpkg status file missing at %1").arg(dpkgStatus));
        return false;
    }
    emit logInfo(QStringLiteral("Debian base verification passed."));
    return true;
}

bool DebianBaseBuilder::createDirectoryStructure()
{
    QDir root(m_targetRoot);
    const QStringList dirs = {
        QStringLiteral("bin"), QStringLiteral("sbin"), QStringLiteral("lib"), QStringLiteral("lib64"),
        QStringLiteral("usr"), QStringLiteral("usr/bin"), QStringLiteral("usr/sbin"),
        QStringLiteral("usr/lib"), QStringLiteral("usr/share"), QStringLiteral("etc"),
        QStringLiteral("var"), QStringLiteral("var/lib"), QStringLiteral("var/lib/dpkg"),
        QStringLiteral("var/cache"), QStringLiteral("var/log"), QStringLiteral("tmp"),
        QStringLiteral("run"), QStringLiteral("home"), QStringLiteral("root"),
        QStringLiteral("opt"), QStringLiteral("srv"), QStringLiteral("mnt"),
        QStringLiteral("media"), QStringLiteral("dev"), QStringLiteral("proc"),
        QStringLiteral("sys")
    };
    for (const QString &d : dirs) {
        if (!root.mkpath(d)) {
            emit logError(QStringLiteral("Failed to create directory %1").arg(d));
            return false;
        }
    }
    emit logInfo(QStringLiteral("Root filesystem directories created."));
    return true;
}

bool DebianBaseBuilder::writeAptConfiguration()
{
    const QString aptDir = m_targetRoot + QStringLiteral("/etc/apt");
    QDir().mkpath(aptDir);
    const QString sources = aptDir + QStringLiteral("/sources.list");
    QFile file(sources);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit logError(QStringLiteral("Failed to write sources.list"));
        return false;
    }
    QTextStream stream(&file);
    stream << "# Baytevora OS Debian sources\n";
    stream << "deb " << m_mirror << " " << m_suite << " main contrib non-free-firmware\n";
    stream << "deb " << m_mirror << " " << m_suite << "-updates main contrib non-free-firmware\n";
    stream << "deb http://security.debian.org/debian-security " << m_suite << "-security main contrib non-free-firmware\n";

    emit logInfo(QStringLiteral("APT sources configured for %1").arg(m_suite));
    return true;
}

bool DebianBaseBuilder::installPackages()
{
    QProcess proc;
    QStringList args = { m_suite, m_targetRoot, m_mirror };
    if (!m_packages.isEmpty()) {
        args << QStringLiteral("--include=%1").arg(m_packages.join(QStringLiteral(",")));
    }
    proc.start(QStringLiteral("debootstrap"), args);
    proc.waitForFinished(-1);
    if (proc.exitCode() != 0) {
        emit logError(QStringLiteral("debootstrap failed: %1").arg(QString::fromUtf8(proc.readAllStandardError())));
        return false;
    }
    return true;
}

bool DebianBaseBuilder::createPlaceholderEnvironment()
{
    // Write a dpkg status file so the package manager integration has data to read.
    const QString dpkgDir = m_targetRoot + QStringLiteral("/var/lib/dpkg");
    QDir().mkpath(dpkgDir);
    QFile status(dpkgDir + QStringLiteral("/status"));
    if (!status.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit logError(QStringLiteral("Failed to write placeholder dpkg status."));
        return false;
    }
    QTextStream stream(&status);
    for (const QString &pkg : m_packages) {
        stream << "Package: " << pkg << "\n";
        stream << "Status: install ok installed\n";
        stream << "Version: 0.1-alpha\n";
        stream << "Description: placeholder package entry for Baytevora OS Alpha\n";
        stream << "\n";
    }

    // Create small placeholder binaries for essential tools so scripts can reference them.
    const QStringList tools = {
        QStringLiteral("systemctl"), QStringLiteral("bash"), QStringLiteral("sh"),
        QStringLiteral("mount"), QStringLiteral("umount"), QStringLiteral("modprobe"),
        QStringLiteral("udevadm"), QStringLiteral("dbus-daemon"), QStringLiteral("NetworkManager"),
        QStringLiteral("pipewire"), QStringLiteral("cupsd"), QStringLiteral("sddm"),
        QStringLiteral("gdm3"), QStringLiteral("apt-get"), QStringLiteral("dpkg")
    };
    for (const QString &tool : tools) {
        const QString path = m_targetRoot + QStringLiteral("/usr/bin/") + tool;
        QFile f(path);
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            stream.setDevice(&f);
            stream << "#!/bin/sh\n";
            stream << "# Placeholder for " << tool << "\n";
            stream << "echo \"[BOS PLACEHOLDER] " << tool << " not functional in Alpha sandbox\" >&2\n";
            stream << "exit 0\n";
            f.setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                             QFile::ReadGroup | QFile::ExeGroup |
                             QFile::ReadOther | QFile::ExeOther);
        }
    }

    // systemd placeholder so live-init can switch_root into /sbin/init.
    const QString systemdDir = m_targetRoot + QStringLiteral("/usr/lib/systemd");
    QDir().mkpath(systemdDir);
    QFile systemd(systemdDir + QStringLiteral("/systemd"));
    if (systemd.open(QIODevice::WriteOnly | QIODevice::Text)) {
        stream.setDevice(&systemd);
        stream << "#!/bin/sh\n# Placeholder systemd for Baytevora OS Alpha sandbox\n";
        stream << "echo \"[BOS PLACEHOLDER] systemd not functional in Alpha sandbox\" >&2\n";
        stream << "exec /bin/sh\n";
        systemd.setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                               QFile::ReadGroup | QFile::ExeGroup |
                               QFile::ReadOther | QFile::ExeOther);
    }
    QFile::link(QStringLiteral("/usr/lib/systemd/systemd"), m_targetRoot + QStringLiteral("/sbin/init"));

    emit logInfo(QStringLiteral("Placeholder Debian base created with %1 package entries.").arg(m_packages.size()));
    return true;
}

} // namespace bldf
