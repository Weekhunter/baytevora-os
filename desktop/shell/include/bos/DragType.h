#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Enum describing the kind of payload carried by a drag operation.
 *
 * DragType is exposed to QML as DragType so components can request and
 * inspect drags using DragType.Text, DragType.FilePath, DragType.DesktopItem,
 * and DragType.Application.
 */
class DragType : public QObject {
    Q_OBJECT

public:
    enum Value {
        Text,
        FilePath,
        DesktopItem,
        Application
    };
    Q_ENUM(Value)

    explicit DragType(QObject *parent = nullptr);
};

} // namespace bos::shell
