#pragma once

#include <memory>

#include <QObject>

#include "bos/DesktopModule.h"
#include "bos/NotificationManager.h"

namespace bos::shell {

/**
 * @brief Desktop module that owns the notification service.
 *
 * NotificationModule initializes and exposes NotificationManager to the rest
 * of the system. UI presentation is handled entirely by QML.
 */
class NotificationModule : public QObject, public DesktopModule {
    Q_OBJECT

public:
    explicit NotificationModule(QObject *parent = nullptr);
    ~NotificationModule() override;

    // DesktopModule interface
    QString name() const override;
    void initialize() override;
    void start() override;
    void shutdown() override;

    /**
     * @return The notification manager owned by this module.
     */
    NotificationManager *notificationManager() const;

private:
    std::unique_ptr<NotificationManager> m_notificationManager;
};

} // namespace bos::shell
