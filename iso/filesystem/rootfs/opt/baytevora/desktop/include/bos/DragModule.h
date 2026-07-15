#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class DragManager;

/**
 * @brief Desktop module that owns the Baytevora Drag & Drop Framework.
 *
 * DragModule creates the DragManager during initialization and registers it
 * with ModuleManager so it follows the desktop session lifecycle.
 */
class DragModule : public DesktopModule {
public:
    DragModule();
    ~DragModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    DragManager *dragManager() const;

private:
    std::unique_ptr<DragManager> m_dragManager;
};

} // namespace bos::shell
