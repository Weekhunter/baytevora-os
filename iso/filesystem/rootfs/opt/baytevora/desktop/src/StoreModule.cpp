#include "bos/StoreModule.h"

#include <QDebug>

#include "bos/StoreManager.h"

namespace bos::shell {

StoreModule::StoreModule() = default;
StoreModule::~StoreModule() = default;

QString StoreModule::name() const
{
    return QStringLiteral("Store");
}

void StoreModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_storeManager = std::make_unique<StoreManager>();
}

void StoreModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void StoreModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_storeManager.reset();
}

StoreManager *StoreModule::storeManager() const
{
    return m_storeManager.get();
}

} // namespace bos::shell
