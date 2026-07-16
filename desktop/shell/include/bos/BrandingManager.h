#pragma once

#include <QHash>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>

namespace bos::shell {

/**
 * @brief Central source of truth for Baytevora branding assets.
 *
 * BrandingManager resolves brand resources from the Baytevora Branding
 * Repository. All QML and C++ consumers must obtain logos, symbols, icons,
 * and wallpaper paths through this manager rather than hardcoding paths.
 */
class BrandingManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString companyName READ companyName CONSTANT)
    Q_PROPERTY(QString osName READ osName CONSTANT)
    Q_PROPERTY(QString osVersion READ osVersion CONSTANT)
    Q_PROPERTY(QString fullVersionLabel READ fullVersionLabel CONSTANT)
    Q_PROPERTY(QString poweredBy READ poweredBy CONSTANT)
    Q_PROPERTY(QStringList productIds READ productIds CONSTANT)

public:
    explicit BrandingManager(QObject *parent = nullptr);

    QString companyName() const;
    QString osName() const;
    QString osVersion() const;
    QString fullVersionLabel() const;
    QString poweredBy() const;
    QStringList productIds() const;

    Q_INVOKABLE QString productName(const QString &productId) const;

    Q_INVOKABLE QUrl applicationLogoUrl(const QString &applicationName,
                                        const QString &variant = QStringLiteral("default")) const;
    Q_INVOKABLE QUrl applicationSymbolUrl(const QString &applicationName) const;
    Q_INVOKABLE QUrl applicationFaviconUrl(const QString &applicationName) const;

    Q_INVOKABLE QUrl iconUrl(const QString &iconName) const;

    Q_INVOKABLE QUrl wallpaperUrl(const QString &name = QString()) const;
    Q_INVOKABLE QStringList availableWallpapers() const;

private:
    QString folderForApplication(const QString &applicationName) const;
    QString brandingFilePath(const QString &relativePath) const;
    QString logoFileName(const QString &variant) const;

    QString m_brandingDir;
    QHash<QString, QString> m_applicationToFolder;
    QHash<QString, QString> m_folderToName;
};

} // namespace bos::shell
