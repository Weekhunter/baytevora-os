#pragma once

#include <QString>

namespace bos::shell {

/**
 * @brief Abstract base class for all desktop environment modules.
 *
 * DesktopModule defines the lifecycle interface used by ModuleManager. Each
 * module provides a name and implements initialize(), start(), and shutdown().
 *
 * Concrete modules are owned by ModuleManager and are destroyed automatically
 * when the module manager is destroyed. Copying is disabled to keep ownership
 * clear.
 */
class DesktopModule {
public:
    virtual ~DesktopModule() = default;

    DesktopModule(const DesktopModule &) = delete;
    DesktopModule &operator=(const DesktopModule &) = delete;

    /**
     * @return The unique name of this module.
     */
    virtual QString name() const = 0;

    /**
     * @brief Initializes the module.
     *
     * Called once after registration and before start(). Modules should set
     * up internal state but not begin active work here.
     */
    virtual void initialize() = 0;

    /**
     * @brief Starts the module.
     *
     * Called after all modules have been initialized. Modules may begin active
     * work or publish services at this point.
     */
    virtual void start() = 0;

    /**
     * @brief Shuts down the module.
     *
     * Called during session shutdown. Modules should release resources and stop
     * active work.
     */
    virtual void shutdown() = 0;

protected:
    DesktopModule() = default;
};

} // namespace bos::shell
