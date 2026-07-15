#pragma once

#include <QObject>
#include <QString>

namespace bos::shell {

/**
 * @brief Category enum values used by the Baytevora Store.
 *
 * StoreCategoryEnum is exposed to QML as StoreCategory so the store UI can
 * filter by Featured, Productivity, Development, Utilities, System, and
 * Entertainment.
 */
class StoreCategoryEnum : public QObject {
    Q_OBJECT

public:
    enum Value {
        Featured,
        Productivity,
        Development,
        Utilities,
        System,
        Entertainment
    };
    Q_ENUM(Value)

    explicit StoreCategoryEnum(QObject *parent = nullptr);

    static QString name(StoreCategoryEnum::Value category);
};

} // namespace bos::shell
