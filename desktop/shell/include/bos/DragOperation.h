#pragma once

#include <QPoint>
#include <QString>
#include <QVariantMap>

#include "bos/DragData.h"
#include "bos/DragOperationState.h"

namespace bos::shell {

/**
 * @brief Represents one active drag session.
 *
 * DragOperation stores the source identifier, target identifier, payload,
 * current pointer position, and lifecycle state. It is converted to a
 * QVariantMap when exposed to QML.
 */
struct DragOperation {
    DragOperationState::Value state = DragOperationState::Idle;
    QString source;
    QString target;
    DragData data;
    QPoint position;

    QVariantMap toMap() const;

    bool isActive() const;

private:
    QString stateToString() const;
};

} // namespace bos::shell
