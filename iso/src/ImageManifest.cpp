#include "big/ImageManifest.h"

#include <QDateTime>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

namespace big {

ImageManifest::ImageManifest(QObject *parent)
    : QObject(parent)
{
}

QString ImageManifest::version() const { return m_version; }
void ImageManifest::setVersion(const QString &value)
{
    if (m_version == value) return;
    m_version = value;
    emit versionChanged();
}

QString ImageManifest::buildTimestamp() const { return m_buildTimestamp; }
void ImageManifest::setBuildTimestamp(const QString &value)
{
    if (m_buildTimestamp == value) return;
    m_buildTimestamp = value;
    emit buildTimestampChanged();
}

QString ImageManifest::kernelVersion() const { return m_kernelVersion; }
void ImageManifest::setKernelVersion(const QString &value)
{
    if (m_kernelVersion == value) return;
    m_kernelVersion = value;
    emit kernelVersionChanged();
}

QVariantList ImageManifest::components() const { return m_components; }

void ImageManifest::addComponent(const QString &name, const QString &version, const QString &path)
{
    QVariantMap component;
    component[QStringLiteral("name")] = name;
    component[QStringLiteral("version")] = version;
    if (!path.isEmpty()) component[QStringLiteral("path")] = path;
    m_components.append(component);
    emit componentsChanged();
}

void ImageManifest::clearComponents()
{
    m_components.clear();
    emit componentsChanged();
}

QVariantMap ImageManifest::generateManifest() const
{
    QVariantMap manifest;
    manifest[QStringLiteral("version")] = m_version;
    manifest[QStringLiteral("buildTimestamp")] = m_buildTimestamp;
    manifest[QStringLiteral("kernelVersion")] = m_kernelVersion;
    manifest[QStringLiteral("components")] = m_components;
    return manifest;
}

QVariantMap ImageManifest::generateBuildInfo(const QVariantMap &buildParameters) const
{
    QVariantMap info;
    info[QStringLiteral("version")] = m_version;
    info[QStringLiteral("buildTimestamp")] = m_buildTimestamp;
    info[QStringLiteral("buildHost")] = QStringLiteral("Baytevora Build System");
    info[QStringLiteral("kernelVersion")] = m_kernelVersion;
    info[QStringLiteral("parameters")] = buildParameters;
    return info;
}

bool ImageManifest::saveManifest(const QString &path) const
{
    const QJsonDocument doc(QJsonObject::fromVariantMap(generateManifest()));
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

bool ImageManifest::saveBuildInfo(const QString &path, const QVariantMap &buildParameters) const
{
    const QJsonDocument doc(QJsonObject::fromVariantMap(generateBuildInfo(buildParameters)));
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

} // namespace big
