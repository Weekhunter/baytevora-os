#pragma once

#include <memory>
#include <vector>

#include "bos/ApplicationInfo.h"

namespace bos::shell {

/**
 * @brief Owns all installed applications and provides query methods.
 *
 * The registry does not scan the filesystem. Applications are registered
 * programmatically during startup.
 */
class ApplicationRegistry {
public:
    ApplicationRegistry();
    ~ApplicationRegistry();

    ApplicationRegistry(const ApplicationRegistry &) = delete;
    ApplicationRegistry &operator=(const ApplicationRegistry &) = delete;

    /**
     * @brief Registers an application.
     */
    void registerApplication(const ApplicationInfo &info);

    /**
     * @brief Unregisters the application with the given ID.
     */
    void unregisterApplication(const QString &id);

    /**
     * @brief Finds an application by its unique ID.
     * @return A pointer to the application, or nullptr if not found.
     */
    const ApplicationInfo *findById(const QString &id) const;

    /**
     * @brief Finds an application by its display name.
     * @return A pointer to the application, or nullptr if not found.
     */
    const ApplicationInfo *findByName(const QString &name) const;

    /**
     * @return All registered applications.
     */
    std::vector<ApplicationInfo> applications() const;

private:
    std::vector<ApplicationInfo> m_applications;
};

} // namespace bos::shell
