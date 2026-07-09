#pragma once

#include <QMap>
#include <QObject>
#include <QSet>
#include <QVariantList>

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class ApplicationLauncher;
class ApplicationRegistry;
class WindowManager;

/**
 * @brief Coordinates application launching for the Baytevora Desktop Environment.
 *
 * ApplicationManager is both a DesktopModule (owned by ModuleManager) and a
 * QObject (exposed to QML). It owns the ApplicationRegistry and
 * ApplicationLauncher, tracks running applications, and requests windows from
 * WindowManager.
 *
 * Sprint 10 only creates demonstration windows; real binaries are not executed.
 */
class ApplicationManager : public QObject, public DesktopModule {
    Q_OBJECT

    /**
     * @brief Registered applications exposed to QML.
     */
    Q_PROPERTY(QVariantList applications READ applications NOTIFY applicationsChanged)

    /**
     * @brief Names of currently running applications exposed to QML.
     */
    Q_PROPERTY(QVariantList runningApplications READ runningApplications NOTIFY runningApplicationsChanged)

public:
    explicit ApplicationManager(QObject *parent = nullptr);
    ~ApplicationManager() override;

    // DesktopModule interface
    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    /**
     * @brief Sets the WindowManager used to create application windows.
     *
     * Must be called before launching applications. This is wired in
     * Application.cpp after all modules have started.
     */
    void setWindowManager(WindowManager *windowManager);

    QVariantList applications() const;
    QVariantList runningApplications() const;

public slots:
    /**
     * @brief Launches the application with the given display name.
     *
     * Validates the request, enforces single-instance policy, and requests a
     * demonstration window from WindowManager.
     */
    Q_INVOKABLE bool launchApplication(const QString &name);

signals:
    void applicationsChanged();
    void runningApplicationsChanged();

private:
    void registerPlaceholderApplications();
    void onWindowClosed(int id);

    std::unique_ptr<ApplicationRegistry> m_registry;
    std::unique_ptr<ApplicationLauncher> m_launcher;
    WindowManager *m_windowManager = nullptr;

    QSet<QString> m_running;
    QMap<int, QString> m_windowToApp;
};

} // namespace bos::shell
