#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class PackageManager;

/**
 * @brief Desktop module that owns the Baytevora Package Manager (BPM).
 *
 * PackageModule creates the PackageManager during initialization and registers
 * it with the module system so it follows the desktop session lifecycle.
 */
class PackageModule : public DesktopModule {
public:
    PackageModule();
    ~PackageModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    PackageManager *packageManager() const;

private:
    std::unique_ptr<PackageManager> m_packageManager;
};

} // namespace bos::shell
