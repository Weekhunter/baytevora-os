#pragma once

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Operation type for a package transaction.
 */
class PackageOperation : public QObject {
    Q_OBJECT

public:
    enum Value {
        Install,
        Remove,
        Update
    };
    Q_ENUM(Value)

    explicit PackageOperation(QObject *parent = nullptr);
};

/**
 * @brief State of a package transaction.
 */
class PackageTransactionState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Pending,
        Running,
        Completed,
        Failed,
        Cancelled
    };
    Q_ENUM(Value)

    explicit PackageTransactionState(QObject *parent = nullptr);
};

/**
 * @brief Model for a single package installation, removal, or update transaction.
 */
struct PackageTransaction {
    QString transactionId;
    PackageOperation::Value operation = PackageOperation::Install;
    QStringList packageList;
    PackageTransactionState::Value state = PackageTransactionState::Pending;
    int progress = 0;
    QString errorMessage;
    QDateTime startTime;
    QDateTime finishTime;

    QVariantMap toMap() const;
    QString operationName() const;
    QString stateName() const;
};

} // namespace bos::shell
