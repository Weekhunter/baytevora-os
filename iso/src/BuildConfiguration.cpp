#include "big/BuildConfiguration.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>

namespace big {

BuildConfiguration::BuildConfiguration(QObject *parent)
    : QObject(parent)
{
}

QString BuildConfiguration::sourceRoot() const { return m_sourceRoot; }
void BuildConfiguration::setSourceRoot(const QString &value)
{
    if (m_sourceRoot == value) return;
    m_sourceRoot = value;
    emit sourceRootChanged();
}

QString BuildConfiguration::outputDir() const { return m_outputDir; }
void BuildConfiguration::setOutputDir(const QString &value)
{
    if (m_outputDir == value) return;
    m_outputDir = value;
    emit outputDirChanged();
}

QString BuildConfiguration::filesystemType() const { return m_filesystemType; }
void BuildConfiguration::setFilesystemType(const QString &value)
{
    if (m_filesystemType == value) return;
    m_filesystemType = value;
    emit filesystemTypeChanged();
}

int BuildConfiguration::compressionLevel() const { return m_compressionLevel; }
void BuildConfiguration::setCompressionLevel(int value)
{
    if (m_compressionLevel == value) return;
    m_compressionLevel = value;
    emit compressionLevelChanged();
}

QString BuildConfiguration::kernelPath() const { return m_kernelPath; }
void BuildConfiguration::setKernelPath(const QString &value)
{
    if (m_kernelPath == value) return;
    m_kernelPath = value;
    emit kernelPathChanged();
}

QString BuildConfiguration::initramfsPath() const { return m_initramfsPath; }
void BuildConfiguration::setInitramfsPath(const QString &value)
{
    if (m_initramfsPath == value) return;
    m_initramfsPath = value;
    emit initramfsPathChanged();
}

bool BuildConfiguration::loadFromFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    const QByteArray data = file.readAll();
    if (path.endsWith(QStringLiteral(".yaml")) || path.endsWith(QStringLiteral(".yml"))) {
        // Minimal YAML parser for the known keys.
        const QString text = QString::fromUtf8(data);
        const QRegularExpression re(QStringLiteral("^\\s*(%1):\\s*(.+)$"));
        auto parse = [&text, this](const QString &key, auto setter) {
            const QRegularExpression lineRe(re.arg(QRegularExpression::escape(key)));
            const QRegularExpressionMatch match = lineRe.match(text);
            if (match.hasMatch()) {
                setter(match.captured(1).trimmed());
            }
        };
        parse(QStringLiteral("sourceRoot"), [this](const QString &v) { setSourceRoot(v); });
        parse(QStringLiteral("outputDir"), [this](const QString &v) { setOutputDir(v); });
        parse(QStringLiteral("filesystemType"), [this](const QString &v) { setFilesystemType(v); });
        parse(QStringLiteral("kernelPath"), [this](const QString &v) { setKernelPath(v); });
        parse(QStringLiteral("initramfsPath"), [this](const QString &v) { setInitramfsPath(v); });
        const QRegularExpression compRe(QStringLiteral("^\\s*compressionLevel:\\s*(\\d+)$"));
        const auto compMatch = compRe.match(text);
        if (compMatch.hasMatch()) {
            setCompressionLevel(compMatch.captured(1).toInt());
        }
        return true;
    }

    // JSON fallback.
    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return false;
    const QJsonObject obj = doc.object();
    setSourceRoot(obj.value(QStringLiteral("sourceRoot")).toString());
    setOutputDir(obj.value(QStringLiteral("outputDir")).toString());
    setFilesystemType(obj.value(QStringLiteral("filesystemType")).toString());
    setCompressionLevel(obj.value(QStringLiteral("compressionLevel")).toInt());
    setKernelPath(obj.value(QStringLiteral("kernelPath")).toString());
    setInitramfsPath(obj.value(QStringLiteral("initramfsPath")).toString());
    return true;
}

bool BuildConfiguration::validate() const
{
    if (m_sourceRoot.isEmpty() || m_outputDir.isEmpty()) return false;
    if (m_filesystemType.isEmpty()) return false;
    return true;
}

QVariantMap BuildConfiguration::toMap() const
{
    QVariantMap map;
    map[QStringLiteral("sourceRoot")] = m_sourceRoot;
    map[QStringLiteral("outputDir")] = m_outputDir;
    map[QStringLiteral("filesystemType")] = m_filesystemType;
    map[QStringLiteral("compressionLevel")] = m_compressionLevel;
    map[QStringLiteral("kernelPath")] = m_kernelPath;
    map[QStringLiteral("initramfsPath")] = m_initramfsPath;
    return map;
}

} // namespace big
