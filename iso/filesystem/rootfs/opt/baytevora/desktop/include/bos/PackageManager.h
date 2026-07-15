#pragma once

#include <QHash>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QVariantList>

#include <memory>

#include "bos/Package.h"
#include "bos/PackageDependency.h"
#include "bos/PackageInfo.h"
#include "bos/PackageRepository.h"
#include "bos/PackageTransaction.h"

namespace bos::shell {

class NotificationManager;
class PackageDatabase;

/**
 * @brief Coordinates the Baytevora Package Manager Phase 2 lifecycle.
 *
 * PackageManager owns a PackageDatabase of metadata-only packages plus
 * placeholder dependency, repository, and transaction support. All network
 * operations are forbidden in this sprint and remain no-ops.
 */
class PackageManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList packages READ packages NOTIFY packagesChanged)
    Q_PROPERTY(QVariantList installedPackages READ installedPackages NOTIFY packagesChanged)
    Q_PROPERTY(QVariantList availablePackages READ availablePackages NOTIFY packagesChanged)
    Q_PROPERTY(QVariantList repositories READ repositories NOTIFY repositoriesChanged)
    Q_PROPERTY(QVariantList transactions READ transactions NOTIFY transactionsChanged)
    Q_PROPERTY(int packageCount READ packageCount NOTIFY packagesChanged)

public:
    explicit PackageManager(QObject *parent = nullptr);
    ~PackageManager() override;

    void setNotificationManager(NotificationManager *notificationManager);

    QVariantList packages() const;
    QVariantList installedPackages() const;
    QVariantList availablePackages() const;
    QVariantList repositories() const;
    QVariantList transactions() const;
    int packageCount() const;

    Q_INVOKABLE QVariantMap package(const QString &packageId) const;
    Q_INVOKABLE QVariantMap applicationPackage(const QString &applicationId) const;
    Q_INVOKABLE QVariantList dependenciesFor(const QString &packageId) const;
    Q_INVOKABLE QVariantList missingDependencies(const QString &packageId) const;
    Q_INVOKABLE QVariantList installationPlan(const QString &packageId) const;
    Q_INVOKABLE QVariantList updatePlan() const;

    Q_INVOKABLE bool installPackage(const QString &packageId);
    Q_INVOKABLE bool uninstallPackage(const QString &packageId);
    Q_INVOKABLE bool updatePackage(const QString &packageId);
    Q_INVOKABLE bool enablePackage(const QString &packageId);
    Q_INVOKABLE bool disablePackage(const QString &packageId);
    Q_INVOKABLE bool enableRepository(const QString &repositoryId);
    Q_INVOKABLE bool disableRepository(const QString &repositoryId);
    Q_INVOKABLE bool setRepositoryPriority(const QString &repositoryId, int priority);
    Q_INVOKABLE bool cancelTransaction(const QString &transactionId);

    Q_INVOKABLE QString stateName(int state) const;
    Q_INVOKABLE QString typeName(int type) const;
    Q_INVOKABLE QString operationName(int operation) const;

signals:
    void packagesChanged();
    void repositoriesChanged();
    void transactionsChanged();

private:
    void seedDependencies();
    void seedRepositories();
    void seedTransactions();
    void notify(const QString &title, const QString &message);
    void emitChange();

    Package buildPackage(const PackageInfo &info) const;
    QVariantList transactionMaps() const;
    PackageTransaction *findTransaction(const QString &transactionId);
    void advanceTransaction(const QString &transactionId);
    void completeTransaction(const QString &transactionId, bool success, const QString &error = QString());
    void addTransaction(PackageOperation::Value operation, const QStringList &packageList);
    void processPendingTransactions();

    std::unique_ptr<PackageDatabase> m_database;
    NotificationManager *m_notificationManager = nullptr;

    QHash<QString, QList<PackageDependency>> m_dependencies;
    QList<PackageRepository> m_repositories;
    QList<std::unique_ptr<PackageTransaction>> m_transactions;
    QHash<QString, QTimer *> m_timers;
};

} // namespace bos::shell
