#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Model for an available Baytevora Store application update.
 */
struct StoreUpdate {
    QString applicationId;
    QString installedVersion;
    QString availableVersion;
    bool updateAvailable = false;

    QVariantMap toMap() const;
};

} // namespace bos::shell
