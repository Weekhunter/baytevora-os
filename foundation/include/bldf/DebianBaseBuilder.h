#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

namespace bldf {

/**
 * @brief Prepares the Debian Stable base for Baytevora OS.
 */
class DebianBaseBuilder : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString suite READ suite WRITE setSuite NOTIFY suiteChanged FINAL)
    Q_PROPERTY(QString mirror READ mirror WRITE setMirror NOTIFY mirrorChanged FINAL)
    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)
    Q_PROPERTY(QStringList packages READ packages WRITE setPackages NOTIFY packagesChanged FINAL)

public:
    explicit DebianBaseBuilder(QObject *parent = nullptr);

    QString suite() const;
    void setSuite(const QString &value);

    QString mirror() const;
    void setMirror(const QString &value);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    QStringList packages() const;
    void setPackages(const QStringList &value);

    Q_INVOKABLE bool loadPackageList(const QString &path);
    Q_INVOKABLE bool buildBase();
    Q_INVOKABLE bool verifyInstallation() const;

signals:
    void suiteChanged();
    void mirrorChanged();
    void targetRootChanged();
    void packagesChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool createDirectoryStructure();
    bool writeAptConfiguration();
    bool installPackages();
    bool createPlaceholderEnvironment();

    QString m_suite = QStringLiteral("stable");
    QString m_mirror = QStringLiteral("http://deb.debian.org/debian");
    QString m_targetRoot;
    QStringList m_packages;
};

} // namespace bldf
