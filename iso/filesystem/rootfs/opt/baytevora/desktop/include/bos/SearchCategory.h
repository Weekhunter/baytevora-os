#pragma once

#include <QObject>

namespace bos::shell {

/**
 * @brief Categories for searchable items in the Baytevora Search Service.
 *
 * SearchCategory is exposed to QML as SearchCategory so QML components can
 * compare result categories using SearchCategory.Application, SearchCategory.Setting,
 * SearchCategory.Desktop, and SearchCategory.Command.
 */
class SearchCategory : public QObject {
    Q_OBJECT

public:
    enum Value {
        Application,
        Setting,
        Desktop,
        Command
    };
    Q_ENUM(Value)

    explicit SearchCategory(QObject *parent = nullptr);
};

} // namespace bos::shell
