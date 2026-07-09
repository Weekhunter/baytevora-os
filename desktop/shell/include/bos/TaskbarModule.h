#pragma once

#include "bos/DesktopModule.h"

namespace bos::shell {

/**
 * @brief Placeholder module that represents the BDE taskbar component.
 *
 * TaskbarModule participates in the module lifecycle and logs taskbar-specific
 * lifecycle events. The actual taskbar UI is implemented in QML and bound to
 * the WindowManager context property.
 */
class TaskbarModule : public DesktopModule {
public:
    TaskbarModule();
    ~TaskbarModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;
};

} // namespace bos::shell
