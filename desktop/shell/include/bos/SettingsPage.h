#pragma once

#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Data model representing a single Settings page.
 *
 * Each page has a stable identifier and a human-readable title. The model is
 * intentionally small because Sprint 13 only needs a navigation list; more
 * metadata can be added later as the Settings application grows.
 */
class SettingsPage {
public:
    SettingsPage() = default;

    SettingsPage(const QString &id, const QString &title)
        : m_id(id)
        , m_title(title)
    {
    }

    QString id() const { return m_id; }
    QString title() const { return m_title; }

    void setId(const QString &id) { m_id = id; }
    void setTitle(const QString &title) { m_title = title; }

    QVariantMap toMap() const
    {
        return {
            {QStringLiteral("id"), m_id},
            {QStringLiteral("title"), m_title}
        };
    }

private:
    QString m_id;
    QString m_title;
};

} // namespace bos::shell
