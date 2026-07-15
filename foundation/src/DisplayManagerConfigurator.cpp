#include "bldf/DisplayManagerConfigurator.h"

#include <QDir>
#include <QFile>
#include <QTextStream>

namespace bldf {

DisplayManagerConfigurator::DisplayManagerConfigurator(QObject *parent)
    : QObject(parent)
{
}

QString DisplayManagerConfigurator::targetRoot() const { return m_targetRoot; }
void DisplayManagerConfigurator::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

QString DisplayManagerConfigurator::displayManager() const { return m_displayManager; }
void DisplayManagerConfigurator::setDisplayManager(const QString &value)
{
    if (m_displayManager == value) return;
    m_displayManager = value;
    emit displayManagerChanged();
}

QString DisplayManagerConfigurator::liveUser() const { return m_liveUser; }
void DisplayManagerConfigurator::setLiveUser(const QString &value)
{
    if (m_liveUser == value) return;
    m_liveUser = value;
    emit liveUserChanged();
}

bool DisplayManagerConfigurator::configureAll()
{
    if (m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("targetRoot is not set."));
        return false;
    }
    return createLiveUser() && createSessionFile() && createSessionScript() &&
           createInstallerLauncher() && configureSDDM() && configureGDM();
}

bool DisplayManagerConfigurator::createSessionFile()
{
    const QString xsessions = m_targetRoot + QStringLiteral("/usr/share/xsessions");
    QDir().mkpath(xsessions);
    const QString path = xsessions + QStringLiteral("/Baytevora.desktop");
    const QString contents = QStringLiteral(
        "[Desktop Entry]\n"
        "Name=Baytevora\n"
        "Comment=Baytevora Desktop Session\n"
        "Exec=/usr/bin/baytevora-session\n"
        "Type=Application\n"
        "DesktopNames=Baytevora\n"
    );
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("Baytevora.desktop session file created."));
    return true;
}

bool DisplayManagerConfigurator::createSessionScript()
{
    const QString path = m_targetRoot + QStringLiteral("/usr/bin/baytevora-session");
    const QString contents = QStringLiteral(
        "#!/bin/sh\n"
        "# Baytevora desktop session launcher\n"
        "# Prefer Wayland; fall back to X11 if unavailable.\n"
        "if command -v weston >/dev/null 2>&1; then\n"
        "    export QT_QPA_PLATFORM=wayland\n"
        "    export XDG_SESSION_TYPE=wayland\n"
        "elif [ -n \"$DISPLAY\" ]; then\n"
        "    export QT_QPA_PLATFORM=xcb\n"
        "    export XDG_SESSION_TYPE=x11\n"
        "fi\n"
        "export XDG_CURRENT_DESKTOP=Baytevora\n"
        "export XDG_DATA_DIRS=/usr/share:/usr/local/share:/opt/baytevora/desktop:/usr/share/baytevora\n"
        "exec /opt/baytevora/desktop/build/Baytevora_OS_Shell \"$@\"\n"
    );
    if (!writeFile(path, contents)) return false;
    QFile::setPermissions(path, QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                               QFile::ReadGroup | QFile::ExeGroup |
                               QFile::ReadOther | QFile::ExeOther);
    emit logInfo(QStringLiteral("baytevora-session launcher created."));
    return true;
}

bool DisplayManagerConfigurator::createInstallerLauncher()
{
    const QString path = m_targetRoot + QStringLiteral("/usr/bin/baytevora-installer");
    const QString contents = QStringLiteral(
        "#!/bin/sh\n"
        "# Auto-launch Baytevora OS Installer in the live environment\n"
        "exec /opt/baytevora/installer/build/Baytevora_OS_Installer \"$@\"\n"
    );
    if (!writeFile(path, contents)) return false;
    QFile::setPermissions(path, QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                               QFile::ReadGroup | QFile::ExeGroup |
                               QFile::ReadOther | QFile::ExeOther);
    emit logInfo(QStringLiteral("baytevora-installer launcher created."));
    return true;
}

bool DisplayManagerConfigurator::configureSDDM()
{
    const QString confDir = m_targetRoot + QStringLiteral("/etc/sddm");
    QDir().mkpath(confDir);
    const QString path = confDir + QStringLiteral("/sddm.conf");
    const QString contents = QStringLiteral(
        "[Autologin]\n"
        "User=%1\n"
        "Session=Baytevora.desktop\n"
        "Relogin=false\n"
        "\n"
        "[General]\n"
        "DisplayServer=wayland\n"
        "GreeterEnvironment=QT_QPA_PLATFORM=wayland\n"
        "\n"
        "[Wayland]\n"
        "CompositorCommand=weston --shell=kiosk\n"
    ).arg(m_liveUser);
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("SDDM configured for auto-login."));
    return true;
}

bool DisplayManagerConfigurator::configureGDM()
{
    const QString confDir = m_targetRoot + QStringLiteral("/etc/gdm3");
    QDir().mkpath(confDir);
    const QString path = confDir + QStringLiteral("/custom.conf");
    const QString contents = QStringLiteral(
        "[daemon]\n"
        "AutomaticLoginEnable=true\n"
        "AutomaticLogin=%1\n"
        "WaylandEnable=true\n"
        "\n"
        "[security]\n"
        "\n"
        "[greeter]\n"
        "\n"
        "[chooser]\n"
        "\n"
        "[debug]\n"
    ).arg(m_liveUser);
    if (!writeFile(path, contents)) return false;
    emit logInfo(QStringLiteral("GDM configuration written as alternative."));
    return true;
}

bool DisplayManagerConfigurator::createLiveUser()
{
    const QString passwd = m_targetRoot + QStringLiteral("/etc/passwd");
    const QString shadow = m_targetRoot + QStringLiteral("/etc/shadow");
    const QString group = m_targetRoot + QStringLiteral("/etc/group");

    // Append live user entries if not present.
    auto appendIfMissing = [](const QString &path, const QString &line) {
        QFile file(path);
        QString content;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            content = QString::fromUtf8(file.readAll());
        }
        if (!content.contains(line.section(QLatin1Char(':'), 0, 0) + QLatin1String(":"))) {
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream s(&file);
                s << line;
            }
        }
    };

    appendIfMissing(passwd, m_liveUser + QStringLiteral(":x:1000:1000:Live User:/home/live:/bin/bash\n"));
    appendIfMissing(group, QStringLiteral("live:x:1000:\n"));
    appendIfMissing(group, QStringLiteral("sudo:x:27:%1\n").arg(m_liveUser));
    appendIfMissing(shadow, m_liveUser + QStringLiteral(":!:0:0:99999:7:::\n"));

    QDir().mkpath(m_targetRoot + QStringLiteral("/home/") + m_liveUser);

    emit logInfo(QStringLiteral("Live user '%1' configured.").arg(m_liveUser));
    return true;
}

bool DisplayManagerConfigurator::writeFile(const QString &path, const QString &contents)
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
