#include "bos/LockModule.h"

#include <QDebug>

#include "bos/LockManager.h"

namespace bos::shell {

LockModule::LockModule() = default;
LockModule::~LockModule() = default;

QString LockModule::name() const
{
    return QStringLiteral("Lock");
}

void LockModule::initialize()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module initializing");
    m_lockManager = std::make_unique<LockManager>();
}

void LockModule::start()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module starting");
}

void LockModule::shutdown()
{
    qDebug() << QStringLiteral("[BDE]") << name() << QStringLiteral("module shutting down");
    m_lockManager.reset();
}

LockManager *LockModule::lockManager() const
{
    return m_lockManager.get();
}

} // namespace bos::shell
