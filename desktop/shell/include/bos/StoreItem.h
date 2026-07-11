#pragma once

#include <QString>
#include <QVariantMap>

#include "bos/StoreCategory.h"

namespace bos::shell {

/**
 * @brief Lightweight immutable model for a Baytevora Store catalog entry.
 *
 * StoreItem carries the metadata shown to the user in the store UI and is
 * exposed to QML as a QVariantMap.
 */
struct StoreItem {
    QString packageId;
    QString name;
    QString description;
    QString developer;
    QString version;
    double rating = 0.0;
    int downloads = 0;
    StoreCategory::Value category = StoreCategory::Utilities;
    bool installed = false;
    bool featured = false;
    QString iconPath;

    QVariantMap toMap() const;
};

} // namespace bos::shell
