#pragma once

#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "bos/SearchCategory.h"

namespace bos::shell {

/**
 * @brief Represents a single searchable object in the Baytevora Search Service.
 *
 * SearchItem is a plain value object. It is converted to a QVariantMap when
 * exposed to QML so that the search results list can be consumed directly.
 */
struct SearchItem {
    QString id;
    QString title;
    QString subtitle;
    SearchCategory::Value category = SearchCategory::Application;
    QStringList keywords;
    QString iconName;
    QString provider;
    bool enabled = true;

    QVariantMap toMap() const;
};

} // namespace bos::shell
