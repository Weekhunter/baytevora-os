#pragma once

#include "bos/DesktopModule.h"

namespace bos::shell {

/**
 * @brief Placeholder module for wallpaper management.
 *
 * This module does not manage the wallpaper in Sprint 4; the Wallpaper QML
 * component still handles rendering. This placeholder reserves the module slot
 * for future wallpaper services such as slideshows, dynamic wallpapers, or
 * configuration persistence.
 */
class WallpaperModule : public DesktopModule {
public:
    WallpaperModule();
    ~WallpaperModule() override;

    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;
};

} // namespace bos::shell
