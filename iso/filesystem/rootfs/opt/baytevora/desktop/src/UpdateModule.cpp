#include "bos/UpdateModule.h"

#include <QDebug>

#include "bos/UpdateManager.h"

namespace bos::shell {

UpdateModule::UpdateModule() = default;
UpdateModule::~UpdateModule() = default;

QString UpdateModule::name() const
{
    return QStringLiteral("Update");
}

void UpdateModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_updateManager = std::make_unique<UpdateManager>();
}

void UpdateModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void UpdateModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_updateManager.reset();
}

UpdateManager *UpdateModule::updateManager() const
{
    return m_updateManager.get();
}

} // namespace bos::shell
