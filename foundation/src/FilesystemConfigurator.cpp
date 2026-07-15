#include "bldf/FilesystemConfigurator.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

namespace bldf {

FilesystemConfigurator::FilesystemConfigurator(QObject *parent)
    : QObject(parent)
{
}

QString FilesystemConfigurator::targetRoot() const { return m_targetRoot; }
void FilesystemConfigurator::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

QString FilesystemConfigurator::hostname() const { return m_hostname; }
void FilesystemConfigurator::setHostname(const QString &value)
{
    if (m_hostname == value) return;
    m_hostname = value;
    emit hostnameChanged();
}

QString FilesystemConfigurator::locale() const { return m_locale; }
void FilesystemConfigurator::setLocale(const QString &value)
{
    if (m_locale == value) return;
    m_locale = value;
    emit localeChanged();
}

QString FilesystemConfigurator::timezone() const { return m_timezone; }
void FilesystemConfigurator::setTimezone(const QString &value)
{
    if (m_timezone == value) return;
    m_timezone = value;
    emit timezoneChanged();
}

bool FilesystemConfigurator::configureAll()
{
    if (m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("targetRoot is not set."));
        return false;
    }
    return configureFstab() && configureHostname() && configureHosts() &&
           configureLocale() && configureTimezone() && configureResolv() &&
           configureOsRelease() && configureSudoers();
}

bool FilesystemConfigurator::configureFstab()
{
    const QString path = m_targetRoot + QStringLiteral("/etc/fstab");
    const QString contents = QStringLiteral(
        "# Baytevora OS fstab\n"
        "# <file system> <mount point>   <type>  <options>       <dump>  <pass>\n"
        "proc            /proc           proc    defaults          0       0\n"
        "sysfs           /sys            sysfs   defaults          0       0\n"
        "devtmpfs        /dev            devtmpfs rw,nosuid        0       0\n"
        "tmpfs           /tmp            tmpfs   defaults,nosuid,nodev 0   0\n"
        "tmpfs           /run            tmpfs   defaults,nosuid,nodev 0   0\n"
        "LABEL=BAYTEVORA_ROOT /          ext4    errors=remount-ro 0       1\n"
        "LABEL=BAYTEVORA_BOOT /boot      ext4    defaults          0       2\n"
        "LABEL=BAYTEVORA_SWAP none       swap    sw                0       0\n"
    );
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("fstab configured."));
    return true;
}

bool FilesystemConfigurator::configureHostname()
{
    if (!writeFile(m_targetRoot + QStringLiteral("/etc/hostname"), m_hostname + QStringLiteral("\n"))) return false;
    emit logInfo(QStringLiteral("Hostname set to %1").arg(m_hostname));
    return true;
}

bool FilesystemConfigurator::configureHosts()
{
    const QString contents = QStringLiteral(
        "127.0.0.1\tlocalhost\n"
        "127.0.1.1\t%1\n"
        "::1\t\tip6-localhost ip6-loopback\n"
        "ff02::1\tip6-allnodes\n"
        "ff02::2\tip6-allrouters\n"
    ).arg(m_hostname);
    if (!writeFile(m_targetRoot + QStringLiteral("/etc/hosts"), contents)) return false;
    emit logInfo(QStringLiteral("hosts configured."));
    return true;
}

bool FilesystemConfigurator::configureLocale()
{
    const QString path = m_targetRoot + QStringLiteral("/etc/locale.gen");
    const QString contents = m_locale + QStringLiteral(" UTF-8\n");
    if (!writeFile(path, contents)) return false;

    const QString localeConf = m_targetRoot + QStringLiteral("/etc/locale.conf");
    if (!writeFile(localeConf, QStringLiteral("LANG=%1\n").arg(m_locale))) return false;

    emit logInfo(QStringLiteral("Locale configured: %1").arg(m_locale));
    return true;
}

bool FilesystemConfigurator::configureTimezone()
{
    const QString path = m_targetRoot + QStringLiteral("/etc/timezone");
    if (!writeFile(path, m_timezone + QStringLiteral("\n"))) return false;

    const QString localtimeLink = m_targetRoot + QStringLiteral("/etc/localtime");
    QFile::remove(localtimeLink);
    QFile::link(QStringLiteral("/usr/share/zoneinfo/") + m_timezone, localtimeLink);

    emit logInfo(QStringLiteral("Timezone configured: %1").arg(m_timezone));
    return true;
}

bool FilesystemConfigurator::configureResolv()
{
    const QString contents = QStringLiteral(
        "nameserver 8.8.8.8\n"
        "nameserver 8.8.4.4\n"
        "nameserver 1.1.1.1\n"
    );
    if (!writeFile(m_targetRoot + QStringLiteral("/etc/resolv.conf"), contents)) return false;
    emit logInfo(QStringLiteral("resolv.conf configured."));
    return true;
}

bool FilesystemConfigurator::configureOsRelease()
{
    const QString contents = QStringLiteral(
        "PRETTY_NAME=\"Baytevora OS 0.1 Alpha (Debian-based)\"\n"
        "NAME=\"Baytevora OS\"\n"
        "VERSION_ID=\"0.1\"\n"
        "VERSION=\"0.1 Alpha\"\n"
        "ID=baytevora\n"
        "ID_LIKE=debian\n"
        "HOME_URL=\"https://baytevora.example/\"\n"
        "SUPPORT_URL=\"https://baytevora.example/support\"\n"
        "BUG_REPORT_URL=\"https://baytevora.example/issues\"\n"
    );
    if (!writeFile(m_targetRoot + QStringLiteral("/etc/os-release"), contents)) return false;
    if (!writeFile(m_targetRoot + QStringLiteral("/etc/issue"), QStringLiteral("Baytevora OS 0.1 Alpha \\l \\n"))) return false;
    emit logInfo(QStringLiteral("os-release configured."));
    return true;
}

bool FilesystemConfigurator::configureSudoers()
{
    const QString sudoersD = m_targetRoot + QStringLiteral("/etc/sudoers.d");
    QDir().mkpath(sudoersD);
    const QString contents = QStringLiteral(
        "# Allow live user to run commands without a password\n"
        "live ALL=(ALL) NOPASSWD: ALL\n"
        "# Default installed user\n"
        "%sudo ALL=(ALL:ALL) ALL\n"
    );
    const QString path = sudoersD + QStringLiteral("/live-user");
    if (!writeFile(path, contents)) return false;
    QFile::setPermissions(path, QFile::ReadOwner | QFile::WriteOwner);
    emit logInfo(QStringLiteral("Sudoers configured for live user."));
    return true;
}

bool FilesystemConfigurator::writeFile(const QString &path, const QString &contents)
{
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
