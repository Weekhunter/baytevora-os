#include "bos/NotificationModule.h"

#include <QDebug>

namespace bos::shell {

NotificationModule::NotificationModule(QObject *parent)
    : QObject(parent)
    , m_notificationManager(std::make_unique<NotificationManager>(this))
{
}

NotificationModule::~NotificationModule() = default;

QString NotificationModule::name() const
{
    return QStringLiteral("Notification");
}

void NotificationModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initialized");
}

void NotificationModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module started");
}

void NotificationModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
}

NotificationManager *NotificationModule::notificationManager() const
{
    return m_notificationManager.get();
}

} // namespace bos::shell
