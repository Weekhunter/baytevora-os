#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class DesktopManager;

/**
 * @brief Desktop module that owns the DesktopManager.
 *
 * This module is responsible for initializing the desktop icon model during the
 * shell startup sequence. The DesktopManager is exposed to QML by the
 * Application class after the module has started.
 */
class DesktopIconsModule : public DesktopModule {
public:
    DesktopIconsModule();
    ~DesktopIconsModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    DesktopManager *desktopManager() const;

private:
    std::unique_ptr<DesktopManager> m_desktopManager;
};

} // namespace bos::shell
