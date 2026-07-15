#pragma once

#include <QList>
#include <QObject>
#include <QVariantList>

namespace bos::shell {

class BrowserPermission;
class NotificationManager;

/**
 * @brief Manages per-site browser permission rules.
 *
 * Permission rules are persisted to a local JSON file and loaded when the
 * browser starts. Supported permission types are Camera, Microphone, Location,
 * Notifications, Clipboard, and Popups. Supported states are Ask, Allow,
 * and Block.
 */
class BrowserPermissionManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVariantList permissions READ permissions NOTIFY permissionsChanged FINAL)

public:
    explicit BrowserPermissionManager(QObject *parent = nullptr);
    ~BrowserPermissionManager() override;

    QVariantList permissions() const;

    void setNotificationManager(NotificationManager *notificationManager);

    Q_INVOKABLE QString permission(const QString &origin, const QString &permissionType) const;
    Q_INVOKABLE void setPermission(const QString &origin, const QString &permissionType,
                                   const QString &state);
    Q_INVOKABLE void resetPermission(const QString &origin, const QString &permissionType);
    Q_INVOKABLE void resetAllPermissions();
    Q_INVOKABLE void resetPermissionsForOrigin(const QString &origin);
    Q_INVOKABLE QVariantList permissionsForOrigin(const QString &origin) const;

private:
    void load();
    void save();
    QString storageDirectory() const;
    QString storageFilePath() const;
    int generatePermissionId();
    BrowserPermission *findPermission(const QString &origin, const QString &permissionType) const;
    void emitNotification(const QString &title, const QString &message);

    QList<BrowserPermission*> m_permissions;
    NotificationManager *m_notificationManager = nullptr;
    int m_nextPermissionId = 1;
};

} // namespace bos::shell
