#pragma once

#include <QString>

namespace bos::shell {

class ApplicationRegistry;

/**
 * @brief Validates launch requests before they are forwarded to ApplicationManager.
 *
 * ApplicationLauncher is a lightweight helper that checks whether the target
 * application exists in the registry.
 */
class ApplicationLauncher {
public:
    explicit ApplicationLauncher(const ApplicationRegistry *registry);
    ~ApplicationLauncher();

    ApplicationLauncher(const ApplicationLauncher &) = delete;
    ApplicationLauncher &operator=(const ApplicationLauncher &) = delete;

    /**
     * @brief Checks whether the application with the given name exists.
     * @return True if a launch request can be forwarded, false otherwise.
     */
    bool canLaunch(const QString &name) const;

    /**
     * @return A human-readable validation failure reason, or empty if valid.
     */
    QString lastError() const { return m_lastError; }

private:
    const ApplicationRegistry *m_registry;
    mutable QString m_lastError;
};

} // namespace bos::shell
