#include "bos/PackageManager.h"

#include <QDebug>

#include "bos/NotificationManager.h"
#include "bos/PackageDatabase.h"

namespace bos::shell {

PackageManager::PackageManager(QObject *parent)
    : QObject(parent)
    , m_database(std::make_unique<PackageDatabase>())
{
    qDebug() << QStringLiteral("[BDE] PackageManager initialized");
}

PackageManager::~PackageManager() = default;

void PackageManager::setNotificationManager(NotificationManager *notificationManager)
{
    m_notificationManager = notificationManager;
}

QVariantList PackageManager::packages() const
{
    QVariantList list;
    for (const PackageInfo &info : m_database->allPackages()) {
        list.append(info.toMap());
    }
    return list;
}

QVariantList PackageManager::installedPackages() const
{
    QVariantList list;
    for (const PackageInfo &info : m_database->allPackages()) {
        if (info.installed) {
            list.append(info.toMap());
        }
    }
    return list;
}

QVariantList PackageManager::availablePackages() const
{
    QVariantList list;
    for (const PackageInfo &info : m_database->allPackages()) {
        if (!info.installed) {
            list.append(info.toMap());
        }
    }
    return list;
}

int PackageManager::packageCount() const
{
    return m_database->allPackages().size();
}

QVariantMap PackageManager::package(const QString &packageId) const
{
    return m_database->package(packageId).toMap();
}

void PackageManager::installPackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return;
    }

    const PackageInfo info = m_database->package(packageId);
    if (info.installed) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is already installed.").arg(info.name));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Install requested for") << packageId;
    m_database->setState(packageId, PackageState::Installed);
    emitChange();
    notify(QStringLiteral("Package"), QStringLiteral("%1 install requested.").arg(info.name));
}

void PackageManager::uninstallPackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return;
    }

    const PackageInfo info = m_database->package(packageId);
    if (!info.installed) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is not installed.").arg(info.name));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Uninstall requested for") << packageId;
    m_database->setState(packageId, PackageState::Available);
    emitChange();
    notify(QStringLiteral("Package"), QStringLiteral("%1 uninstall requested.").arg(info.name));
}

void PackageManager::enablePackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return;
    }

    const PackageInfo info = m_database->package(packageId);
    if (info.state != PackageState::Disabled) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is already enabled.").arg(info.name));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Enable requested for") << packageId;
    m_database->setState(packageId, PackageState::Installed);
    emitChange();
    notify(QStringLiteral("Package"), QStringLiteral("%1 enabled.").arg(info.name));
}

void PackageManager::disablePackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return;
    }

    const PackageInfo info = m_database->package(packageId);
    if (info.state == PackageState::Disabled) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is already disabled.").arg(info.name));
        return;
    }

    qDebug() << QStringLiteral("[BDE] Disable requested for") << packageId;
    m_database->setState(packageId, PackageState::Disabled);
    emitChange();
    notify(QStringLiteral("Package"), QStringLiteral("%1 disabled.").arg(info.name));
}

QString PackageManager::stateName(int state) const
{
    switch (static_cast<PackageState::Value>(state)) {
    case PackageState::Available:
        return QStringLiteral("Available");
    case PackageState::Installed:
        return QStringLiteral("Installed");
    case PackageState::UpdateAvailable:
        return QStringLiteral("Update Available");
    case PackageState::Disabled:
        return QStringLiteral("Disabled");
    }
    return QStringLiteral("Unknown");
}

QString PackageManager::typeName(int type) const
{
    switch (static_cast<PackageType::Value>(type)) {
    case PackageType::System:
        return QStringLiteral("System");
    case PackageType::Application:
        return QStringLiteral("Application");
    case PackageType::Library:
        return QStringLiteral("Library");
    }
    return QStringLiteral("Unknown");
}

void PackageManager::notify(const QString &title, const QString &message)
{
    if (m_notificationManager) {
        m_notificationManager->createNotification(title, message,
                                                  QStringLiteral("Package"),
                                                  QStringLiteral("info"));
    }
}

void PackageManager::emitChange()
{
    emit packagesChanged();
}

} // namespace bos::shell
