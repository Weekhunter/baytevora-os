#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

#include "bos/SessionManager.h"

namespace bos::shell {

class FirstBootManager;
class SettingsPersistence;
class WelcomeManager;

/**
 * @brief The Application class manages the desktop shell lifecycle.
 *
 * This class encapsulates the Qt application initialization and QML engine
 * setup. It is intentionally small for Sprint 1 and designed to be extended as
 * future sprints add additional desktop modules.
 */
class Application {
public:
    /**
     * @brief Constructs the shell application.
     * @param app Reference to the QGuiApplication instance created in main().
     */
    explicit Application(QGuiApplication &app);

    ~Application();

    /**
     * @brief Loads the QML interface and starts the Qt event loop.
     * @return The application's exit code.
     */
    int run();

private:
    /**
     * @brief Performs internal setup that does not require a running event loop.
     */
    void initialize();

    /**
     * @brief Loads the main QML interface from the BOS.Shell module.
     */
    void loadInterface();

    /**
     * @brief Sprint 22: loads the login screen before the desktop session.
     */
    void loadLoginInterface();

    /**
     * @brief Milestone F: loads the first-boot setup wizard.
     */
    void loadFirstBootInterface();

    /**
     * @brief Milestone F: opens the Welcome Center window after first login.
     */
    void openWelcomeCenter();

    /**
     * @brief Sprint 22: starts the desktop session and loads the desktop UI.
     */
    void startDesktopSession();

    /**
     * @brief Registers the QML types and enums required by the shell.
     */
    void registerQmlTypes();

    /**
     * @brief Exposes the Baytevora Design Language token managers to QML.
     */
    void exposeDesignManagers();

    /**
     * @brief Connects QML engine signals used for error handling.
     */
    void connectSignals();

    QObject *m_loginWindow = nullptr;
    QObject *m_firstBootWindow = nullptr;
    QObject *m_welcomeCenterWindow = nullptr;

    SettingsPersistence *m_settingsPersistence = nullptr;
    FirstBootManager *m_firstBootManager = nullptr;
    WelcomeManager *m_welcomeManager = nullptr;

    QGuiApplication &m_app;
    std::unique_ptr<QQmlApplicationEngine> m_engine;
    std::unique_ptr<SessionManager> m_sessionManager;
};

} // namespace bos::shell
