#include "bos/SettingsPersistence.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace bos::shell {

namespace {

constexpr char kConfigFileName[] = "first-boot.json";
constexpr char kConfigDirName[] = "Baytevora";

} // namespace

SettingsPersistence::SettingsPersistence(QObject *parent)
    : QObject(parent)
{
}

QString SettingsPersistence::configDir() const
{
    const QString baseDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    return QDir(baseDir).filePath(QStringLiteral(kConfigDirName));
}

QString SettingsPersistence::configPath() const
{
    return QDir(configDir()).filePath(QStringLiteral(kConfigFileName));
}

QVariantMap SettingsPersistence::load() const
{
    const QString path = configPath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return QVariantMap();
    }

    const QByteArray data = file.readAll();
    const QJsonDocument document = QJsonDocument::fromJson(data);
    if (!document.isObject()) {
        return QVariantMap();
    }

    return jsonObjectToVariantMap(document.object());
}

bool SettingsPersistence::save(const QVariantMap &settings) const
{
    const QString dir = configDir();
    if (!QDir().mkpath(dir)) {
        return false;
    }

    const QString path = configPath();
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    const QJsonDocument document(variantMapToJsonObject(settings));
    return file.write(document.toJson(QJsonDocument::Indented)) != -1;
}

QJsonObject SettingsPersistence::variantMapToJsonObject(const QVariantMap &map) const
{
    QJsonObject object;
    for (auto it = map.cbegin(); it != map.cend(); ++it) {
        const QVariant value = it.value();
        if (value.typeId() == QMetaType::QVariantMap) {
            object.insert(it.key(), variantMapToJsonObject(value.toMap()));
        } else if (value.typeId() == QMetaType::QVariantList) {
            const QVariantList list = value.toList();
            QJsonArray array;
            for (const QVariant &item : list) {
                if (item.typeId() == QMetaType::QVariantMap) {
                    array.append(variantMapToJsonObject(item.toMap()));
                } else {
                    array.append(QJsonValue::fromVariant(item));
                }
            }
            object.insert(it.key(), array);
        } else {
            object.insert(it.key(), QJsonValue::fromVariant(value));
        }
    }
    return object;
}

QVariantMap SettingsPersistence::jsonObjectToVariantMap(const QJsonObject &object) const
{
    QVariantMap map;
    for (auto it = object.cbegin(); it != object.cend(); ++it) {
        const QJsonValue value = it.value();
        if (value.isObject()) {
            map.insert(it.key(), jsonObjectToVariantMap(value.toObject()));
        } else if (value.isArray()) {
            const QJsonArray array = value.toArray();
            QVariantList list;
            for (const QJsonValue &item : array) {
                if (item.isObject()) {
                    list.append(jsonObjectToVariantMap(item.toObject()));
                } else {
                    list.append(item.toVariant());
                }
            }
            map.insert(it.key(), list);
        } else {
            map.insert(it.key(), value.toVariant());
        }
    }
    return map;
}

} // namespace bos::shell
