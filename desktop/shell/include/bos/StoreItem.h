#pragma once

#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "bos/StoreCategoryEnum.h"

namespace bos::shell {

/**
 * @brief Lightweight immutable model for a Baytevora Store catalog entry.
 *
 * StoreItem carries the metadata shown to the user in the store UI and is
 * exposed to QML as a QVariantMap.
 */
struct StoreItem {
    QString applicationId;
    QString name;
    QString version;
    QString developer;
    StoreCategoryEnum::Value category = StoreCategoryEnum::Utilities;
    QString shortDescription;
    QString longDescription;
    bool installed = false;
    QString installedVersion;
    QString latestVersion;
    QStringList screenshots;
    QString changelog;
    double rating = 0.0;
    QString size;
    QString iconPath;
    bool featured = false;
    int downloads = 0;

    QVariantMap toMap() const;
};

} // namespace bos::shell
