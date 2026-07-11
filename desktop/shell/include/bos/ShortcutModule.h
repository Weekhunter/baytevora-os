#pragma once

#include <memory>

#include "bos/DesktopModule.h"

class QWidget;

namespace bos::shell {

class ShortcutManager;

/**
 * @brief Desktop module that owns the ShortcutManager.
 *
 * ShortcutModule creates a hidden QWidget parent for the underlying QShortcut
 * objects and initializes the ShortcutManager during the module lifecycle.
 */
class ShortcutModule : public DesktopModule {
public:
    ShortcutModule();
    ~ShortcutModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    ShortcutManager *shortcutManager() const;

private:
    std::unique_ptr<QWidget> m_shortcutHost;
    std::unique_ptr<ShortcutManager> m_shortcutManager;
};

} // namespace bos::shell
