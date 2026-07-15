#pragma once

#include <QHash>
#include <QList>
#include <QString>

#include "bos/PackageInfo.h"

namespace bos::shell {

/**
 * @brief Owns the set of placeholder packages for the Baytevora Package Manager.
 *
 * PackageDatabase stores package metadata only. It performs no filesystem or
 * network operations. It provides lookup by packageId and access to the full
 * package list.
 */
class PackageDatabase {
public:
    PackageDatabase();

    QList<PackageInfo> allPackages() const;
    PackageInfo package(const QString &packageId) const;
    bool contains(const QString &packageId) const;

    void setState(const QString &packageId, PackageState::Value state);

private:
    void seedPackages();

    QHash<QString, PackageInfo> m_packages;
};

} // namespace bos::shell
