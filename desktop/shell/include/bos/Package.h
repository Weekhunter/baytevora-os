#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Rich model for a Baytevora Package Manager package entry.
 */
struct Package {
    QString packageId;
    QString applicationId;
    QString name;
    QString version;
    QString architecture = QStringLiteral("x86_64");
    QString size;
    bool installed = false;
    int state = 0;
    int packageType = 0;
    QString description;
    QString category;
    QString developer;

    QVariantMap toMap() const;
};

} // namespace bos::shell
