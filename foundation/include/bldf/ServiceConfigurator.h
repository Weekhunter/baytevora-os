#pragma once

#include <QObject>
#include <QString>

namespace bldf {

/**
 * @brief Configures system services for Baytevora OS.
 */
class ServiceConfigurator : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)

public:
    explicit ServiceConfigurator(QObject *parent = nullptr);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    Q_INVOKABLE bool configureAll();
    Q_INVOKABLE bool createBaytevoraServiceUnits();
    Q_INVOKABLE bool configureNetworkManager();
    Q_INVOKABLE bool configurePipeWire();
    Q_INVOKABLE bool configureCUPS();
    Q_INVOKABLE bool enableDebianServices();

signals:
    void targetRootChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool writeFile(const QString &path, const QString &contents);

    QString m_targetRoot;
};

} // namespace bldf
