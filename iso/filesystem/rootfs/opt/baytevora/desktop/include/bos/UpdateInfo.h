#pragma once

#include <QDateTime>
#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Lightweight immutable data model for a Baytevora update.
 *
 * UpdateInfo carries version, title, description, size, release date, and
 * type information. It is exposed to QML as a QVariantMap.
 */
struct UpdateInfo {
    QString version;
    QString title;
    QString description;
    QString size;
    QDateTime releaseDate;
    QString type;

    QVariantMap toMap() const;
};

} // namespace bos::shell
