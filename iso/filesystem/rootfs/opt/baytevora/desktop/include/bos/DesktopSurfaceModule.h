#pragma once

#include "bos/DesktopModule.h"

namespace bos::shell {

/**
 * @brief Placeholder module for the desktop surface.
 *
 * This module does not contain any visible functionality in Sprint 4. It exists
 * to exercise the module lifecycle and to reserve a registration slot for the
 * desktop surface component that will be managed here in future sprints.
 */
class DesktopSurfaceModule : public DesktopModule {
public:
    DesktopSurfaceModule();
    ~DesktopSurfaceModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;
};

} // namespace bos::shell
