#include "bos/DesktopSurfaceModule.h"

#include <QDebug>

namespace bos::shell {

DesktopSurfaceModule::DesktopSurfaceModule() = default;
DesktopSurfaceModule::~DesktopSurfaceModule() = default;

QString DesktopSurfaceModule::name() const
{
    return QStringLiteral("DesktopSurface");
}

void DesktopSurfaceModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
}

void DesktopSurfaceModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void DesktopSurfaceModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
}

} // namespace bos::shell
