#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Model for a Baytevora Store category.
 */
struct StoreCategory {
    int categoryId = 0;
    QString name;
    QString icon;
    int applicationCount = 0;

    QVariantMap toMap() const;
};

} // namespace bos::shell
