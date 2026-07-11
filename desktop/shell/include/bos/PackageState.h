#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Lifecycle states of a Baytevora package.
 *
 * PackageState is exposed to QML as PackageState so the package UI can react to
 * Available, Installed, UpdateAvailable, and Disabled.
 */
class PackageState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Available,
        Installed,
        UpdateAvailable,
        Disabled
    };
    Q_ENUM(Value)

    explicit PackageState(QObject *parent = nullptr);
};

} // namespace bos::shell
