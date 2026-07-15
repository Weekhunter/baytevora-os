#pragma once

#include <QString>
#include <QVariantMap>

#include "bos/DragType.h"

namespace bos::shell {

/**
 * @brief Lightweight immutable payload description for a drag operation.
 *
 * DragData supports text, file paths, desktop item IDs, and application IDs.
 * It does not carry binary data and is converted to a QVariantMap when sent
 * to QML.
 */
struct DragData {
    DragType::Value type = DragType::Text;
    QString value;

    QVariantMap toMap() const;

private:
    QString typeToString() const;
};

} // namespace bos::shell
