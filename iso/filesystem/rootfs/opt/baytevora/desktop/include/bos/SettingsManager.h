#pragma once

#include <QElapsedTimer>
#include <QList>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QVariantList>

#include "bos/SettingsPage.h"

namespace bos::shell {

/**
 * @brief Backing model for the Settings application.
 *
 * SettingsManager owns the list of pages, tracks the currently selected page,
 * and exposes read-only system information. Placeholder configuration methods
 * log their requests but do not change the desktop; real engines will be wired
 * in future sprints.
 *
 * Each SettingsWindow.qml instantiates its own SettingsManager so that multiple
 * Settings windows remain independent.
 */
class SettingsManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList pages READ pages NOTIFY pagesChanged)
    Q_PROPERTY(QString currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(QString bosVersion READ bosVersion CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString architecture READ architecture CONSTANT)
    Q_PROPERTY(QString uptime READ uptime NOTIFY uptimeChanged)
    Q_PROPERTY(QString wallpaperPath READ wallpaperPath WRITE setWallpaperPath NOTIFY wallpaperPathChanged)

public:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager() override;

    QVariantList pages() const;
    QString currentPage() const;
    void setCurrentPage(const QString &pageId);

    QString bosVersion() const;
    QString qtVersion() const;
    QString architecture() const;
    QString uptime() const;

    QString wallpaperPath() const;
    void setWallpaperPath(const QString &path);

    Q_INVOKABLE void setTheme(const QString &theme);
    Q_INVOKABLE void setAccentColor(const QString &color);
    Q_INVOKABLE void setFontSize(int size);

    Q_INVOKABLE void chooseWallpaper();
    Q_INVOKABLE void restoreDefaultWallpaper();

signals:
    void pagesChanged();
    void currentPageChanged();
    void uptimeChanged();
    void wallpaperPathChanged();

private slots:
    void updateUptime();

private:
    QList<SettingsPage> m_pages;
    QString m_currentPage;
    QString m_wallpaperPath;
    QElapsedTimer m_sessionTimer;
    QTimer m_uptimeTimer;
};

} // namespace bos::shell
