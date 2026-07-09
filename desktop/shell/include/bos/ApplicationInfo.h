#pragma once

#include <QVariantMap>
#include <QString>

namespace bos::shell {

/**
 * @brief Lightweight data model representing a BOS desktop application.
 *
 * ApplicationInfo stores metadata for an application and can be converted to a
 * QVariantMap for QML consumption.
 */
class ApplicationInfo {
public:
    ApplicationInfo() = default;

    ApplicationInfo(const QString &id,
                    const QString &name,
                    const QString &description,
                    const QString &version,
                    const QString &category,
                    const QString &iconName,
                    const QString &executable,
                    bool singleInstance)
        : m_id(id)
        , m_name(name)
        , m_description(description)
        , m_version(version)
        , m_category(category)
        , m_iconName(iconName)
        , m_executable(executable)
        , m_singleInstance(singleInstance)
    {
    }

    QString id() const { return m_id; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    QString version() const { return m_version; }
    QString category() const { return m_category; }
    QString iconName() const { return m_iconName; }
    QString executable() const { return m_executable; }
    bool singleInstance() const { return m_singleInstance; }

    void setId(const QString &id) { m_id = id; }
    void setName(const QString &name) { m_name = name; }
    void setDescription(const QString &description) { m_description = description; }
    void setVersion(const QString &version) { m_version = version; }
    void setCategory(const QString &category) { m_category = category; }
    void setIconName(const QString &iconName) { m_iconName = iconName; }
    void setExecutable(const QString &executable) { m_executable = executable; }
    void setSingleInstance(bool singleInstance) { m_singleInstance = singleInstance; }

    /**
     * @return A QVariantMap representation suitable for QML.
     */
    QVariantMap toMap() const
    {
        return {
            {QStringLiteral("id"), m_id},
            {QStringLiteral("name"), m_name},
            {QStringLiteral("description"), m_description},
            {QStringLiteral("version"), m_version},
            {QStringLiteral("category"), m_category},
            {QStringLiteral("iconName"), m_iconName},
            {QStringLiteral("executable"), m_executable},
            {QStringLiteral("singleInstance"), m_singleInstance}
        };
    }

private:
    QString m_id;
    QString m_name;
    QString m_description;
    QString m_version;
    QString m_category;
    QString m_iconName;
    QString m_executable;
    bool m_singleInstance = false;
};

} // namespace bos::shell
