#pragma once

#include <QObject>
#include <QString>

namespace bldf {

/**
 * @brief Configures the Linux filesystem for Baytevora OS.
 */
class FilesystemConfigurator : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)
    Q_PROPERTY(QString hostname READ hostname WRITE setHostname NOTIFY hostnameChanged FINAL)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged FINAL)
    Q_PROPERTY(QString timezone READ timezone WRITE setTimezone NOTIFY timezoneChanged FINAL)

public:
    explicit FilesystemConfigurator(QObject *parent = nullptr);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    QString hostname() const;
    void setHostname(const QString &value);

    QString locale() const;
    void setLocale(const QString &value);

    QString timezone() const;
    void setTimezone(const QString &value);

    Q_INVOKABLE bool configureAll();
    Q_INVOKABLE bool configureFstab();
    Q_INVOKABLE bool configureHostname();
    Q_INVOKABLE bool configureHosts();
    Q_INVOKABLE bool configureLocale();
    Q_INVOKABLE bool configureTimezone();
    Q_INVOKABLE bool configureResolv();
    Q_INVOKABLE bool configureOsRelease();
    Q_INVOKABLE bool configureSudoers();

signals:
    void targetRootChanged();
    void hostnameChanged();
    void localeChanged();
    void timezoneChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool writeFile(const QString &path, const QString &contents);

    QString m_targetRoot;
    QString m_hostname = QStringLiteral("baytevora-live");
    QString m_locale = QStringLiteral("en_US.UTF-8");
    QString m_timezone = QStringLiteral("UTC");
};

} // namespace bldf
