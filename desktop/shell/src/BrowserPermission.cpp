#include "bos/BrowserPermission.h"

namespace bos::shell {

BrowserPermission::BrowserPermission(int permissionId, QObject *parent)
    : QObject(parent)
    , m_permissionId(permissionId)
{
}

BrowserPermission::~BrowserPermission() = default;

int BrowserPermission::permissionId() const { return m_permissionId; }
QString BrowserPermission::origin() const { return m_origin; }
QString BrowserPermission::permissionType() const { return m_permissionType; }
QString BrowserPermission::state() const { return m_state; }
QDateTime BrowserPermission::lastModified() const { return m_lastModified; }

void BrowserPermission::setOrigin(const QString &origin)
{
    if (m_origin == origin) {
        return;
    }
    m_origin = origin;
    emit originChanged();
}

void BrowserPermission::setPermissionType(const QString &permissionType)
{
    if (m_permissionType == permissionType) {
        return;
    }
    m_permissionType = permissionType;
    emit permissionTypeChanged();
}

void BrowserPermission::setState(const QString &state)
{
    if (m_state == state) {
        return;
    }
    m_state = state;
    emit stateChanged();
}

void BrowserPermission::setLastModified(const QDateTime &lastModified)
{
    if (m_lastModified == lastModified) {
        return;
    }
    m_lastModified = lastModified;
    emit lastModifiedChanged();
}

} // namespace bos::shell
