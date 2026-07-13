#pragma once

#include <QDateTime>
#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Model for an installed Baytevora Store application.
 */
struct InstalledApplication {
    QString applicationId;
    QString version;
    QDateTime installDate;
    QDateTime lastUpdated;

    QVariantMap toMap() const;
};

} // namespace bos::shell
