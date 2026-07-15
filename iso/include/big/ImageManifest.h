#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace big {

/**
 * @brief Generates ISO image manifest and build information.
 */
class ImageManifest : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged FINAL)
    Q_PROPERTY(QString buildTimestamp READ buildTimestamp WRITE setBuildTimestamp NOTIFY buildTimestampChanged FINAL)
    Q_PROPERTY(QString kernelVersion READ kernelVersion WRITE setKernelVersion NOTIFY kernelVersionChanged FINAL)
    Q_PROPERTY(QVariantList components READ components NOTIFY componentsChanged FINAL)

public:
    explicit ImageManifest(QObject *parent = nullptr);

    QString version() const;
    void setVersion(const QString &value);

    QString buildTimestamp() const;
    void setBuildTimestamp(const QString &value);

    QString kernelVersion() const;
    void setKernelVersion(const QString &value);

    QVariantList components() const;

    Q_INVOKABLE void addComponent(const QString &name, const QString &version, const QString &path = QString());
    Q_INVOKABLE void clearComponents();
    Q_INVOKABLE QVariantMap generateManifest() const;
    Q_INVOKABLE QVariantMap generateBuildInfo(const QVariantMap &buildParameters) const;
    Q_INVOKABLE bool saveManifest(const QString &path) const;
    Q_INVOKABLE bool saveBuildInfo(const QString &path, const QVariantMap &buildParameters) const;

signals:
    void versionChanged();
    void buildTimestampChanged();
    void kernelVersionChanged();
    void componentsChanged();

private:
    QString m_version = QStringLiteral("0.1 Alpha");
    QString m_buildTimestamp;
    QString m_kernelVersion = QStringLiteral("unknown");
    QVariantList m_components;
};

} // namespace big
