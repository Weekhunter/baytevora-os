#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Model for a package dependency relationship.
 */
struct PackageDependency {
    QString packageId;
    QString dependencyId;
    QString minimumVersion;
    bool optional = false;

    QVariantMap toMap() const;
};

} // namespace bos::shell
