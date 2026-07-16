#pragma once

#include <QJsonObject>
#include <QObject>
#include <QVariantMap>

namespace bos::shell {

/**
 * @brief Loads and saves the Baytevora OS first-boot and system configuration.
 *
 * SettingsPersistence reads/writes a JSON file in the platform config location
 * (e.g., ~/.config/Baytevora/first-boot.json). It is used by FirstBootManager,
 * WelcomeManager, and Application to decide startup flow and to restore user
 * preferences.
 */
class SettingsPersistence : public QObject {
    Q_OBJECT

public:
    explicit SettingsPersistence(QObject *parent = nullptr);

    QVariantMap load() const;
    bool save(const QVariantMap &settings) const;

    QString configPath() const;
    QString configDir() const;

private:
    QJsonObject variantMapToJsonObject(const QVariantMap &map) const;
    QVariantMap jsonObjectToVariantMap(const QJsonObject &object) const;
};

} // namespace bos::shell
