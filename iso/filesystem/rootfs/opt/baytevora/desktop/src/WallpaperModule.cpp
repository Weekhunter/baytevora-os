#include "bos/WallpaperModule.h"

#include <QDebug>

namespace bos::shell {

WallpaperModule::WallpaperModule() = default;
WallpaperModule::~WallpaperModule() = default;

QString WallpaperModule::name() const
{
    return QStringLiteral("Wallpaper");
}

void WallpaperModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
}

void WallpaperModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void WallpaperModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
}

} // namespace bos::shell
