#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class UpdateManager;

/**
 * @brief Desktop module that owns the Baytevora Update Manager (BUM).
 *
 * UpdateModule creates the UpdateManager during initialization and registers it
 * with the module system so it follows the desktop session lifecycle.
 */
class UpdateModule : public DesktopModule {
public:
    UpdateModule();
    ~UpdateModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    UpdateManager *updateManager() const;

private:
    std::unique_ptr<UpdateManager> m_updateManager;
};

} // namespace bos::shell
