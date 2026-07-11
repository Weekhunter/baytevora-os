#include "bos/PowerModule.h"

#include <QDebug>

#include "bos/PowerManager.h"

namespace bos::shell {

PowerModule::PowerModule()
{
}

PowerModule::~PowerModule() = default;

QString PowerModule::name() const
{
    return QStringLiteral("Power");
}

void PowerModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_powerManager = std::make_unique<PowerManager>();
}

void PowerModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void PowerModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_powerManager.reset();
}

PowerManager *PowerModule::powerManager() const
{
    return m_powerManager.get();
}

} // namespace bos::shell
