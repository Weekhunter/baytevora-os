#include "bldf/ComponentInstaller.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

namespace bldf {

namespace {

bool copyRecursively(const QString &source, const QString &target)
{
    const QFileInfo info(source);
    if (!info.exists()) return false;

    if (info.isDir()) {
        QDir targetDir(target);
        if (!targetDir.exists() && !targetDir.mkpath(QStringLiteral("."))) return false;
        const QDir sourceDir(source);
        const auto entries = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);
        for (const QString &entry : entries) {
            if (!copyRecursively(sourceDir.absoluteFilePath(entry), target + QStringLiteral("/") + entry))
                return false;
        }
        return true;
    }

    QFile targetFile(target);
    if (targetFile.exists() && !targetFile.remove()) return false;
    return QFile::copy(source, target);
}

} // namespace

ComponentInstaller::ComponentInstaller(QObject *parent)
    : QObject(parent)
{
}

QString ComponentInstaller::sourceRoot() const { return m_sourceRoot; }
void ComponentInstaller::setSourceRoot(const QString &value)
{
    if (m_sourceRoot == value) return;
    m_sourceRoot = value;
    emit sourceRootChanged();
}

QString ComponentInstaller::targetRoot() const { return m_targetRoot; }
void ComponentInstaller::setTargetRoot(const QString &value)
{
    if (m_targetRoot == value) return;
    m_targetRoot = value;
    emit targetRootChanged();
}

bool ComponentInstaller::installAll()
{
    if (m_sourceRoot.isEmpty() || m_targetRoot.isEmpty()) {
        emit logError(QStringLiteral("sourceRoot and targetRoot must be set."));
        return false;
    }
    return installDesktop() && installInstaller() && installBranding() && installServices() && installPackageManagerHook();
}

bool ComponentInstaller::installDesktop()
{
    const QString source = m_sourceRoot + QStringLiteral("/desktop/shell");
    const QString target = m_targetRoot + QStringLiteral("/opt/baytevora/desktop");
    QDir().mkpath(target);
    if (!copyRecursively(source, target)) {
        emit logError(QStringLiteral("Failed to install desktop shell."));
        return false;
    }
    if (!createSymlink(QStringLiteral("/opt/baytevora/desktop/build/Baytevora_OS_Shell"),
                       m_targetRoot + QStringLiteral("/usr/bin/baytevora-desktop"))) {
        emit logWarning(QStringLiteral("Could not create baytevora-desktop symlink."));
    }
    emit logInfo(QStringLiteral("Desktop shell installed."));
    return true;
}

bool ComponentInstaller::installInstaller()
{
    const QString source = m_sourceRoot + QStringLiteral("/installer");
    const QString target = m_targetRoot + QStringLiteral("/opt/baytevora/installer");
    QDir().mkpath(target);
    if (!copyRecursively(source, target)) {
        emit logError(QStringLiteral("Failed to install installer."));
        return false;
    }
    if (!createSymlink(QStringLiteral("/opt/baytevora/installer/build/Baytevora_OS_Installer"),
                       m_targetRoot + QStringLiteral("/usr/bin/baytevora-installer"))) {
        emit logWarning(QStringLiteral("Could not create baytevora-installer symlink."));
    }
    emit logInfo(QStringLiteral("Installer installed."));
    return true;
}

bool ComponentInstaller::installBranding()
{
    const QString projectRoot = QFileInfo(m_sourceRoot).dir().absolutePath();
    const QString source = projectRoot + QStringLiteral("/tasks/Branding");
    const QString target = m_targetRoot + QStringLiteral("/usr/share/baytevora/branding");
    QDir().mkpath(target);
    if (QFile::exists(source)) {
        if (!copyRecursively(source, target)) {
            emit logError(QStringLiteral("Failed to install branding assets."));
            return false;
        }
    } else {
        emit logWarning(QStringLiteral("Branding source not found at %1").arg(source));
    }
    emit logInfo(QStringLiteral("Branding assets installed."));
    return true;
}

bool ComponentInstaller::installServices()
{
    const QString servicesTarget = m_targetRoot + QStringLiteral("/opt/baytevora/services");
    QDir().mkpath(servicesTarget);

    const QString storageSource = m_sourceRoot + QStringLiteral("/desktop/shell/services/storage");
    if (QFile::exists(storageSource)) {
        copyRecursively(storageSource, servicesTarget + QStringLiteral("/storage"));
    }

    const QString printingSource = m_sourceRoot + QStringLiteral("/desktop/shell/services/printing");
    if (QFile::exists(printingSource)) {
        copyRecursively(printingSource, servicesTarget + QStringLiteral("/printing"));
    }

    const QString appSource = m_sourceRoot + QStringLiteral("/desktop/shell/services/application");
    if (QFile::exists(appSource)) {
        copyRecursively(appSource, servicesTarget + QStringLiteral("/application"));
    }

    emit logInfo(QStringLiteral("Baytevora services installed."));
    return true;
}

bool ComponentInstaller::installPackageManagerHook()
{
    const QString dpkgStatus = m_targetRoot + QStringLiteral("/var/lib/dpkg/status");
    if (!QFile::exists(dpkgStatus)) {
        emit logWarning(QStringLiteral("dpkg status not found; creating minimal placeholder."));
        QDir().mkpath(QFileInfo(dpkgStatus).absolutePath());
        QFile file(dpkgStatus);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << "Package: baytevora-base\nStatus: install ok installed\nVersion: 0.1-alpha\nDescription: Baytevora OS base placeholder\n\n";
        }
    }

    const QString hookPath = m_targetRoot + QStringLiteral("/usr/lib/baytevora/package-manager-backend");
    QDir().mkpath(QFileInfo(hookPath).absolutePath());
    QFile hook(hookPath);
    if (hook.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&hook);
        stream << "#!/bin/sh\n";
        stream << "# Baytevora Package Manager backend (Alpha read-only hook)\n";
        stream << "# Reads installed packages from /var/lib/dpkg/status\n";
        stream << "cat /var/lib/dpkg/status\n";
        hook.setPermissions(QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                            QFile::ReadGroup | QFile::ExeGroup |
                            QFile::ReadOther | QFile::ExeOther);
    }
    return writeRegistry();
}

bool ComponentInstaller::copyDirectory(const QString &source, const QString &target)
{
    return copyRecursively(source, target);
}

bool ComponentInstaller::createSymlink(const QString &target, const QString &link)
{
    QFile::remove(link);
    return QFile::link(target, link);
}

bool ComponentInstaller::writeRegistry()
{
    const QString target = m_targetRoot + QStringLiteral("/opt/baytevora/registry.json");
    QJsonObject registry;
    registry[QStringLiteral("distribution")] = QStringLiteral("debian");
    registry[QStringLiteral("version")] = QStringLiteral("0.1 Alpha");
    QJsonArray components;
    const QStringList names = {
        QStringLiteral("Desktop Shell"), QStringLiteral("Installer"),
        QStringLiteral("Branding"), QStringLiteral("StorageManager"),
        QStringLiteral("Printing Framework"), QStringLiteral("Application Framework")
    };
    for (const QString &name : names) {
        QJsonObject obj;
        obj[QStringLiteral("name")] = name;
        obj[QStringLiteral("version")] = QStringLiteral("0.1");
        components.append(obj);
    }
    registry[QStringLiteral("components")] = components;

    QFile file(target);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    file.write(QJsonDocument(registry).toJson(QJsonDocument::Indented));
    emit logInfo(QStringLiteral("Component registry written."));
    return true;
}

} // namespace bldf
