#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Lifecycle states of the UpdateManager.
 *
 * UpdateState is exposed to QML as UpdateState so the update UI can react to
 * Idle, Checking, UpdatesAvailable, Downloading, ReadyToInstall, UpToDate,
 * and Error.
 */
class UpdateState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Idle,
        Checking,
        UpdatesAvailable,
        Downloading,
        ReadyToInstall,
        UpToDate,
        Error
    };
    Q_ENUM(Value)

    explicit UpdateState(QObject *parent = nullptr);
};

} // namespace bos::shell
