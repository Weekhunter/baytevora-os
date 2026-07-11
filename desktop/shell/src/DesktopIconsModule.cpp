#include "bos/DesktopIconsModule.h"

#include <QDebug>

#include "bos/DesktopManager.h"

namespace bos::shell {

DesktopIconsModule::DesktopIconsModule()
    : m_desktopManager(std::make_unique<DesktopManager>())
{
}

DesktopIconsModule::~DesktopIconsModule() = default;

QString DesktopIconsModule::name() const
{
    return QStringLiteral("DesktopIcons");
}

void DesktopIconsModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");

    if (m_desktopManager) {
        m_desktopManager->loadDefaults();
    }
}

void DesktopIconsModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void DesktopIconsModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
}

DesktopManager *DesktopIconsModule::desktopManager() const
{
    return m_desktopManager.get();
}

} // namespace bos::shell
