#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Classification of a Baytevora package.
 *
 * PackageType is exposed to QML as PackageType so the package UI can show
 * whether a package is System, Application, or Library.
 */
class PackageType : public QObject {
    Q_OBJECT

public:
    enum Value {
        System,
        Application,
        Library
    };
    Q_ENUM(Value)

    explicit PackageType(QObject *parent = nullptr);
};

} // namespace bos::shell
