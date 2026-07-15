#include "bos/DragOperation.h"

namespace bos::shell {

QVariantMap DragOperation::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("state")] = static_cast<int>(state);
    map[QStringLiteral("stateName")] = stateToString();
    map[QStringLiteral("source")] = source;
    map[QStringLiteral("target")] = target;
    map[QStringLiteral("data")] = data.toMap();
    map[QStringLiteral("x")] = position.x();
    map[QStringLiteral("y")] = position.y();
    return map;
}

bool DragOperation::isActive() const
{
    return state == DragOperationState::Started
           || state == DragOperationState::Dragging;
}

QString DragOperation::stateToString() const
{
    switch (state) {
    case DragOperationState::Idle:
        return QStringLiteral("Idle");
    case DragOperationState::Started:
        return QStringLiteral("Started");
    case DragOperationState::Dragging:
        return QStringLiteral("Dragging");
    case DragOperationState::Dropped:
        return QStringLiteral("Dropped");
    case DragOperationState::Cancelled:
        return QStringLiteral("Cancelled");
    }
    return QStringLiteral("Unknown");
}

} // namespace bos::shell
