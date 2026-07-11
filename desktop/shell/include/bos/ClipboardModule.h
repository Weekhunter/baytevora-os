#pragma once

#include <memory>

#include "bos/DesktopModule.h"

namespace bos::shell {

class ClipboardManager;
class NotificationManager;

/**
 * @brief Desktop module that owns the ClipboardManager.
 *
 * ClipboardModule initializes the central clipboard manager during the shell
 * startup sequence. The ClipboardManager is exposed to QML by the Application
 * class after the module has started.
 */
class ClipboardModule : public DesktopModule {
public:
    ClipboardModule();
    ~ClipboardModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    ClipboardManager *clipboardManager() const;
    void setNotificationManager(NotificationManager *manager);

private:
    std::unique_ptr<ClipboardManager> m_clipboardManager;
};

} // namespace bos::shell
