#include "bos/SessionManager.h"

#include <QDebug>

#include "bos/ApplicationManager.h"
#include "bos/ClipboardModule.h"
#include "bos/DesktopIconsModule.h"
#include "bos/PowerModule.h"
#include "bos/SearchModule.h"
#include "bos/ShortcutModule.h"
#include "bos/DesktopSurfaceModule.h"
#include "bos/LauncherModule.h"
#include "bos/ModuleManager.h"
#include "bos/NotificationModule.h"
#include "bos/TaskbarModule.h"
#include "bos/WallpaperModule.h"
#include "bos/WindowManager.h"

namespace bos::shell {

SessionManager::SessionManager()
    : m_moduleManager(std::make_unique<ModuleManager>())
{
}

SessionManager::~SessionManager() = default;

void SessionManager::initialize()
{
    if (m_initialized) {
        log(QStringLiteral("Session already initialized"));
        return;
    }

    m_initialized = true;
    log(QStringLiteral("Session initialized"));

    // Register placeholder modules from previous sprints, the WindowManager
    // framework, the Taskbar module, and the Launcher module. Additional
    // desktop modules will be added here as they are implemented.
    m_moduleManager->registerModule(std::make_unique<DesktopSurfaceModule>());
    m_moduleManager->registerModule(std::make_unique<DesktopIconsModule>());
    m_moduleManager->registerModule(std::make_unique<ClipboardModule>());
    m_moduleManager->registerModule(std::make_unique<SearchModule>());
    m_moduleManager->registerModule(std::make_unique<PowerModule>());
    m_moduleManager->registerModule(std::make_unique<ShortcutModule>());
    m_moduleManager->registerModule(std::make_unique<WallpaperModule>());
    m_moduleManager->registerModule(std::make_unique<WindowManager>());
    m_moduleManager->registerModule(std::make_unique<TaskbarModule>());
    m_moduleManager->registerModule(std::make_unique<LauncherModule>());
    m_moduleManager->registerModule(std::make_unique<ApplicationManager>());
    m_moduleManager->registerModule(std::make_unique<NotificationModule>());

    m_moduleManager->initializeAll();
}

void SessionManager::start()
{
    if (!m_initialized) {
        log(QStringLiteral("Cannot start session: not initialized"));
        return;
    }
    if (m_started) {
        log(QStringLiteral("Session already started"));
        return;
    }

    m_moduleManager->startAll();
    m_started = true;
    log(QStringLiteral("Session started"));
}

void SessionManager::shutdown()
{
    if (!m_initialized) {
        log(QStringLiteral("Cannot shutdown session: not initialized"));
        return;
    }

    m_moduleManager->shutdownAll();
    log(QStringLiteral("Session shutdown requested"));
    m_started = false;
    m_initialized = false;
}

ModuleManager *SessionManager::moduleManager() const
{
    return m_moduleManager.get();
}

void SessionManager::log(const QString &message)
{
    qDebug() << QStringLiteral("[BDE]") << message;
}

} // namespace bos::shell
