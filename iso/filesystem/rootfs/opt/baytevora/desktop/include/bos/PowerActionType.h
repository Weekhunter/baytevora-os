#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Enum for power action types in the Baytevora Power Management Service.
 *
 * PowerActionType is exposed to QML as PowerActionType so QML components can
 * compare action types and request specific actions.
 */
class PowerActionType : public QObject {
    Q_OBJECT

public:
    enum Value {
        Shutdown,
        Restart,
        LogOut,
        Lock,
        Sleep,
        Hibernate
    };
    Q_ENUM(Value)

    explicit PowerActionType(QObject *parent = nullptr);
};

} // namespace bos::shell
