#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Model for a local or future remote package repository.
 */
struct PackageRepository {
    QString repositoryId;
    QString name;
    bool enabled = true;
    int priority = 100;
    QString localPath;

    QVariantMap toMap() const;
};

} // namespace bos::shell
