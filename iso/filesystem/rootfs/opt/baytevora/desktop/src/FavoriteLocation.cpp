#include "bos/FavoriteLocation.h"

namespace bos::shell {

FavoriteLocation::FavoriteLocation(int favoriteId, QObject *parent)
    : QObject(parent)
    , m_favoriteId(favoriteId)
{
}

FavoriteLocation::~FavoriteLocation() = default;

int FavoriteLocation::favoriteId() const { return m_favoriteId; }
QString FavoriteLocation::displayName() const { return m_displayName; }
QString FavoriteLocation::path() const { return m_path; }
QString FavoriteLocation::icon() const { return m_icon; }
bool FavoriteLocation::pinned() const { return m_pinned; }

void FavoriteLocation::setDisplayName(const QString &displayName)
{
    if (m_displayName == displayName) {
        return;
    }
    m_displayName = displayName;
    emit displayNameChanged();
}

void FavoriteLocation::setPath(const QString &path)
{
    if (m_path == path) {
        return;
    }
    m_path = path;
    emit pathChanged();
}

void FavoriteLocation::setIcon(const QString &icon)
{
    if (m_icon == icon) {
        return;
    }
    m_icon = icon;
    emit iconChanged();
}

void FavoriteLocation::setPinned(bool pinned)
{
    if (m_pinned == pinned) {
        return;
    }
    m_pinned = pinned;
    emit pinnedChanged();
}

} // namespace bos::shell
