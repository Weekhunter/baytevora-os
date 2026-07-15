#pragma once

#include <QObject>
#include <QString>

namespace bldf {

/**
 * @brief Configures the display manager for the Baytevora session.
 */
class DisplayManagerConfigurator : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)
    Q_PROPERTY(QString displayManager READ displayManager WRITE setDisplayManager NOTIFY displayManagerChanged FINAL)
    Q_PROPERTY(QString liveUser READ liveUser WRITE setLiveUser NOTIFY liveUserChanged FINAL)

public:
    explicit DisplayManagerConfigurator(QObject *parent = nullptr);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    QString displayManager() const;
    void setDisplayManager(const QString &value);

    QString liveUser() const;
    void setLiveUser(const QString &value);

    Q_INVOKABLE bool configureAll();
    Q_INVOKABLE bool createSessionFile();
    Q_INVOKABLE bool createSessionScript();
    Q_INVOKABLE bool createInstallerLauncher();
    Q_INVOKABLE bool configureSDDM();
    Q_INVOKABLE bool configureGDM();
    Q_INVOKABLE bool createLiveUser();

signals:
    void targetRootChanged();
    void displayManagerChanged();
    void liveUserChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool writeFile(const QString &path, const QString &contents);

    QString m_targetRoot;
    QString m_displayManager = QStringLiteral("sddm");
    QString m_liveUser = QStringLiteral("live");
};

} // namespace bldf
