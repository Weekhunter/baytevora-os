#include "bos/PackageTransaction.h"

namespace bos::shell {

PackageOperation::PackageOperation(QObject *parent)
    : QObject(parent)
{
}

PackageTransactionState::PackageTransactionState(QObject *parent)
    : QObject(parent)
{
}

QVariantMap PackageTransaction::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("transactionId")] = transactionId;
    map[QStringLiteral("operation")] = static_cast<int>(operation);
    map[QStringLiteral("operationName")] = operationName();
    map[QStringLiteral("packageList")] = packageList;
    map[QStringLiteral("state")] = static_cast<int>(state);
    map[QStringLiteral("stateName")] = stateName();
    map[QStringLiteral("progress")] = progress;
    map[QStringLiteral("errorMessage")] = errorMessage;
    map[QStringLiteral("startTime")] = startTime.toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    map[QStringLiteral("finishTime")] = finishTime.toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    return map;
}

QString PackageTransaction::operationName() const
{
    switch (operation) {
    case PackageOperation::Install:
        return QStringLiteral("Install");
    case PackageOperation::Remove:
        return QStringLiteral("Remove");
    case PackageOperation::Update:
        return QStringLiteral("Update");
    }
    return QStringLiteral("Unknown");
}

QString PackageTransaction::stateName() const
{
    switch (state) {
    case PackageTransactionState::Pending:
        return QStringLiteral("Pending");
    case PackageTransactionState::Running:
        return QStringLiteral("Running");
    case PackageTransactionState::Completed:
        return QStringLiteral("Completed");
    case PackageTransactionState::Failed:
        return QStringLiteral("Failed");
    case PackageTransactionState::Cancelled:
        return QStringLiteral("Cancelled");
    }
    return QStringLiteral("Unknown");
}

} // namespace bos::shell
