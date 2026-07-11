#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Categories exposed by the Baytevora Store.
 *
 * StoreCategory is exposed to QML as StoreCategory so the store UI can filter
 * by Featured, Productivity, Development, Utilities, System, and
 * Entertainment.
 */
class StoreCategory : public QObject {
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

    explicit StoreCategory(QObject *parent = nullptr);

    static QString name(StoreCategory::Value category);
};

} // namespace bos::shell
