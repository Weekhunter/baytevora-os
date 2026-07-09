#pragma once

#include <memory>
#include <vector>

#include "bos/DesktopModule.h"

namespace bos::shell {

/**
 * @brief Owns and manages the lifecycle of all desktop modules.
 *
 * ModuleManager keeps a list of registered modules and invokes their lifecycle
 * methods in the correct order. It does not depend on concrete module types,
 * only on the DesktopModule interface.
 */
class ModuleManager {
public:
    ModuleManager();
    ~ModuleManager();

    ModuleManager(const ModuleManager &) = delete;
    ModuleManager &operator=(const ModuleManager &) = delete;

    /**
     * @brief Registers a module and takes ownership of it.
     *
     * Modules are stored in registration order, which determines initialization
     * and start order. Shutdown runs in reverse order.
     *
     * @param module A non-null module instance.
     */
    void registerModule(std::unique_ptr<DesktopModule> module);

    /**
     * @brief Calls initialize() on every registered module.
     */
    void initializeAll();

    /**
     * @brief Calls start() on every registered module.
     */
    void startAll();

    /**
     * @brief Calls shutdown() on every registered module in reverse order.
     */
    void shutdownAll();

    /**
     * @brief Finds a registered module by name.
     * @return A non-owning pointer to the module, or nullptr if not found.
     */
    DesktopModule *findModule(const QString &name) const;

private:
    void logLifecycle(const QString &name, const QString &action);

    std::vector<std::unique_ptr<DesktopModule>> m_modules;
};

} // namespace bos::shell
