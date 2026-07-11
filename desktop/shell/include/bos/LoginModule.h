#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class LoginManager;

/**
 * @brief Desktop module that owns the Baytevora Login Manager (BLM).
 *
 * LoginModule creates the LoginManager during initialization and registers it
 * with the module system so it follows the desktop session lifecycle.
 */
class LoginModule : public DesktopModule {
public:
    LoginModule();
    ~LoginModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    LoginManager *loginManager() const;

private:
    std::unique_ptr<LoginManager> m_loginManager;
};

} // namespace bos::shell
