#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class PowerManager;

/**
 * @brief Desktop module that owns the Baytevora Power Management Service.
 *
 * PowerModule creates the PowerManager during initialization and registers it
 * with ModuleManager so it participates in the desktop session lifecycle.
 */
class PowerModule : public DesktopModule {
public:
    PowerModule();
    ~PowerModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    PowerManager *powerManager() const;

private:
    std::unique_ptr<PowerManager> m_powerManager;
};

} // namespace bos::shell
