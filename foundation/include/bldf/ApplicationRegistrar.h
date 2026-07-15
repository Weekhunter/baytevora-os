#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

namespace bldf {

/**
 * @brief Registers Baytevora applications with the desktop environment.
 */
class ApplicationRegistrar : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString targetRoot READ targetRoot WRITE setTargetRoot NOTIFY targetRootChanged FINAL)
    Q_PROPERTY(QString sourceRoot READ sourceRoot WRITE setSourceRoot NOTIFY sourceRootChanged FINAL)

public:
    explicit ApplicationRegistrar(QObject *parent = nullptr);

    QString targetRoot() const;
    void setTargetRoot(const QString &value);

    QString sourceRoot() const;
    void setSourceRoot(const QString &value);

    Q_INVOKABLE bool registerAll();
    Q_INVOKABLE bool registerApplication(const QString &name, const QString &exec,
                                          const QString &icon, const QString &comment = QString());
    Q_INVOKABLE bool configureMimeTypes();
    Q_INVOKABLE bool updateIconCache();

signals:
    void targetRootChanged();
    void sourceRootChanged();
    void logInfo(const QString &message);
    void logWarning(const QString &message);
    void logError(const QString &message);

private:
    bool writeFile(const QString &path, const QString &contents);

    QString m_targetRoot;
    QString m_sourceRoot;
};

} // namespace bldf
