#include "bos/ModuleManager.h"

#include <QDebug>

namespace bos::shell {

ModuleManager::ModuleManager() = default;
ModuleManager::~ModuleManager() = default;

void ModuleManager::registerModule(std::unique_ptr<DesktopModule> module)
{
    if (!module) {
        qWarning() << QStringLiteral("[BDE] Attempted to register a null module");
        return;
    }

    const QString name = module->name();
    m_modules.push_back(std::move(module));
    logLifecycle(name, QStringLiteral("registered"));
}

void ModuleManager::initializeAll()
{
    for (const auto &module : m_modules) {
        module->initialize();
        logLifecycle(module->name(), QStringLiteral("initialized"));
    }
}

void ModuleManager::startAll()
{
    for (const auto &module : m_modules) {
        module->start();
        logLifecycle(module->name(), QStringLiteral("started"));
    }
}

void ModuleManager::shutdownAll()
{
    // Shutdown in reverse order so later-registered dependencies stop first.
    for (auto it = m_modules.rbegin(); it != m_modules.rend(); ++it) {
        (*it)->shutdown();
        logLifecycle((*it)->name(), QStringLiteral("shutdown"));
    }
}

DesktopModule *ModuleManager::findModule(const QString &name) const
{
    for (const auto &module : m_modules) {
        if (module->name() == name) {
            return module.get();
        }
    }
    return nullptr;
}

void ModuleManager::logLifecycle(const QString &name, const QString &action)
{
    qDebug() << QStringLiteral("[BDE] Module") << action + QStringLiteral(":") << name;
}

} // namespace bos::shell
