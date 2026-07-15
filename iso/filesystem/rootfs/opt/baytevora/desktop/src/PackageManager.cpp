#include "bos/PackageManager.h"

#include <QDebug>
#include <QUuid>

#include "bos/NotificationManager.h"
#include "bos/PackageDatabase.h"

namespace bos::shell {

PackageManager::PackageManager(QObject *parent)
    : QObject(parent)
    , m_database(std::make_unique<PackageDatabase>())
{
    seedDependencies();
    seedRepositories();
    seedTransactions();
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
        list.append(buildPackage(info).toMap());
    }
    return list;
}

QVariantList PackageManager::installedPackages() const
{
    QVariantList list;
    for (const PackageInfo &info : m_database->allPackages()) {
        if (info.installed) {
            list.append(buildPackage(info).toMap());
        }
    }
    return list;
}

QVariantList PackageManager::availablePackages() const
{
    QVariantList list;
    for (const PackageInfo &info : m_database->allPackages()) {
        if (!info.installed) {
            list.append(buildPackage(info).toMap());
        }
    }
    return list;
}

QVariantList PackageManager::repositories() const
{
    QVariantList list;
    for (const PackageRepository &repo : m_repositories) {
        list.append(repo.toMap());
    }
    return list;
}

QVariantList PackageManager::transactions() const
{
    return transactionMaps();
}

int PackageManager::packageCount() const
{
    return m_database->allPackages().size();
}

QVariantMap PackageManager::package(const QString &packageId) const
{
    return buildPackage(m_database->package(packageId)).toMap();
}

QVariantMap PackageManager::applicationPackage(const QString &applicationId) const
{
    for (const PackageInfo &info : m_database->allPackages()) {
        if (info.packageId == applicationId) {
            return buildPackage(info).toMap();
        }
    }
    return QVariantMap();
}

QVariantList PackageManager::dependenciesFor(const QString &packageId) const
{
    QVariantList list;
    for (const PackageDependency &dep : m_dependencies.value(packageId)) {
        list.append(dep.toMap());
    }
    return list;
}

QVariantList PackageManager::missingDependencies(const QString &packageId) const
{
    QVariantList list;
    for (const PackageDependency &dep : m_dependencies.value(packageId)) {
        const PackageInfo target = m_database->package(dep.dependencyId);
        if (target.packageId.isEmpty() || !target.installed) {
            list.append(dep.toMap());
        }
    }
    return list;
}

QVariantList PackageManager::installationPlan(const QString &packageId) const
{
    QVariantList plan;
    if (!m_database->contains(packageId)) {
        return plan;
    }
    plan.append(packageId);
    for (const PackageDependency &dep : m_dependencies.value(packageId)) {
        const PackageInfo target = m_database->package(dep.dependencyId);
        if (!target.installed && !plan.contains(dep.dependencyId)) {
            plan.append(dep.dependencyId);
        }
    }
    return plan;
}

QVariantList PackageManager::updatePlan() const
{
    QVariantList plan;
    for (const PackageInfo &info : m_database->allPackages()) {
        if (info.installed && info.state == PackageState::UpdateAvailable) {
            plan.append(info.packageId);
        }
    }
    return plan;
}

bool PackageManager::installPackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return false;
    }

    const PackageInfo info = m_database->package(packageId);
    if (info.installed) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is already installed.").arg(info.name));
        return false;
    }

    addTransaction(PackageOperation::Install, QStringList {packageId});
    processPendingTransactions();
    return true;
}

bool PackageManager::uninstallPackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return false;
    }

    const PackageInfo info = m_database->package(packageId);
    if (!info.installed) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is not installed.").arg(info.name));
        return false;
    }

    addTransaction(PackageOperation::Remove, QStringList {packageId});
    processPendingTransactions();
    return true;
}

bool PackageManager::updatePackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        notify(QStringLiteral("Package"), QStringLiteral("Package not found."));
        return false;
    }

    const PackageInfo info = m_database->package(packageId);
    if (!info.installed) {
        notify(QStringLiteral("Package"), QStringLiteral("%1 is not installed.").arg(info.name));
        return false;
    }

    addTransaction(PackageOperation::Update, QStringList {packageId});
    processPendingTransactions();
    return true;
}

bool PackageManager::enableRepository(const QString &repositoryId)
{
    for (PackageRepository &repo : m_repositories) {
        if (repo.repositoryId == repositoryId) {
            repo.enabled = true;
            emit repositoriesChanged();
            return true;
        }
    }
    return false;
}

bool PackageManager::disableRepository(const QString &repositoryId)
{
    for (PackageRepository &repo : m_repositories) {
        if (repo.repositoryId == repositoryId) {
            repo.enabled = false;
            emit repositoriesChanged();
            return true;
        }
    }
    return false;
}

bool PackageManager::setRepositoryPriority(const QString &repositoryId, int priority)
{
    for (PackageRepository &repo : m_repositories) {
        if (repo.repositoryId == repositoryId) {
            repo.priority = priority;
            emit repositoriesChanged();
            return true;
        }
    }
    return false;
}

bool PackageManager::cancelTransaction(const QString &transactionId)
{
    PackageTransaction *tx = findTransaction(transactionId);
    if (!tx || tx->state != PackageTransactionState::Running) {
        return false;
    }
    tx->state = PackageTransactionState::Cancelled;
    tx->finishTime = QDateTime::currentDateTimeUtc();
    if (QTimer *timer = m_timers.value(transactionId)) {
        timer->stop();
    }
    emit transactionsChanged();
    notify(QStringLiteral("Transaction Cancelled"),
           QStringLiteral("Transaction %1 cancelled.").arg(transactionId));
    return true;
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

QString PackageManager::operationName(int operation) const
{
    switch (static_cast<PackageOperation::Value>(operation)) {
    case PackageOperation::Install:
        return QStringLiteral("Install");
    case PackageOperation::Remove:
        return QStringLiteral("Remove");
    case PackageOperation::Update:
        return QStringLiteral("Update");
    }
    return QStringLiteral("Unknown");
}

void PackageManager::seedDependencies()
{
    auto add = [this](const QString &packageId, const PackageDependency &dep) {
        m_dependencies[packageId].append(dep);
    };

    PackageDependency browserNetwork;
    browserNetwork.packageId = QStringLiteral("bos.browser");
    browserNetwork.dependencyId = QStringLiteral("bos.network-manager");
    browserNetwork.minimumVersion = QStringLiteral("0.1.0");
    browserNetwork.optional = false;
    add(QStringLiteral("bos.browser"), browserNetwork);

    PackageDependency browserArchive;
    browserArchive.packageId = QStringLiteral("bos.browser");
    browserArchive.dependencyId = QStringLiteral("bos.archive");
    browserArchive.minimumVersion = QStringLiteral("0.1.0");
    browserArchive.optional = true;
    add(QStringLiteral("bos.browser"), browserArchive);

    PackageDependency imageViewerArchive;
    imageViewerArchive.packageId = QStringLiteral("bos.image-viewer");
    imageViewerArchive.dependencyId = QStringLiteral("bos.archive");
    imageViewerArchive.minimumVersion = QStringLiteral("0.1.0");
    imageViewerArchive.optional = true;
    add(QStringLiteral("bos.image-viewer"), imageViewerArchive);
}

void PackageManager::seedRepositories()
{
    PackageRepository core;
    core.repositoryId = QStringLiteral("core");
    core.name = QStringLiteral("Baytevora Core");
    core.enabled = true;
    core.priority = 100;
    core.localPath = QStringLiteral("/var/lib/baytevora/repos/core");
    m_repositories.append(core);

    PackageRepository community;
    community.repositoryId = QStringLiteral("community");
    community.name = QStringLiteral("Baytevora Community");
    community.enabled = false;
    community.priority = 200;
    community.localPath = QStringLiteral("/var/lib/baytevora/repos/community");
    m_repositories.append(community);

    PackageRepository enterprise;
    enterprise.repositoryId = QStringLiteral("enterprise");
    enterprise.name = QStringLiteral("Enterprise (placeholder)");
    enterprise.enabled = false;
    enterprise.priority = 300;
    enterprise.localPath = QStringLiteral("/var/lib/baytevora/repos/enterprise");
    m_repositories.append(enterprise);
}

void PackageManager::seedTransactions()
{
    // No pre-existing transactions at startup.
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

Package PackageManager::buildPackage(const PackageInfo &info) const
{
    Package package;
    package.packageId = info.packageId;
    package.applicationId = info.packageId;
    package.name = info.name;
    package.version = info.version;
    package.architecture = QStringLiteral("x86_64");
    package.size = info.size;
    package.installed = info.installed;
    package.description = info.description;
    package.category = info.category;
    package.developer = info.developer;
    package.state = static_cast<int>(info.state);
    package.packageType = static_cast<int>(info.packageType);
    return package;
}

bool PackageManager::enablePackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        return false;
    }
    m_database->setState(packageId, PackageState::Installed);
    emitChange();
    return true;
}

bool PackageManager::disablePackage(const QString &packageId)
{
    if (!m_database->contains(packageId)) {
        return false;
    }
    m_database->setState(packageId, PackageState::Disabled);
    emitChange();
    return true;
}

QVariantList PackageManager::transactionMaps() const
{
    QVariantList list;
    for (const auto &tx : m_transactions) {
        list.append(tx->toMap());
    }
    return list;
}

PackageTransaction *PackageManager::findTransaction(const QString &transactionId)
{
    for (const auto &tx : m_transactions) {
        if (tx->transactionId == transactionId) {
            return tx.get();
        }
    }
    return nullptr;
}

void PackageManager::addTransaction(PackageOperation::Value operation, const QStringList &packageList)
{
    auto tx = std::make_unique<PackageTransaction>();
    tx->transactionId = QUuid::createUuid().toString(QUuid::WithoutBraces).left(8);
    tx->operation = operation;
    tx->packageList = packageList;
    tx->state = PackageTransactionState::Pending;
    tx->progress = 0;
    m_transactions.append(std::move(tx));
    emit transactionsChanged();
}

void PackageManager::processPendingTransactions()
{
    for (const auto &tx : m_transactions) {
        if (tx->state != PackageTransactionState::Pending) {
            continue;
        }

        tx->state = PackageTransactionState::Running;
        tx->startTime = QDateTime::currentDateTimeUtc();
        emit transactionsChanged();

        const QString txId = tx->transactionId;
        QTimer *timer = new QTimer(this);
        timer->setInterval(200);
        m_timers.insert(txId, timer);
        connect(timer, &QTimer::timeout, this, [this, txId]() { advanceTransaction(txId); });
        timer->start();
        return; // process one at a time
    }
}

void PackageManager::advanceTransaction(const QString &transactionId)
{
    PackageTransaction *tx = findTransaction(transactionId);
    if (!tx || tx->state != PackageTransactionState::Running) {
        return;
    }

    tx->progress += 20;
    emit transactionsChanged();

    if (tx->progress >= 100) {
        const QString packageId = tx->packageList.isEmpty() ? QString() : tx->packageList.first();
        if (tx->operation == PackageOperation::Install && m_database->contains(packageId)) {
            m_database->setState(packageId, PackageState::Installed);
        } else if (tx->operation == PackageOperation::Remove && m_database->contains(packageId)) {
            m_database->setState(packageId, PackageState::Available);
        } else if (tx->operation == PackageOperation::Update && m_database->contains(packageId)) {
            m_database->setState(packageId, PackageState::Installed);
        }
        completeTransaction(transactionId, true);
    }
}

void PackageManager::completeTransaction(const QString &transactionId, bool success, const QString &error)
{
    PackageTransaction *tx = findTransaction(transactionId);
    if (!tx) {
        return;
    }

    if (QTimer *timer = m_timers.take(transactionId)) {
        timer->stop();
        timer->deleteLater();
    }

    tx->state = success ? PackageTransactionState::Completed : PackageTransactionState::Failed;
    tx->errorMessage = error;
    tx->finishTime = QDateTime::currentDateTimeUtc();

    // Keep the transaction log bounded so memory does not grow indefinitely.
    while (m_transactions.size() > 50) {
        m_transactions.removeFirst();
    }

    emit transactionsChanged();
    emitChange();

    const QString packageId = tx->packageList.isEmpty() ? QString() : tx->packageList.first();
    const PackageInfo info = m_database->package(packageId);
    if (success) {
        switch (tx->operation) {
        case PackageOperation::Install:
            notify(QStringLiteral("Package Installed"),
                   QStringLiteral("%1 installed successfully.").arg(info.name));
            break;
        case PackageOperation::Remove:
            notify(QStringLiteral("Package Removed"),
                   QStringLiteral("%1 removed successfully.").arg(info.name));
            break;
        case PackageOperation::Update:
            notify(QStringLiteral("Package Updated"),
                   QStringLiteral("%1 updated successfully.").arg(info.name));
            break;
        }
    } else {
        notify(QStringLiteral("Transaction Failed"),
               QStringLiteral("Transaction %1 failed: %2").arg(transactionId, error));
    }

    // Continue with next pending transaction.
    processPendingTransactions();
}

} // namespace bos::shell
