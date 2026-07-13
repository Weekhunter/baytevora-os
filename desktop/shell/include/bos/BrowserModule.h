#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class BrowserManager;

/**
 * @brief Desktop module that owns the Baytevora Browser Foundation (BBF).
 *
 * BrowserModule creates the shared BrowserManager during initialization and
 * follows the existing desktop session lifecycle.
 */
class BrowserModule : public DesktopModule {
public:
    BrowserModule();
    ~BrowserModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    BrowserManager *browserManager() const;

private:
    std::unique_ptr<BrowserManager> m_browserManager;
};

} // namespace bos::shell
