#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Lifecycle states of a drag operation.
 *
 * DragOperationState is exposed to QML as DragOperationState so QML can inspect
 * the current phase of a drag using DragOperationState.Idle,
 * DragOperationState.Started, DragOperationState.Dragging,
 * DragOperationState.Dropped, and DragOperationState.Cancelled.
 */
class DragOperationState : public QObject {
    Q_OBJECT

public:
    enum Value {
        Idle,
        Started,
        Dragging,
        Dropped,
        Cancelled
    };
    Q_ENUM(Value)

    explicit DragOperationState(QObject *parent = nullptr);
};

} // namespace bos::shell
