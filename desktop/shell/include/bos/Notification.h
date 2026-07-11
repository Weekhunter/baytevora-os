#pragma once

#include <QDateTime>
#include <QString>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Severity level for a notification.
 */
enum class NotificationSeverity {
    Info,
    Success,
    Warning,
    Error
};

/**
 * @brief Data model representing a single BOS notification.
 *
 * Notifications are lightweight, transient messages produced by applications
 * or the system. Sprint 11 keeps them in memory only; no persistence or
 * history is implemented.
 */
class Notification {
public:
    Notification() = default;

    Notification(int id,
                 const QString &title,
                 const QString &message,
                 const QString &sourceApplication,
                 const QDateTime &timestamp,
                 NotificationSeverity severity)
        : m_id(id)
        , m_title(title)
        , m_message(message)
        , m_sourceApplication(sourceApplication)
        , m_timestamp(timestamp)
        , m_severity(severity)
    {
    }

    int id() const { return m_id; }
    QString title() const { return m_title; }
    QString message() const { return m_message; }
    QString sourceApplication() const { return m_sourceApplication; }
    QDateTime timestamp() const { return m_timestamp; }
    NotificationSeverity severity() const { return m_severity; }

    void setId(int id) { m_id = id; }
    void setTitle(const QString &title) { m_title = title; }
    void setMessage(const QString &message) { m_message = message; }
    void setSourceApplication(const QString &sourceApplication) { m_sourceApplication = sourceApplication; }
    void setTimestamp(const QDateTime &timestamp) { m_timestamp = timestamp; }
    void setSeverity(NotificationSeverity severity) { m_severity = severity; }

    /**
     * @return A QVariantMap suitable for QML bindings.
     */
    QVariantMap toMap() const
    {
        return {
            {QStringLiteral("id"), m_id},
            {QStringLiteral("title"), m_title},
            {QStringLiteral("message"), m_message},
            {QStringLiteral("sourceApplication"), m_sourceApplication},
            {QStringLiteral("timestamp"), m_timestamp},
            {QStringLiteral("severity"), severityToString(m_severity)}
        };
    }

    /**
     * @brief Converts a severity level to a string.
     */
    static QString severityToString(NotificationSeverity severity)
    {
        switch (severity) {
        case NotificationSeverity::Info:
            return QStringLiteral("info");
        case NotificationSeverity::Success:
            return QStringLiteral("success");
        case NotificationSeverity::Warning:
            return QStringLiteral("warning");
        case NotificationSeverity::Error:
            return QStringLiteral("error");
        }
        return QStringLiteral("info");
    }

private:
    int m_id = -1;
    QString m_title;
    QString m_message;
    QString m_sourceApplication;
    QDateTime m_timestamp;
    NotificationSeverity m_severity = NotificationSeverity::Info;
};

} // namespace bos::shell
