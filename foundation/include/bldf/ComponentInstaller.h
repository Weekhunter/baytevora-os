#pragma once

#include <QObject>
#include <QString>

namespace bldf {

/**
 * @brief Installs Baytevora components into the Linux root filesystem.
 */
class ComponentInstaller : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString sourceRoot READ sourceRoot WRITE setSourceRoot NOTIFY sourceRootChanged FINAL)
    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)

public:
    explicit ComponentInstaller(QObject *parent = nullptr);

    QString sourceRoot() const;
    void setSourceRoot(const QString &value);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    Q_INVOKABLE bool installAll();
    Q_INVOKABLE bool installDesktop();
    Q_INVOKABLE bool installInstaller();
    Q_INVOKABLE bool installBranding();
    Q_INVOKABLE bool installServices();
    Q_INVOKABLE bool installPackageManagerHook();

signals:
    void sourceRootChanged();
    void targetRootChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool copyDirectory(const QString &source, const QString &target);
    bool createSymlink(const QString &target, const QString &link);
    bool writeRegistry();

    QString m_sourceRoot;
    QString m_targetRoot;
};

} // namespace bldf
