#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class LockManager;

/**
 * @brief Desktop module that owns the Baytevora Lock Manager (BLS).
 *
 * LockModule creates the LockManager during initialization and registers it
 * with the module system so it follows the desktop session lifecycle.
 */
class LockModule : public DesktopModule {
public:
    LockModule();
    ~LockModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    LockManager *lockManager() const;

private:
    std::unique_ptr<LockManager> m_lockManager;
};

} // namespace bos::shell
