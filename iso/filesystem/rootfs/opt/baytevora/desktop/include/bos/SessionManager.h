#pragma once

#include <QString>
#include <memory>

namespace bos::shell {

class ModuleManager;

/**
 * @brief Coordinates the startup and shutdown of the Baytevora Desktop
 * Environment.
 *
 * The SessionManager is intentionally lightweight in Sprint 3. It provides the
 * lifecycle hooks (initialize, start, shutdown) and a module registration system
 * used by the Application class to control the desktop session startup order.
 *
 * Future sprints will extend this class with real shutdown coordination,
 * service lifecycle management, and richer module metadata.
 */
class SessionManager {
public:
    SessionManager();
    ~SessionManager();

    // Disable copying to keep ownership clear and avoid accidental sharing.
    SessionManager(const SessionManager &) = delete;
    SessionManager &operator=(const SessionManager &) = delete;

    /**
     * @brief Initializes the desktop session and the module system.
     *
     * This method registers the built-in placeholder modules, then calls
     * ModuleManager::initializeAll().
     */
    void initialize();

    /**
     * @brief Starts the desktop session.
     *
     * Delegates to ModuleManager::startAll() and logs that the session is
     * running.
     */
    void start();

    /**
     * @brief Shuts down the desktop session.
     *
     * Delegates to ModuleManager::shutdownAll(). Full shutdown logic will be
     * added in future sprints.
     */
    void shutdown();

    /**
     * @return A non-owning pointer to the ModuleManager owned by this session.
     */
    ModuleManager *moduleManager() const;

private:
    void log(const QString &message);

    bool m_initialized = false;
    bool m_started = false;
    std::unique_ptr<ModuleManager> m_moduleManager;
};

} // namespace bos::shell
