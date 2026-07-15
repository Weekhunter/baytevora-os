#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class StoreManager;

/**
 * @brief Desktop module that owns the Baytevora Store Manager (BSF).
 *
 * StoreModule creates the StoreManager during initialization and registers
 * it with the module system so it follows the desktop session lifecycle.
 */
class StoreModule : public DesktopModule {
public:
    StoreModule();
    ~StoreModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    StoreManager *storeManager() const;

private:
    std::unique_ptr<StoreManager> m_storeManager;
};

} // namespace bos::shell
