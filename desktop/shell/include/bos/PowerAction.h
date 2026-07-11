#pragma once

#include <QString>
#include <QVariantMap>

#include "bos/PowerActionType.h"

namespace bos::shell {

/**
 * @brief Represents a single power action in the Baytevora Power Management Service.
 *
 * PowerAction is a plain value object. It is converted to a QVariantMap when
 * exposed to QML so the power menu can consume it directly.
 */
struct PowerAction {
    QString id;
    QString title;
    QString description;
    PowerActionType::Value type = PowerActionType::Shutdown;
    bool enabled = true;
    QString iconName;

    QVariantMap toMap() const;
};

} // namespace bos::shell
