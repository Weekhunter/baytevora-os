#pragma once

#include <QObject>

#include "bos/DesktopModule.h"

namespace bos::shell {

/**
 * @brief Manages the launcher visibility state for the Baytevora Desktop Environment.
 *
 * LauncherModule is both a DesktopModule (owned by ModuleManager) and a QObject
 * (exposed to QML). It keeps the launcher open/close logic in C++ and emits
 * visibleChanged so QML can react without polling.
 */
class LauncherModule : public QObject, public DesktopModule {
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)

public:
    explicit LauncherModule(QObject *parent = nullptr);
    ~LauncherModule() override;

    // DesktopModule interface
    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    bool visible() const;

public slots:
    /**
     * @brief Opens the launcher and logs the action.
     */
    Q_INVOKABLE void openLauncher();

    /**
     * @brief Closes the launcher and logs the action.
     */
    Q_INVOKABLE void closeLauncher();

    /**
     * @brief Toggles the launcher open/closed state.
     */
    Q_INVOKABLE void toggleLauncher();

    /**
     * @brief Logs a placeholder launch request for the named application.
     */
    Q_INVOKABLE void requestLaunch(const QString &appName);

signals:
    void visibleChanged();

private:
    void setVisible(bool visible);

    bool m_visible = false;
};

} // namespace bos::shell
