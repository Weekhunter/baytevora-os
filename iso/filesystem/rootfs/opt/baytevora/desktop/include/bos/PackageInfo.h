#pragma once

#include <QString>
#include <QVariantMap>

#include "bos/PackageState.h"
#include "bos/PackageType.h"

namespace bos::shell {

/**
 * @brief Lightweight immutable data model for a Baytevora package.
 *
 * PackageInfo carries packageId, name, version, description, developer,
 * category, installed flag, type, state, and size. It is exposed to QML as a
 * QVariantMap.
 */
struct PackageInfo {
    QString packageId;
    QString name;
    QString version;
    QString description;
    QString developer;
    QString category;
    bool installed = false;
    PackageType::Value packageType = PackageType::Application;
    PackageState::Value state = PackageState::Available;
    QString size;

    QVariantMap toMap() const;
};

} // namespace bos::shell
