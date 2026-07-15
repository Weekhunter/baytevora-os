#pragma once

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace big {

/**
 * @brief Loads and validates the YAML/JSON build configuration.
 */
class BuildConfiguration : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString sourceRoot READ sourceRoot WRITE setSourceRoot NOTIFY sourceRootChanged FINAL)
    Q_PROPERTY(QString outputDir READ outputDir WRITE setOutputDir NOTIFY outputDirChanged FINAL)
    Q_PROPERTY(QString filesystemType READ filesystemType WRITE setFilesystemType NOTIFY filesystemTypeChanged FINAL)
    Q_PROPERTY(int compressionLevel READ compressionLevel WRITE setCompressionLevel NOTIFY compressionLevelChanged FINAL)
    Q_PROPERTY(QString kernelPath READ kernelPath WRITE setKernelPath NOTIFY kernelPathChanged FINAL)
    Q_PROPERTY(QString initramfsPath READ initramfsPath WRITE setInitramfsPath NOTIFY initramfsPathChanged FINAL)

public:
    explicit BuildConfiguration(QObject *parent = nullptr);

    QString sourceRoot() const;
    void setSourceRoot(const QString &value);

    QString outputDir() const;
    void setOutputDir(const QString &value);

    QString filesystemType() const;
    void setFilesystemType(const QString &value);

    int compressionLevel() const;
    void setCompressionLevel(int value);

    QString kernelPath() const;
    void setKernelPath(const QString &value);

    QString initramfsPath() const;
    void setInitramfsPath(const QString &value);

    Q_INVOKABLE bool loadFromFile(const QString &path);
    Q_INVOKABLE bool validate() const;
    Q_INVOKABLE QVariantMap toMap() const;

signals:
    void sourceRootChanged();
    void outputDirChanged();
    void filesystemTypeChanged();
    void compressionLevelChanged();
    void kernelPathChanged();
    void initramfsPathChanged();

private:
    QString m_sourceRoot;
    QString m_outputDir;
    QString m_filesystemType = QStringLiteral("squashfs");
    int m_compressionLevel = 9;
    QString m_kernelPath;
    QString m_initramfsPath;
};

} // namespace big
