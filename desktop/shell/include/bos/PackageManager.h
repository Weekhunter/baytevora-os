#pragma once

#include <QObject>
#include <QVariantList>

#include <memory>

#include "bos/PackageInfo.h"

namespace bos::shell {

class NotificationManager;
class PackageDatabase;

/**
 * @brief Coordinates the Baytevora Package Manager (BPM) placeholder lifecycle.
 *
 * PackageManager owns a PackageDatabase of metadata-only packages. All
 * operations in Sprint 25 are placeholders: they log, notify, and change the
 * stored state, but do not touch the filesystem, network, or archives.
 */
class PackageManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList packages READ packages NOTIFY packagesChanged)
    Q_PROPERTY(QVariantList installedPackages READ installedPackages NOTIFY packagesChanged)
    Q_PROPERTY(QVariantList availablePackages READ availablePackages NOTIFY packagesChanged)
    Q_PROPERTY(int packageCount READ packageCount NOTIFY packagesChanged)

public:
    explicit PackageManager(QObject *parent = nullptr);
    ~PackageManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    QVariantList packages() const;
    QVariantList installedPackages() const;
    QVariantList availablePackages() const;
    int packageCount() const;

    Q_INVOKABLE QVariantMap package(const QString &packageId) const;
    Q_INVOKABLE void installPackage(const QString &packageId);
    Q_INVOKABLE void uninstallPackage(const QString &packageId);
    Q_INVOKABLE void enablePackage(const QString &packageId);
    Q_INVOKABLE void disablePackage(const QString &packageId);

    Q_INVOKABLE QString stateName(int state) const;
    Q_INVOKABLE QString typeName(int type) const;

signals:
    void packagesChanged();

private:
    void notify(const QString &title, const QString &message);
    void emitChange();

    std::unique_ptr<PackageDatabase> m_database;
    NotificationManager *m_notificationManager = nullptr;
};

} // namespace bos::shell
